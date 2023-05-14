#include "TaskQueueHandler.h"

#include <QThread>
#include <QTimer>
#include <QDebug>

#include "Common/ConfigParser.h"

#include "TaskJobs/DeadlineChecker.h"

#include "Generators/OrgDeadlinePassedEmailGenerator.h"
#include "Generators/UserTaskDeadlineEmailGenerator.h"
#include "Generators/UserClaimedTaskEarlyWarningDeadlinePassedEmailGenerator.h"
#include "Generators/UserClaimedTaskLateWarningDeadlinePassedEmailGenerator.h"
#include "Generators/UserRecordWarningDeadlinePassedEmailGenerator.h"

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
            QMap<QString, QVariant> queue_request = TaskDao::get_queue_request(db, TASKQUEUE);
            if (!queue_request.isNull()) {
                qDebug() << "TaskQueueHandler type:" << queue_request["type"];
                switch (queue_request["type"]) {
                    case RUNDEADLINECHECK:
                        DeadlineChecker::run()
                        break;
                    case RUNSTATISTICSUPDATE:
                        TaskDao::update_statistics(db);
                        break;
                }
                TaskDao::mark_queue_request_sent(db, queue_request["id"]);
            }
        }
        mutex.unlock();
    } else qDebug() << "UserQueueHandler: Skipping consumeFromQueue() invocation";
}
