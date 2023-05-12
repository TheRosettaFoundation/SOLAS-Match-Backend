#include "SendTaskUploadNotifications.h"

#include <QDebug>

#include "Common/protobufs/models/Task.pb.h"
#include "Common/protobufs/models/User.pb.h"

#include "Common/DataAccessObjects/TaskDao.h"

#include "Common/MySQLHandler.h"

using namespace SolasMatch::Common::Protobufs::Requests;
using namespace SolasMatch::Common::Protobufs::Emails;
using namespace SolasMatch::Common::Protobufs::Models;

static void SendTaskUploadNotifications::run(int task_id)
{
    qDebug() << "SendTaskUploadNotifications task_id:" << task_id;

    QSharedPointer<MySQLHandler> db = MySQLHandler::getInstance();
    QSharedPointer<Task> task = TaskDao::getTask(db, task_id);

    if (!task.isNull()) {
        QList<QSharedPointer<User> > users = TaskDao::getSubscribedUsers(db, task->id());
        QSharedPointer<User> translator = TaskDao::getUserClaimedTask(db, task->id());

        std::string body = "";
        MessagingClient publisher;
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
                            TrackedTaskUploaded trackedUpload;
                            trackedUpload.set_email_type(trackedUpload.email_type());
                            trackedUpload.set_task_id(task->id());
                            trackedUpload.set_translator_id(translator->id());
                            trackedUpload.set_user_id(revisionClaimer->id());
                            body = trackedUpload.SerializeAsString();
                            publisher.publish(exchange, topic, body);
//qDebug() << "SendTaskUploadNotifications SENT TO revisionClaimer->id():" << QString::number(revisionClaimer->id());//(**)
                        }
                    }
                }

                foreach (QSharedPointer<User> user, users) {
                    TrackedTaskUploaded trackedUpload;
                    trackedUpload.set_email_type(trackedUpload.email_type());
                    trackedUpload.set_task_id(task->id());
                    trackedUpload.set_translator_id(translator->id());
                    trackedUpload.set_user_id(user->id());
                    body = trackedUpload.SerializeAsString();
                    publisher.publish(exchange, topic, body);
//qDebug() << "SendTaskUploadNotifications SENT TO tracker/admin user->id():" << QString::number(user->id());//(**)
                }

                ClaimedTaskUploaded claimedUpload;
                claimedUpload.set_email_type(claimedUpload.email_type());
                claimedUpload.set_task_id(task->id());
                claimedUpload.set_user_id(translator->id());
                body = claimedUpload.SerializeAsString();
                publisher.publish(exchange, topic, body);
            }
        }
    } else {
        qDebug() << "SendTaskUploadNotifications: Unable to find relevant data in the DB, "
                 << "Searched for task ID " << QString::number(task_id);
    }
}
