#include "DeadlineChecker.h"

#include <QDebug>
#include <QThread>

#include "Common/MessagingClient.h"
#include "Common/ConfigParser.h"
#include "Common/DataAccessObjects/TaskDao.h"
#include "Common/DataAccessObjects/ProjectDao.h"
#include "Common/protobufs/models/Task.pb.h"
#include "Common/protobufs/models/Project.pb.h"
#include "Common/protobufs/requests/DeadlineCheckRequest.pb.h"
#include "Common/protobufs/emails/EmailMessage.pb.h"
#include "Common/protobufs/emails/OrgTaskDeadlinePassed.pb.h"
#include "Common/protobufs/emails/UserClaimedTaskDeadlinePassed.pb.h"
#include "Common/protobufs/emails/UserClaimedTaskEarlyWarningDeadlinePassed.pb.h"
#include "Common/protobufs/emails/UserClaimedTaskLateWarningDeadlinePassed.pb.h"

using namespace SolasMatch::Common::Protobufs::Emails;

DeadlineChecker::DeadlineChecker()
{
    //Default Constructor
}

DeadlineChecker::DeadlineChecker(AMQPMessage *mess)
{
    this->message = mess;
}

DeadlineChecker::~DeadlineChecker()
{
}

void DeadlineChecker::run()
{
    qDebug() << "Starting new thread to check deadlines";
    ConfigParser settings;
    QString exchange = settings.get("messaging.exchange");
    QSharedPointer<MySQLHandler> db = MySQLHandler::getInstance();
    MessagingClient client;
    if(client.init()) {
        QList<QSharedPointer<Task> > tasks = TaskDao::getOverdueTasks(db);
        foreach(QSharedPointer<Task> task, tasks) {
            qDebug() << "Task " << task->id() << " is pass its deadline of " << QString::fromStdString(task->deadline());
            QSharedPointer<User> translator = TaskDao::getUserClaimedTask(db, task->id());

            QList<QSharedPointer<User> > users = TaskDao::getSubscribedUsers(db, task->id());
            foreach(QSharedPointer<User> user, users) {

                QSharedPointer<Project> project = ProjectDao::getProject(db, task->projectid());

                OrgTaskDeadlinePassed orgEmail;
                orgEmail.set_email_type(EmailMessage::OrgTaskDeadlinePassed);
                orgEmail.set_user_id(user->id());
                orgEmail.set_org_id(project->organisationid());
                orgEmail.set_task_id(task->id());
                if(!translator.isNull()) {
                    orgEmail.set_translator_id(translator->id());

                    client.publish(exchange, "email.org.task.deadline", orgEmail.SerializeAsString());
                } else {
                    qDebug() << "Task " << task->id() << " has was not claimed so not sending OrgTaskDeadlinePassed";
                }
            }

            if(!translator.isNull()) {
                UserClaimedTaskDeadlinePassed userEmail;
                userEmail.set_email_type(EmailMessage::UserClaimedTaskDeadlinePassed);
                userEmail.set_task_id(task->id());
                userEmail.set_translator_id(translator->id());

                client.publish(exchange, "email.user.deadline.passed",
                               userEmail.SerializeAsString());
            }

            // https://github.com/TheRosettaFoundation/SOLAS-Match-Backend/issues/45
            // qDebug() << "DeadlineChecker::Finished processing task, unpublishing it now";
            // task->set_published(false);
            // TaskDao::insertAndUpdate(db, task);
        }

        tasks = TaskDao::getEarlyWarningTasks(db);
        foreach(QSharedPointer<Task> task, tasks) {
            qDebug() << "Task " << task->id() << " is within a week of its deadline of " << QString::fromStdString(task->deadline());
            QSharedPointer<User> translator = TaskDao::getUserClaimedTask(db, task->id());

            if(!translator.isNull()) {
                UserClaimedTaskEarlyWarningDeadlinePassed userEmail;
                userEmail.set_email_type(EmailMessage::UserClaimedTaskEarlyWarningDeadlinePassed);
                userEmail.set_task_id(task->id());
                userEmail.set_translator_id(translator->id());

                client.publish(exchange, "email.user.early.deadline.passed",
                               userEmail.SerializeAsString());
            }

            TaskDao::taskNotificationSentInsertAndUpdate(db, task->id(), 1);
            qDebug() << "DeadlineChecker::Task early warning email queued";
        }

        tasks = TaskDao::getLateWarningTasks(db);
        foreach(QSharedPointer<Task> task, tasks) {
            qDebug() << "Task " << task->id() << " is a week late on its deadline of " << QString::fromStdString(task->deadline());
            QSharedPointer<User> translator = TaskDao::getUserClaimedTask(db, task->id());

            if(!translator.isNull()) {
                UserClaimedTaskLateWarningDeadlinePassed userEmail;
                userEmail.set_email_type(EmailMessage::UserClaimedTaskLateWarningDeadlinePassed);
                userEmail.set_task_id(task->id());
                userEmail.set_translator_id(translator->id());

                client.publish(exchange, "email.user.late.deadline.passed",
                               userEmail.SerializeAsString());
            }

            TaskDao::taskNotificationSentInsertAndUpdate(db, task->id(), 2);
            qDebug() << "DeadlineChecker::Task late warning email queued";
        }
    } else {
        qDebug() << "Unable to connect to RabbitMQ. Check conf.ini for settings.";
    }
}

void DeadlineChecker::setAMQPMessage(AMQPMessage *message)
{
    this->message = message;
}
