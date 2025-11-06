#include "DeadlineChecker.h"

#include <QDebug>
#include <QThread>

#include "Common/ConfigParser.h"
#include "Common/DataAccessObjects/TaskDao.h"
#include "Common/DataAccessObjects/ProjectDao.h"
#include "Common/DataAccessObjects/UserDao.h"
#include "Common/protobufs/models/Task.pb.h"
#include "Common/protobufs/models/Project.pb.h"

#include "../EmailPlugin/Generators/OrgDeadlinePassedEmailGenerator.h"
#include "../EmailPlugin/Generators/UserTaskDeadlineEmailGenerator.h"
#include "../EmailPlugin/Generators/UserClaimedTaskEarlyWarningDeadlinePassedEmailGenerator.h"
#include "../EmailPlugin/Generators/UserClaimedTaskLateWarningDeadlinePassedEmailGenerator.h"
#include "../EmailPlugin/Generators/UserRecordWarningDeadlinePassedEmailGenerator.h"

void DeadlineChecker::run()
{
    qDebug() << "DeadlineChecker";
    ConfigParser settings;
    QSharedPointer<MySQLHandler> db = MySQLHandler::getInstance();
        QList<QSharedPointer<Task> > tasks = TaskDao::getOverdueTasks(db);
        foreach(QSharedPointer<Task> task, tasks) {
            qDebug() << "Task " << task->id() << " is pass its deadline of " << QString::fromStdString(task->deadline());
            QSharedPointer<User> translator = TaskDao::getUserClaimedTask(db, task->id());

            QList<QSharedPointer<User> > users = TaskDao::getSubscribedUsers(db, task->id());
            foreach(QSharedPointer<User> user, users) {
                OrgDeadlinePassedMailGenerator::run(user->id(), task->id());
            }

            if(!translator.isNull()) {
                UserTaskDeadlineEmailGenerator::run(task->id(), translator->id());
            }
        }

        tasks = TaskDao::getEarlyWarningTasks(db);
        foreach(QSharedPointer<Task> task, tasks) {
            qDebug() << "Task " << task->id() << " is within a week of its deadline of " << QString::fromStdString(task->deadline());
            QSharedPointer<User> translator = TaskDao::getUserClaimedTask(db, task->id());

            if(!translator.isNull()) {
                UserClaimedTaskEarlyWarningDeadlinePassedEmailGenerator::run(task->id(), translator->id());
            }

            TaskDao::taskNotificationSentInsertAndUpdate(db, task->id(), 1);
            qDebug() << "DeadlineChecker::Task early warning email queued";
        }

        tasks = TaskDao::getLateWarningTasks(db);
        foreach(QSharedPointer<Task> task, tasks) {
            qDebug() << "Task " << task->id() << " is a week late on its deadline of " << QString::fromStdString(task->deadline());
            QSharedPointer<User> translator = TaskDao::getUserClaimedTask(db, task->id());

            if(!translator.isNull()) {
                UserClaimedTaskLateWarningDeadlinePassedEmailGenerator::run(task->id(), translator->id());
            }

            TaskDao::taskNotificationSentInsertAndUpdate(db, task->id(), 2);
            qDebug() << "DeadlineChecker::Task late warning email queued";
        }

        QList<QSharedPointer<User> > users = UserDao::getRecordWarningUsers(db);
        foreach (QSharedPointer<User> user, users) {
            qDebug() << "User " << user->id() << " will be deleted in 168+ hours";
            UserRecordWarningDeadlinePassedEmailGenerator::run(user->id());
        }
}
