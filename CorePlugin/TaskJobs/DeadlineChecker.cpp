#include "DeadlineChecker.h"

#include <QDebug>
#include <QThread>

#include "Common/ConfigParser.h"
#include "Common/DataAccessObjects/TaskDao.h"
#include "Common/DataAccessObjects/ProjectDao.h"
#include "Common/DataAccessObjects/UserDao.h"
#include "Common/protobufs/models/Task.pb.h"
#include "Common/protobufs/models/Project.pb.h"

using namespace SolasMatch::Common::Protobufs::Emails;

static void DeadlineChecker::run()
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

                QSharedPointer<Project> project = ProjectDao::getProject(db, task->projectid());

                int translator_id = 0;
                if(!translator.isNull()) {
                    translator_id = translator->id();
                }
                OrgDeadlinePassedMailGenerator::run(user->id(), project->organisationid(), task->id(), translator_id);
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

OrgDeadlinePassedMailGenerator::run(int user_id, int org_id, int task_id, int translator_id);

UserTaskDeadlineEmailGenerator::run(int task_id, int translator_id);

UserClaimedTaskEarlyWarningDeadlinePassedEmailGenerator::run(int task_id, int translator_id);
UserClaimedTaskLateWarningDeadlinePassedEmailGenerator::run(int task_id, int translator_id);

UserRecordWarningDeadlinePassedEmailGenerator::run(int user_id);
