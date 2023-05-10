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

#include "Common/protobufs/emails/JSON.h"

using namespace SolasMatch::Common::Protobufs::Notifications;
using namespace SolasMatch::Common::Protobufs::Emails;
using namespace SolasMatch::Common::Protobufs::Models;

TaskRevokedNotificationHandler::TaskRevokedNotificationHandler()
{
}

TaskRevokedNotificationHandler::~TaskRevokedNotificationHandler()
{
}

void TaskRevokedNotificationHandler::run(task_id, claimant_id)
{
    qDebug() << "Starting new thread to handle task revoked notifications";

    QSharedPointer<MySQLHandler> db = MySQLHandler::getInstance();
    QList<QSharedPointer<User> > subscribedUsers = TaskDao::getSubscribedUsers(db, task_id);
    if (subscribedUsers.length() > 0) {
                    OrgTaskRevokedEmail subscriberNotification;
                    subscriberNotification.set_claimant_id(claimant_id);
                    subscriberNotification.set_task_id(task_id);
                    subscriberNotification.set_email_type(subscriberNotification.email_type());
                    foreach (QSharedPointer<User> user, subscribedUsers) {
                        subscriberNotification.set_user_id(user->id());
                        client.publish(exchange, topic, subscriberNotification.SerializeAsString());
                    }
    } else {
        qDebug() << "TaskRevokedNotification: No users subscribed to task";
    }

    UserTaskRevokedEmail userNotification;
    userNotification.set_task_id(task_id);
    userNotification.set_user_id(claimant_id);
    userNotification.set_email_type(userNotification.email_type());
    client.publish(exchange, topic, userNotification.SerializeAsString());
}
