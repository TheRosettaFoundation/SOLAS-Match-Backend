#include "UserQueueHandler.h"

#include <QTimer>
#include <QDebug>

#include "Common/ConfigParser.h"

#include "UserJobs/TaskStreamNotificationHandler.h"
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
