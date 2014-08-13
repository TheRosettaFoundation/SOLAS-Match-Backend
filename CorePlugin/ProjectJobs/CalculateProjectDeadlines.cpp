#include "CalculateProjectDeadlines.h"

#include <QDebug>
#include <QDateTime>
#include <QStringList>

#include "Common/GraphBuilder.h"
#include "Common/ConfigParser.h"
#include "Common/Definitions.h"
#include "Common/MessagingClient.h"

#include "Common/protobufs/requests/CalculateProjectDeadlinesRequest.pb.h"
#include "Common/protobufs/emails/ProjectCreatedEmail.pb.h"

#include "Common/protobufs/models/Task.pb.h"
#include "Common/protobufs/models/Project.pb.h"

#include "Common/DataAccessObjects/ProjectDao.h"
#include "Common/DataAccessObjects/TaskDao.h"

using namespace SolasMatch::Common::Protobufs::Requests;
using namespace SolasMatch::Common::Protobufs::Emails;

CalculateProjectDeadlines::CalculateProjectDeadlines()
{
    // Default Constructor
}

CalculateProjectDeadlines::~CalculateProjectDeadlines()
{
}

void CalculateProjectDeadlines::run()
{
    qDebug() << "Starting new thread to calculate project deadlines";
    uint32_t length = 0;

    char *body = this->message->getMessage(&length);
    CalculateProjectDeadlinesRequest request;
    if (length > 0) {
        request.ParseFromString(body);

        // Send email to site admins informing them of the new project
        ProjectCreatedEmail projectCreatedEmail = ProjectCreatedEmail();
        projectCreatedEmail.set_email_type(EmailMessage::ProjectCreated);
        projectCreatedEmail.set_project_id(request.project_id());
        ConfigParser settings;
        MessagingClient publisher;
        publisher.init();
        QStringList admins = settings.get("mail.admin_emails").split(",");
        foreach(QString admin, admins) {
            projectCreatedEmail.set_recipient_email(admin.trimmed().toStdString());
            publisher.publish(settings.get("messaging.exchange"), "email",
                              QString::fromStdString(projectCreatedEmail.SerializeAsString()));
        }

        QSharedPointer<MySQLHandler> db  = MySQLHandler::getInstance();
        QSharedPointer<Project> project = ProjectDao::getProject(db, request.project_id());

        if (!project.isNull()) {
            GraphBuilder mBuilder = GraphBuilder();
            if (mBuilder.getProjectGraph(project->id()) && mBuilder.isGraphValid()) {
                QSharedPointer<WorkflowGraph> graph = mBuilder.getGraph();
                foreach (::google::protobuf::int32 nodeId, graph->rootnode()) {
                    int index = mBuilder.find(nodeId);
                    WorkflowNode node = graph->allnodes(index);
                    this->calculateSubGraphDeadlines(node, mBuilder, project, db);
                }
            } else {
                qDebug() << "CalculateProjectDeadlines: failed to construct workflow graph";
            }
        } else {
            qDebug() << "CalculateProjectDeadlines: No project found with id " << request.project_id();
        }
    } else {
        qDebug() << "CalculateProjectDeadlines: Processing failed - empty message";
    }
}

void CalculateProjectDeadlines::calculateSubGraphDeadlines(WorkflowNode node, GraphBuilder builder,
                                                           QSharedPointer<Project> project, QSharedPointer<MySQLHandler> db)
{
    QMap<QString, int> deadlineDefaults = QMap<QString, int>();
    deadlineDefaults.insert("zero", 0);
    deadlineDefaults.insert("gracePeriod", 1);
    deadlineDefaults.insert("segmentationPeriod", 3);
    deadlineDefaults.insert("translationPeriod", 3);
    deadlineDefaults.insert("proofreadingPeriod", 3);
    deadlineDefaults.insert("desegmentationPeriod", 3);
    QList<QString> deadlineLengths = QList<QString>();

    QDateTime createdDate = QDateTime::fromString(
                QString::fromStdString(project->createdtime()), "yyyy-MM-ddTHH:mm:ss");
    QDateTime projectDeadline = QDateTime::fromString(
                QString::fromStdString(project->deadline()), "yyyy-MM-ddTHH:mm:ss");

    ::google::protobuf::RepeatedField< ::google::protobuf::int32> currentLayer =
            ::google::protobuf::RepeatedField< ::google::protobuf::int32>();
    currentLayer.Add(node.taskid());
    ::google::protobuf::RepeatedField< ::google::protobuf::int32> previousLayer =
            ::google::protobuf::RepeatedField< ::google::protobuf::int32>();

    deadlineLengths = this->parseGraphForDefaultLengths(deadlineDefaults, builder, currentLayer, &previousLayer);
    deadlineLengths.removeLast();
    deadlineLengths.append("gracePeriod");
    deadlineDefaults = this->calculateDeadlineDefaults(deadlineDefaults, deadlineLengths, createdDate, projectDeadline);

    this->setProjectDeadlines(deadlineLengths, deadlineDefaults, builder, projectDeadline, db, previousLayer);
}

