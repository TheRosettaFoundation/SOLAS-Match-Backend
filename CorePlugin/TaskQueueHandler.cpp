#include "TaskQueueHandler.h"

#include <QThread>
#include <QTimer>
#include <QDebug>

#include "Common/ConfigParser.h"

#include "TaskJobs/DeadlineChecker.h"
#include "TaskJobs/SendTaskUploadNotifications.h"

using namespace SolasMatch::Common::Protobufs::Requests;

TaskQueueHandler::TaskQueueHandler()
{
    // Default Constructor
}

void TaskQueueHandler::run()
{
    qDebug() << "Running TaskQueueHandler on thread " << this->thread()->currentThreadId();
    ConfigParser settings;

    QTimer *message_queue_read_timer = new QTimer();
    connect(message_queue_read_timer, SIGNAL(timeout()), client, SLOT(consumeFromQueue()));
    message_queue_read_timer->start(settings.get("messaging.poll_rate").toInt());
}

[[[
void UserQueueHandler::consumeFromQueue()
{
    static QMutex mutex;
    if (mutex.tryLock()) {
        if (!QFileInfo::exists("/repo/SOLAS-Match-Backend/STOP_consumeFromQueue")) {
            QSharedPointer<MySQLHandler> db = MySQLHandler::getInstance();
            QMap<QString, QVariant> queue_request = TaskDao::get_queue_request(db, 1); // UserQueueHandler: 1
            if (!queue_request.isNull()) {
                qDebug() << "UserQueueHandler type:" << queue_request["type"];
                switch (queue_request["type"]) {
                    case 3?:
                        TaskRevokedNotificationHandler::run(queue_request["task_id"], queue_request["claimant_id"]);
                    break;
                    case 4?:
                        TaskDao::update_statistics(db);
                        // db->call("statsUpdateAll", "");
                    break;

                    case 3?:
                        OrgCreatedNotifications::run(queue_request["org_id"]);
                    break;

                    case 3?:
TaskStreamNotificationHandler::run();
                    break;

                    case 3?:
DeadlineChecker::run()
                    break;

                }
                TaskDao::remove_queue_request(db, queue_request["id"]);
            }
        }
        mutex.unlock();
    } else qDebug() << "UserQueueHandler: Skipping consumeFromQueue() invocation";
}
]]]
void TaskQueueHandler::messageReceived(AMQPMessage *message)
{
    qDebug() << "TaskQueueHandler: Received Message";

    AMQPQueue *messageQueue = message->getQueue();
    if(messageQueue != NULL)
    {
        messageQueue->Ack(message->getDeliveryTag());
    }

    uint32_t length = 0;
    char *body = message->getMessage(&length);

  if (SolasMatch::Common::Protobufs::Emails::JSON::isJSON(std::string(body, length))) {
    SolasMatch::Common::Protobufs::Emails::JSON requestMessage;
    requestMessage.ParseFromString(std::string(body, length));

    int classId = QMetaType::type(QString::fromStdString(requestMessage.class_name()).toLatin1());
    if (classId == 0) {
        qDebug() << "TaskQueueHandler JSON: Invalid proto type: " << QString::fromStdString(requestMessage.class_name());
    } else {
        JobInterface *runnable = static_cast<JobInterface *>(QMetaType::create(classId));
        runnable->setAMQPMessage(message);
        this->mThreadPool->start(runnable);
    }
  } else {
    RequestMessage requestMessage;
    requestMessage.ParseFromString(std::string(body, length));

    int classId = QMetaType::type(QString::fromStdString(requestMessage.class_name()).toLatin1());
    if (classId == 0) {
        qDebug() << "TaskQueueHandler: Invalid proto type: " << QString::fromStdString(requestMessage.class_name());
    } else {
        JobInterface *runnable = static_cast<JobInterface *>(QMetaType::create(classId));
        runnable->setAMQPMessage(message);
        this->mThreadPool->start(runnable);
    }
  }
}
