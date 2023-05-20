#include "UserQueueHandler.h"

#include <QTimer>
#include <QFileInfo>
#include <QDebug>

#include "Common/ConfigParser.h"

#include "UserJobs/TaskStreamNotificationHandler.h"

#include "../EmailPlugin/Generators/UserTaskStreamEmailGenerator.h"

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
            QMap<QString, QVariant> queue_request = UserDao::get_queue_request(db, USERQUEUE);
            if (!queue_request.isEmpty()) {
                qDebug() << "UserQueueHandler type:" << queue_request["type"].toInt();
                switch (queue_request["type"].toInt()) {
                    case RUNTASKSTREAM:
                        TaskStreamNotificationHandler::run();
                    break;
                }
                UserDao::mark_queue_request_handled(db, queue_request["id"].toULongLong());
            }
        }
        mutex.unlock();
    } else qDebug() << "UserQueueHandler: Skipping consumeFromQueue() invocation";
}

void UserQueueHandler::setThreadPool(QThreadPool *tp)
{
    this->mThreadPool = tp;
}

bool UserQueueHandler::isEnabled()
{
    return true;
}
