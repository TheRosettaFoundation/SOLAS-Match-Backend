#include "TaskRevokedNotificationHandler.h"

#include <QDebug>
#include <QSharedPointer>

#include "Common/ConfigParser.h"
#include "Common/MySQLHandler.h"
#include "Common/MessagingClient.h"
#include "Common/DataAccessObjects/TaskDao.h"
#include "Common/protobufs/notifications/TaskRevokedNotification.pb.h"
#include "Common/protobufs/models/User.pb.h"
#include "Common/protobufs/emails/UserTaskRevokedEmail.pb.h"
#include "Common/protobufs/emails/OrgTaskRevokedEmail.pb.h"

using namespace SolasMatch::Common::Protobufs::Notifications;
using namespace SolasMatch::Common::Protobufs::Emails;
using namespace SolasMatch::Common::Protobufs::Models;

TaskRevokedNotificationHandler::TaskRevokedNotificationHandler()
{
    this->message = NULL;
}

TaskRevokedNotificationHandler::TaskRevokedNotificationHandler(AMQPMessage *proto)
{
    this->message = proto;
}

TaskRevokedNotificationHandler::~TaskRevokedNotificationHandler()
{
}

void TaskRevokedNotificationHandler::run()
{
    qDebug() << "Starting new thread to handle task revoked notifications";
    ConfigParser settings;
    QString exchange = settings.get("messaging.exchange");
    QString topic = "email.task.revoked";
    QSharedPointer<MySQLHandler> db = MySQLHandler::getInstance();

    MessagingClient client;
    if (client.init()) {
        uint32_t length = 0;
        char *body = this->message->getMessage(&length);
        if (length > 0) {
            TaskRevokedNotification notification;
            if (notification.ParseFromString(body)) {
                QList<QSharedPointer<User> > subscribedUsers = TaskDao::getSubscribedUsers(db, notification.task_id());
                if (subscribedUsers.length() > 0) {
                    OrgTaskRevokedEmail subscriberNotification;
                    subscriberNotification.set_claimant_id(notification.claimant_id());
                    subscriberNotification.set_task_id(notification.task_id());
                    subscriberNotification.set_email_type(subscriberNotification.email_type());
                    foreach (QSharedPointer<User> user, subscribedUsers) {
                        subscriberNotification.set_user_id(user->id());
                        client.publish(exchange, topic, QString::fromStdString(subscriberNotification.SerializeAsString()));
                    }
                } else {
                    qDebug() << "TaskRevokedNotification: No users subscribed to task";
                }

                UserTaskRevokedEmail userNotification;
                userNotification.set_task_id(notification.task_id());
                userNotification.set_user_id(notification.claimant_id());
                userNotification.set_email_type(userNotification.email_type());
                client.publish(exchange, topic, QString::fromStdString(userNotification.SerializeAsString()));
            } else {
                qDebug() << "TaskRevokedNotificationHandler: Failed to parse message body";
            }
        } else {
            qDebug() << "TaskRevokedNotificationHandler: Unable to parse message body, length is 0";
        }
    } else {
        qDebug() << "TaskRevokedNotificationHandler: Failed to initialise RabbitMQ Client";
    }
}

void TaskRevokedNotificationHandler::setAMQPMessage(AMQPMessage *message)
{
    this->message = message;
}
