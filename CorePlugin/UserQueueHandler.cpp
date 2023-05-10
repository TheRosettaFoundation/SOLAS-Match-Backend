#include "UserQueueHandler.h"

#include <QThread>
#include <QTimer>
#include <QDebug>

#include "Common/ConfigParser.h"
#include "Common/protobufs/requests/RequestMessage.pb.h"
#include "Common/protobufs/requests/StatisticsUpdateRequest.pb.h"
#include "Common/protobufs/requests/UserTaskStreamNotificationRequest.pb.h"
#include "Common/protobufs/requests/OrgCreatedNotificationRequest.pb.h"
#include "Common/protobufs/notifications/TaskRevokedNotification.pb.h"

#include "UserJobs/TaskStreamNotificationHandler.h"
#include "UserJobs/StatisticsUpdate.h"
#include "UserJobs/OrgCreatedNotifications.h"
#include "UserJobs/TaskRevokedNotificationHandler.h"

#include "Common/protobufs/emails/JSON.h"

using namespace SolasMatch::Common::Protobufs::Requests;
using namespace SolasMatch::Common::Protobufs::Notifications;

UserQueueHandler::UserQueueHandler()
{
    // Default Constructor
}

void UserQueueHandler::run()
{
    qDebug() << "Running UserQueueHandler on thread " << this->thread()->currentThreadId();
    this->registerRequestTypes();
    ConfigParser settings;

    QTimer *message_queue_read_timer = new QTimer();
    connect(message_queue_read_timer, SIGNAL(timeout()), this, SLOT(consumeFromQueue()));
    message_queue_read_timer->start(settings.get("messaging.poll_rate").toInt());
}

void UserQueueHandler::consumeFromQueue()
{
    if (!QFileInfo::exists("/repo/SOLAS-Match-Backend/STOP_consumeFromQueue")) {
        QSharedPointer<MySQLHandler> db = MySQLHandler::getInstance();
        QMap<QString, QVariant> queue_request = TaskDao::get_queue_request(db, 1);
        if (!queue_request.isNull()) {
            qDebug() << "UserQueueHandler: Message received";
            switch (queue_request["type"]) {
                case 3:
                    UserTaskRevokedGenerator = new UserTaskRevokedGenerator();
                    UserTaskRevokedGenerator->run(queue_request["task_id"], queue_request["claimant_id"]);
                break;
            }

            TaskDao::remove_queue_request(db, queue_request["id"]);
        }
    }
}
//    StatisticsUpdateRequest statUpdate = StatisticsUpdateRequest();
//    qRegisterMetaType<StatisticsUpdate>(QString::fromStdString(statUpdate.class_name()).toLatin1());
//    UserTaskStreamNotificationRequest streamReq = UserTaskStreamNotificationRequest();
//    qRegisterMetaType<TaskStreamNotificationHandler>(QString::fromStdString(streamReq.class_name()).toLatin1());
//    OrgCreatedNotificationRequest orgCreated = OrgCreatedNotificationRequest();
//    qRegisterMetaType<OrgCreatedNotifications>(QString::fromStdString(orgCreated.class_name()).toLatin1());
//    TaskRevokedNotification taskRevoked = TaskRevokedNotification();
//    qRegisterMetaType<TaskRevokedNotificationHandler>(QString::fromStdString(taskRevoked.class_name()).toLatin1());

