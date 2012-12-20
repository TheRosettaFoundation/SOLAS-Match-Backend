#include "DeadlineChecker.h"

#include <QDebug>
#include <QUuid>
#include <QThread>
#include <QDateTime>

#include "Common/DataAccessObjects/TaskDao.h"
#include "Common/protobufs/models/Task.pb.h"
#include "Common/protobufs/requests/DeadlineCheckRequest.pb.h"

DeadlineChecker::DeadlineChecker()
{
    //Default Constructor
}

DeadlineChecker::DeadlineChecker(AMQPMessage *mess)
{
    this->message = mess;
}

DeadlineChecker::~DeadlineChecker()
{
    //delete message;
}

void DeadlineChecker::run()
{
    qDebug() << "Starting new thread " << this->thread()->currentThreadId();
    db = new MySQLHandler(QUuid::createUuid().toString());
    if(db->init()) {
        QList<QSharedPointer<Task> > tasks = TaskDao::getTasks(db);
        foreach(QSharedPointer<Task> task, tasks) {
            QDateTime currentTime = QDateTime::currentDateTime();
            QDateTime deadlineTime = QDateTime::fromString(QString::fromStdString(task->deadline()), "yyyy-MM-ddTHH:mm:ss");
            if(currentTime > deadlineTime) {
                qDebug() << "Task " << task->id() << " is pass its deadline of " << QString::fromStdString(task->deadline());
            }
        }
    } else {
        qDebug() << "Unable to connect to MySQL server. Check conf.ini for DB settings.";
    }

    if(message->getQueue()) {
        message->getQueue()->Ack(message->getDeliveryTag());
    }
    delete db;
}
