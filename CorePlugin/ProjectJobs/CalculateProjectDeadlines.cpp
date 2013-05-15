#include "CalculateProjectDeadlines.h"

#include <QDebug>
#include <QDateTime>

#include "Common/GraphBuilder.h"
#include "Common/Definitions.h"

#include "Common/protobufs/requests/CalculateProjectDeadlinesRequest.pb.h"

#include "Common/protobufs/models/Task.pb.h"
#include "Common/protobufs/models/Project.pb.h"

#include "Common/DataAccessObjects/ProjectDao.h"
#include "Common/DataAccessObjects/TaskDao.h"

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

        GraphBuilder mBuilder = GraphBuilder();
        if (mBuilder.getProjectGraph(request.project_id()) && mBuilder.isGraphValid()) {
            QSharedPointer<MySQLHandler> db  = MySQLHandler::getInstance();
            QSharedPointer<Project> project = ProjectDao::getProject(db, request.project_id());

            QSharedPointer<WorkflowGraph> graph = mBuilder.getGraph();
            foreach (::google::protobuf::int32 nodeId, graph->rootnode()) {
                int index = mBuilder.find(nodeId);
                WorkflowNode node = graph->allnodes(index);
                this->calculateSubGraphDeadlines(node, mBuilder, project);
            }
        } else {
            qDebug() << "CalculateProjectDeadlines: failed to construct workflow graph";
        }
    } else {
        qDebug() << "CalculateProjectDeadlines: Processing failed - empty message";
    }
}

void CalculateProjectDeadlines::calculateSubGraphDeadlines(WorkflowNode node, GraphBuilder builder,
                                                           QSharedPointer<Project> project)
{
    int *zero = new int(0);
    int *gracePeriod = new int(1);
    int *segmentationPeriod = new int(3);
    int *translationPeriod = new int(3);
    int *proofreadingPeriod = new int(3);
    int *desegmentationPeriod = new int(3);
    QList<int *> deadlineLengths = QList<int *>();

    QDateTime projectDeadline = QDateTime::fromString(
                QString::fromStdString(project->deadline()), "yyyy-MM-ddTHH:mm:ss");
    QDateTime createdDate = QDateTime::fromString(
                QString::fromStdString(project->createdtime()), "yyyy-MM-ddTHH:mm:ss");
    ::google::protobuf::RepeatedField< ::google::protobuf::int32> currentLayer =
            ::google::protobuf::RepeatedField< ::google::protobuf::int32>();
    currentLayer.Add(node.taskid());
    ::google::protobuf::RepeatedField< ::google::protobuf::int32> nextLayer =
            ::google::protobuf::RepeatedField< ::google::protobuf::int32>();
    ::google::protobuf::RepeatedField< ::google::protobuf::int32> previousLayer =
            ::google::protobuf::RepeatedField< ::google::protobuf::int32>();
    while (currentLayer.size() > 0) {
        int *maxDeadline = zero;
        foreach (::google::protobuf::int32 nodeId, currentLayer) {
            int index = builder.find(nodeId);
            WorkflowNode node = builder.getGraph()->allnodes(index);
            Task task = node.task();
            switch (task.tasktype()) {
                case CHUNKING:
                if (*(maxDeadline) < *(segmentationPeriod)) {
                    maxDeadline = segmentationPeriod;
                }
                break;
                case TRANSLATION:
                if (*(maxDeadline) < *(translationPeriod)) {
                    maxDeadline = translationPeriod;
                }
                break;
                case PROOFREADING:
                if (*(maxDeadline) < *(proofreadingPeriod)) {
                    maxDeadline = proofreadingPeriod;
                }
                break;
                case POSTEDITING:
                if (*(maxDeadline) < *(desegmentationPeriod)) {
                    maxDeadline = desegmentationPeriod;
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

    deadlineLengths.removeLast();
    deadlineLengths.append(gracePeriod);
    int estimatedProjectLength = 0;
    foreach (int *period, deadlineLengths) {
        estimatedProjectLength += *(period);
    }

    int count = -1;
    while (createdDate.addDays(estimatedProjectLength + 3) > projectDeadline) {
        switch (count) {
            case -1:
                (*gracePeriod)--;
                break;
            case 0:
                (*segmentationPeriod)--;
                break;
            case 1:
                (*desegmentationPeriod)--;
                break;
            case 2:
                (*proofreadingPeriod)--;
                break;
            case 3:
                (*translationPeriod)--;
                break;
        }
        count++;
        count = count % 4;

        estimatedProjectLength = 0;
        foreach (int *period, deadlineLengths) {
            estimatedProjectLength += *(period);
        }
    }

    count = deadlineLengths.size() - 1;
    currentLayer = previousLayer;
    previousLayer.Clear();
    while (currentLayer.size() > 0) {
        foreach (::google::protobuf::int32 nodeId, currentLayer) {
            int index = builder.find(nodeId);
            WorkflowNode currentNode = builder.getGraph()->allnodes(index);
            Task task = currentNode.task();

            if (task.taskstatus() < IN_PROGRESS) {
                int taskDeadlinePeriod = 0;
                for (int i = count; i < deadlineLengths.size(); i++) {
                    taskDeadlinePeriod += *(deadlineLengths.at(i));
                }
                QDateTime taskDeadline = projectDeadline.addDays(-(taskDeadlinePeriod));
                task.set_deadline(taskDeadline.toString("yyyy-MM-ddTHH:mm:ss").toStdString());
                TaskDao::insertAndUpdate(db, QSharedPointer<Task>(&task));
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

    delete zero;
    delete gracePeriod;
    delete segmentationPeriod;
    delete translationPeriod;
    delete proofreadingPeriod;
    delete desegmentationPeriod;
}

void CalculateProjectDeadlines::setAMQPMessage(AMQPMessage *message)
{
    this->message = message;
}
