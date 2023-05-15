#include "SendTaskUploadNotifications.h"

#include <QDebug>

#include "Common/protobufs/models/Task.pb.h"
#include "Common/protobufs/models/User.pb.h"

#include "Common/DataAccessObjects/TaskDao.h"

#include "Common/MySQLHandler.h"

using namespace SolasMatch::Common::Protobufs::Models;

static void SendTaskUploadNotifications::run(int task_id)
{
    qDebug() << "SendTaskUploadNotifications task_id:" << QString::number(task_id);

    QSharedPointer<MySQLHandler> db = MySQLHandler::getInstance();
    QSharedPointer<Task> task = TaskDao::getTask(db, task_id);

    if (!task.isNull()) {
        QList<QSharedPointer<User> > users = TaskDao::getSubscribedUsers(db, task->id());
        QSharedPointer<User> translator = TaskDao::getUserClaimedTask(db, task->id());

        QMap<QString, QVariant> memsource_task = TaskDao::get_memsource_task(db, task->id());
        if (!memsource_task.isEmpty()) {
            if (!translator.isNull()) {
                // These are any tasks with a higher workflow...
                QList<QSharedPointer<Task> > revision_tasks = TaskDao::get_matching_revision_memsource_tasks(db, task);
                foreach (QSharedPointer<Task> revision_task, revision_tasks) {
//qDebug() << "SendTaskUploadNotifications Matching Revision Task:" << QString::number(revision_task->id());//(**)
                    if (TaskDao::is_task_translated_in_memsource(db, revision_task)) { // Only notify if all prerequisite tasks are translated
//qDebug() << "SendTaskUploadNotifications Matching Revision Task IS TRANSLATED:" << QString::number(revision_task->id());//(**)
                        QSharedPointer<User> revisionClaimer = TaskDao::getUserClaimedTask(db, revision_task->id());
                        if (!revisionClaimer.isNull()) {
                            TrackedTaskUploadedEmailGenerator::run(revisionClaimer->id(), task->id(), translator->id());
//qDebug() << "SendTaskUploadNotifications SENT TO revisionClaimer->id():" << QString::number(revisionClaimer->id());//(**)
                        }
                    }
                }

                foreach (QSharedPointer<User> user, users) {
                    TrackedTaskUploadedEmailGenerator::run(user->id(), task->id(), translator->id());
//qDebug() << "SendTaskUploadNotifications SENT TO tracker/admin user->id():" << QString::number(user->id());//(**)
                }

                ClaimedTaskUploadedGenerator::run(task->id(), translator->id());
                publisher.publish(exchange, topic, body);
            }
        }
    } else {
        qDebug() << "SendTaskUploadNotifications: Unable to find relevant data in the DB, "
                 << "Searched for task ID " << QString::number(task_id);
    }
}
