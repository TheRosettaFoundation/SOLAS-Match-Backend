#include "TaskQueueHandler.h"

#include <QThread>
#include <QTimer>
#include <QFileInfo>
#include <QDebug>

#include "Common/ConfigParser.h"

#include "TaskJobs/DeadlineChecker.h"

#include "../EmailPlugin/Generators/OrgDeadlinePassedEmailGenerator.h"
#include "../EmailPlugin/Generators/UserTaskDeadlineEmailGenerator.h"
#include "../EmailPlugin/Generators/UserClaimedTaskEarlyWarningDeadlinePassedEmailGenerator.h"
#include "../EmailPlugin/Generators/UserClaimedTaskLateWarningDeadlinePassedEmailGenerator.h"
#include "../EmailPlugin/Generators/UserRecordWarningDeadlinePassedEmailGenerator.h"

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
            QMap<QString, QVariant> queue_request = UserDao::get_queue_request(db, TASKQUEUE);
            if (!queue_request.isEmpty()) {
                qDebug() << "TaskQueueHandler type:" << queue_request["type"].toInt();
                switch (queue_request["type"].toInt()) {
                    case RUNDEADLINECHECK:
                        DeadlineChecker::run();
                        break;
                    case RUNSTATISTICSUPDATE:
                        UserDao::update_statistics(db);
                        break;
                }
                UserDao::mark_queue_request_handled(db, queue_request["id"].toInt());
            }
        }
        mutex.unlock();
    } else qDebug() << "UserQueueHandler: Skipping consumeFromQueue() invocation";
}
