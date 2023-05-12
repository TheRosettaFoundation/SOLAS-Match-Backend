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
    connect(message_queue_read_timer, SIGNAL(timeout()), this, SLOT(consumeFromQueue()));
    message_queue_read_timer->start(settings.get("messaging.poll_rate").toInt());
}

void TaskQueueHandler::consumeFromQueue()
{
    static QMutex mutex;
    if (mutex.tryLock()) {
        if (!QFileInfo::exists("/repo/SOLAS-Match-Backend/STOP_consumeFromQueue")) {
            QSharedPointer<MySQLHandler> db = MySQLHandler::getInstance();
???            QMap<QString, QVariant> queue_request = TaskDao::get_queue_request(db, 1); // UserQueueHandler: 1
            if (!queue_request.isNull()) {
                qDebug() << "UserQueueHandler type:" << queue_request["type"];
                switch (queue_request["type"]) {
                    case 3?:
NOT HERE                        TaskRevokedNotificationHandler::run(queue_request["task_id"], queue_request["claimant_id"]);
                    break;
                    case 4?:
NOT HERE                        TaskDao::update_statistics(db);
                        // db->call("statsUpdateAll", "");
                    break;

                    case 3?:
NOT HERE                        OrgCreatedNotifications::run(queue_request["org_id"]);
                    break;

                    case 3?:
NOT HERETaskStreamNotificationHandler::run();
                    break;

                    case 3?:
OR IN USER QUEUE (DUP) DeadlineChecker::run();
                    break;

                    case 3?:
SendTaskuploadNotifications::run(queue_request["task_id"]);
                    break;
                }
                TaskDao::remove_queue_request(db, queue_request["id"]);
            }
        }
        mutex.unlock();
    } else qDebug() << "UserQueueHandler: Skipping consumeFromQueue() invocation";
}
