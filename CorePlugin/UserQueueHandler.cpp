#include "UserQueueHandler.h"

#include <QTimer>
#include <QDebug>

#include "Common/ConfigParser.h"

#include "UserJobs/TaskStreamNotificationHandler.h"
#include "UserJobs/StatisticsUpdate.h"
#include "UserJobs/OrgCreatedNotifications.h"
#include "UserJobs/TaskRevokedNotificationHandler.h"

UserQueueHandler::UserQueueHandler()
{
    // Default Constructor
}

void UserQueueHandler::run()
{
    qDebug() << "Running UserQueueHandler on thread " << this->thread()->currentThreadId();
    ConfigParser settings;

    QTimer *message_queue_read_timer = new QTimer();
    connect(message_queue_read_timer, SIGNAL(timeout()), this, SLOT(consumeFromQueue()));
    message_queue_read_timer->start(settings.get("messaging.poll_rate").toInt());
}

void UserQueueHandler::consumeFromQueue()
{
    static QMutex mutex;
    if (mutex.tryLock()) {
        if (!QFileInfo::exists("/repo/SOLAS-Match-Backend/STOP_consumeFromQueue")) {
            QSharedPointer<MySQLHandler> db = MySQLHandler::getInstance();
            QMap<QString, QVariant> queue_request = TaskDao::get_queue_request(db, 1);
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


                }
                TaskDao::remove_queue_request(db, queue_request["id"]);
            }
        }
        mutex.unlock();
    } else qDebug() << "UserQueueHandler: Skipping consumeFromQueue() invocation";
}
//    OrgCreatedNotificationRequest orgCreated = OrgCreatedNotificationRequest();
//    qRegisterMetaType<OrgCreatedNotifications>(QString::fromStdString(orgCreated.class_name()).toLatin1());

//    UserTaskStreamNotificationRequest streamReq = UserTaskStreamNotificationRequest();
//    qRegisterMetaType<TaskStreamNotificationHandler>(QString::fromStdString(streamReq.class_name()).toLatin1());
