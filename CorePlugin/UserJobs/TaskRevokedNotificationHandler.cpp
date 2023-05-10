#include "TaskRevokedNotificationHandler.h"

#include <QDebug>
#include <QSharedPointer>

#include "Common/ConfigParser.h"
#include "Common/MySQLHandler.h"
#include "Common/DataAccessObjects/TaskDao.h"
#include "Common/protobufs/models/User.pb.h"

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
        OrgTaskRevokedGenerator = new OrgTaskRevokedGenerator();
        foreach (QSharedPointer<User> user, subscribedUsers) {
            OrgTaskRevokedGenerator->run(task_id, user->id(), claimant_id);
        }
    } else {
        qDebug() << "TaskRevokedNotification: No users subscribed to task";
    }
    UserTaskRevokedGenerator = new UserTaskRevokedGenerator();
    UserTaskRevokedGenerator->run(task_id, claimant_id);
}
