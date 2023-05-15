#include "TaskRevokedNotificationHandler.h"

#include <QDebug>
#include <QSharedPointer>

#include "Common/ConfigParser.h"
#include "Common/MySQLHandler.h"
#include "Common/DataAccessObjects/TaskDao.h"
#include "Common/protobufs/models/User.pb.h"

#include "../EmailPlugin/Generators/OrgTaskRevokedGenerator.h"
#include "../EmailPlugin/Generators/UserTaskRevokedGenerator.h"

using namespace SolasMatch::Common::Protobufs::Models;

void TaskRevokedNotificationHandler::run(int task_id, int claimant_id)
{
    qDebug() << "TaskRevokedNotificationHandler task_id:" << QString::number(task_id) << "claimant_id:" << QString::number(claimant_id);

    QSharedPointer<MySQLHandler> db = MySQLHandler::getInstance();
    QList<QSharedPointer<User> > subscribedUsers = TaskDao::getSubscribedUsers(db, task_id);
    if (subscribedUsers.length() > 0) {
        foreach (QSharedPointer<User> user, subscribedUsers) {
            OrgTaskRevokedGenerator::run(task_id, user->id(), claimant_id);
        }
    } else {
        qDebug() << "TaskRevokedNotificationHandler: No users subscribed to task";
    }
    UserTaskRevokedGenerator::run(task_id, claimant_id);
}