QMap<QString, int> CalculateProjectDeadlines::calculateDeadlineDefaults(QMap<QString, int> deadlineDefaults,
                                                                        QList<QString> deadlineLengths,
                                                                        QDateTime created, QDateTime deadline)
{
    int estimatedProjectLength = 0;
    foreach (QString period, deadlineLengths) {
        estimatedProjectLength += deadlineDefaults.value(period);
    }

    if (created.daysTo(deadline) > 3) {
        int count = -1;
        while (created.addDays(estimatedProjectLength + 3) > deadline) {
            switch (count) {
                case -1:
                    deadlineDefaults.insert("gracePeriod", deadlineDefaults.value("gracePeriod") - 1);
                    break;
                case 0:
                    deadlineDefaults.insert("segmentationPeriod", deadlineDefaults.value("segmentationPeriod") - 1);
                    break;
                case 1:
                    deadlineDefaults.insert("desegmentationPeriod", deadlineDefaults.value("desegmentationPeriod") - 1);
                    break;
                case 2:
                    deadlineDefaults.insert("proofreadingPeriod", deadlineDefaults.value("proofreadingPeriod") - 1);
                    break;
                case 3:
                    deadlineDefaults.insert("translationPeriod", deadlineDefaults.value("translationPeriod") - 1);
                    break;
            }
            count++;
            count = count % 4;

            estimatedProjectLength = 0;
            foreach (QString period, deadlineLengths) {
                estimatedProjectLength += deadlineDefaults.value(period);
            }
        }
    } else {
        deadlineDefaults.insert("gracePeriod", 0);
        deadlineDefaults.insert("segmentationPeriod", 0);
        deadlineDefaults.insert("desegmentationPeriod", 0);
        deadlineDefaults.insert("proofreadingPeriod", 0);
        deadlineDefaults.insert("translationPeriod", 0);
    }

    return deadlineDefaults;
}

/*
 * @param leafNodes - When this returns leafNodes contains the ids of all tasks in the last layer of the graph
 */
QList<QString> CalculateProjectDeadlines::parseGraphForDefaultLengths(QMap<QString, int> defaults, GraphBuilder builder,
                                              ::google::protobuf::RepeatedField<google::protobuf::int32> currentLayer,
                                              ::google::protobuf::RepeatedField<google::protobuf::int32> *leafNodes)
{
    ::google::protobuf::RepeatedField< ::google::protobuf::int32> nextLayer =
            ::google::protobuf::RepeatedField< ::google::protobuf::int32>();
    ::google::protobuf::RepeatedField< ::google::protobuf::int32> previousLayer =
            ::google::protobuf::RepeatedField< ::google::protobuf::int32>();
    QList<QString> deadlineLengths = QList<QString>();

    while (currentLayer.size() > 0) {
        QString maxDeadline = "zero";
        foreach (::google::protobuf::int32 nodeId, currentLayer) {
            int index = builder.find(nodeId);
            WorkflowNode node = builder.getGraph()->allnodes(index);
            Task task = node.task();
            switch (task.tasktype()) {
                case CHUNKING:
                if (defaults.value(maxDeadline) < defaults.value("segmentationPeriod")) {
                    maxDeadline = "segmentationPeriod";
                }
                break;
                case TRANSLATION:
                if (defaults.value(maxDeadline) < defaults.value("translationPeriod")) {
                    maxDeadline = "translationPeriod";
                }
                break;
                case PROOFREADING:
                if (defaults.value(maxDeadline) < defaults.value("proofreadingPeriod")) {
                    maxDeadline = "proofreadingPeriod";
                }
                break;
                case POSTEDITING:
                if (defaults.value(maxDeadline) < defaults.value("desegmentationPeriod")) {
                    maxDeadline = "desegmentationPeriod";
                }
                break;
            }

            foreach (::google::protobuf::int32 nextId, node.next()) {
                bool found = false;
                foreach (::google::protobuf::int32 nId, nextLayer) {
                    if (nextId == nId) {
                        found = true;
                    }
                }
                if (!found) {
                    nextLayer.Add(nextId);
                }
            }
        }
        deadlineLengths.append(maxDeadline);

        previousLayer = currentLayer;
        currentLayer = nextLayer;
        nextLayer.Clear();
    }

    foreach (::google::protobuf::int32 leafId, previousLayer) {
        leafNodes->Add(leafId);
    }

    return deadlineLengths;
}

/*
 * @param currentLayer - The list of task ids in the bottom layer of the graph
 */
void CalculateProjectDeadlines::setProjectDeadlines(QList<QString> deadlineLengths, QMap<QString, int> defaults,
                                                    GraphBuilder builder, QDateTime projectDeadline, QSharedPointer<MySQLHandler> db,
                                                    ::google::protobuf::RepeatedField<google::protobuf::int32> currentLayer)
{
    ::google::protobuf::RepeatedField< ::google::protobuf::int32> previousLayer =
            ::google::protobuf::RepeatedField< ::google::protobuf::int32>();
    int count = deadlineLengths.size() - 1;

    while (currentLayer.size() > 0) {
        foreach (::google::protobuf::int32 nodeId, currentLayer) {
            int index = builder.find(nodeId);
            WorkflowNode currentNode = builder.getGraph()->allnodes(index);
            Task task = currentNode.task();

            if (task.taskstatus() < IN_PROGRESS) {
                int taskDeadlinePeriod = 0;
                for (int i = count; i < deadlineLengths.size(); i++) {
                    taskDeadlinePeriod += defaults.value(deadlineLengths.at(i));
                }
                QDateTime taskDeadline = projectDeadline.addDays(-(taskDeadlinePeriod));
                task.set_deadline(taskDeadline.toString("yyyy-MM-dd HH:mm:ss").toStdString());
                qDebug() << "Setting deadline of task " << task.id() << " to " << taskDeadline.toString("yyyy-MM-dd HH:mm:ss");
                TaskDao::insertAndUpdate(db, task);
            }

            foreach (::google::protobuf::int32 prevId, currentNode.previous()) {
                bool found = false;
                foreach (::google::protobuf::int32 pId, previousLayer) {
                    if (prevId == pId) {
                        found = true;
                    }
                }
                if (!found) {
                    previousLayer.Add(prevId);
                }
            }
        }
        count--;

        currentLayer = previousLayer;
        previousLayer.Clear();
    }
}

void CalculateProjectDeadlines::setAMQPMessage(AMQPMessage *message)
{
    this->message = message;
}
