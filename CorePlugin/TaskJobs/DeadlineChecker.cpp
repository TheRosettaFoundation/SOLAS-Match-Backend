#include "DeadlineChecker.h"

#include <QDebug>
#include <QThread>
#include <QDateTime>

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
    qDebug() << "Starting new thread to check deadlines " << this->thread()->currentThreadId();
    ConfigParser settings;
    QString exchange = settings.get("messaging.exchange");
    QSharedPointer<MySQLHandler> db = MySQLHandler::getInstance();
    MessagingClient client;
    if(client.init()) {
        QList<QSharedPointer<Task> > tasks = TaskDao::getOverdueTasks(db);
        foreach(QSharedPointer<Task> task, tasks) {
            qDebug() << "Task " << task->id() << " is pass its deadline of " << QString::fromStdString(task->deadline());
            QSharedPointer<User> translator = TaskDao::getTaskTranslator(db, task->id());

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
                }

                client.publish(exchange, "email.org.task.deadline",
                               QString::fromStdString(orgEmail.SerializeAsString()));
            }

            if(!translator.isNull()) {
                UserClaimedTaskDeadlinePassed userEmail;
                userEmail.set_email_type(EmailMessage::UserClaimedTaskDeadlinePassed);
                userEmail.set_task_id(task->id());
                userEmail.set_translator_id(translator->id());

                client.publish(exchange, "email.user.deadline.passed",
                               QString::fromStdString(userEmail.SerializeAsString()));
            }

            qDebug() << "DeadlineChecker::Finished processing task, unpublishing it now";
            task->set_published(false);
            TaskDao::insertAndUpdate(db, task);
        }
    } else {
        qDebug() << "Unable to connect to RabbitMQ. Check conf.ini for settings.";
    }
}
