#include "CalculateProjectDeadlines.h"

#include <QDebug>
#include <QDateTime>

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

        QSharedPointer<MySQLHandler> db = MySQLHandler::getInstance();
        QSharedPointer<Project> project = ProjectDao::getProject(db, request.project_id());
        QList<QSharedPointer<Task> > tasks = TaskDao::getTasks(db, -1, request.project_id());

        if (project.isNull() || tasks.count() < 1) {
            qDebug() << "CalculateProjectDeadlines: Unable to find data in DB, searched for project "
                     << QString::number(request.project_id()) << " and its tasks";
        } else {
            QList<QList<int> > layers = QList<QList<int> >();
            QList<int> rootLayer = QList<int>();
            QMap<int, QSharedPointer<Task> > taskMap = QMap<int, QSharedPointer<Task> >();
            QMap<int, QList<QSharedPointer<Task> > > taskPreReqs = QMap<int, QList<QSharedPointer<Task> > >();
            foreach (QSharedPointer<Task> task, tasks) {
                taskMap.insert(task->id(), task);
                QList<QSharedPointer<Task> > preReqs = TaskDao::getTaskPreReqs(db, task->id());
                if (preReqs.count() < 1) {
                    rootLayer.append(task->id());
                } else {
                    taskPreReqs.insert(task->id(), preReqs);
                }
            }
            layers.append(rootLayer);

            QList<int> previousLayer = rootLayer;
            QList<int> currentLayer = QList<int>();
            while (taskPreReqs.count() > 0) {
                QMapIterator<int, QList<QSharedPointer<Task> > > i(taskPreReqs);
                while (i.hasNext()) {
                    i.next();
                    QList<QSharedPointer<Task> > preReqs = i.value();
                    foreach (QSharedPointer<Task> task, preReqs) {
                        if (previousLayer.contains(task->id())) {
                            preReqs.removeOne(task);
                        }
                    }

                    if (preReqs.count() < 1) {
                        currentLayer.append(i.key());
                        taskPreReqs.remove(i.key());
                    } else {
                        taskPreReqs.insert(i.key(), preReqs);
                    }
                }

                layers.append(currentLayer);
                previousLayer = currentLayer;
                currentLayer = QList<int>();
            }

            int i = layers.count() - 1;
            QDateTime deadline = QDateTime::fromString(
                        QString::fromStdString(project->deadline()), "yyyy-MM-ddTHH:mm:ss");
            QDateTime created = QDateTime::fromString(
                        QString::fromStdString(project->createdtime()), "yyyy-MM-ddTHH:mm:ss");
            if (created.addDays(((layers.count() - 1) * 3) + 1) <= deadline) {
                qDebug() << "Updating project task deadlines";
                deadline = deadline.addDays(-1);
                while (i >= 0) {
                    foreach (int taskId, layers.at(i)) {
                        QSharedPointer<Task> task = taskMap.value(taskId);
                        task->set_deadline(deadline.toString("yyyy-MM-ddTHH:mm:ss").toStdString());
                        TaskDao::insertAndUpdate(db, task);
                    }
                    deadline = deadline.addDays(-3);
                    i--;
                }
            } else {
                qDebug() << "Not enough time to automatically set project task deadlines";
            }
        }
    } else {
        qDebug() << "CalculateProjectDeadlines: Processing failed - empty message";
    }
}

void CalculateProjectDeadlines::setAMQPMessage(AMQPMessage *message)
{
    this->message = message;
}
