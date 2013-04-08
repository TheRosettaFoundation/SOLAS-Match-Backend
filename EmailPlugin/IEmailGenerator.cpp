#include "IEmailGenerator.h"

#include <QDebug>
#include <QStringList>
#include <QUuid>
#include <ctemplate/template.h>

#include "Common/MySQLHandler.h"
#include "Common/ConfigParser.h"
#include "Common/MessagingClient.h"

#include "Common/DataAccessObjects/UserDao.h"
#include "Common/DataAccessObjects/OrganisationDao.h"
#include "Common/DataAccessObjects/TaskDao.h"
#include "Common/DataAccessObjects/ProjectDao.h"

#include "Common/protobufs/models/User.pb.h"
#include "Common/protobufs/models/Task.pb.h"
#include "Common/protobufs/models/Project.pb.h"
#include "Common/protobufs/models/ArchivedTask.pb.h"
#include "Common/protobufs/models/Organisation.pb.h"

#define TEMPLATE_DIRECTORY "/etc/SOLAS-Match/templates/"

IEmailGenerator::IEmailGenerator()
{
    //Default Constructor
}

void IEmailGenerator::setEmailQueue(QSharedPointer<EmailQueue> emailQueue)
{
    this->emailQueue = emailQueue;
}

void IEmailGenerator::setProtoBody(QString proto)
{
    this->protoBody = proto;
}

void IEmailGenerator::setAMQPMessage(AMQPMessage *mess)
{
    this->currentMessage = mess;
}

QSharedPointer<Email> IEmailGenerator::generateErrorEmail(QString error)
{
    ConfigParser settings;
    QSharedPointer<Email> email = QSharedPointer<Email>(new Email());

    email->setSender(settings.get("site.system_email_address"));
    QStringList admins = settings.get("mail.admin_emails").split(",");
    foreach(QString admin, admins) {
        email->addRecipient(admin.trimmed());
    }
    email->setSubject("An error has occurred");

    QString body = "<p>Hello,</p><p>An error has occurred in the SOLAS-Match worker Daemon. ";
    body += error + "</p>";
    email->setBody(body);

    return email;
}

/*
QSharedPointer<Email> EmailGenerator::generateEmail(UserClaimedTaskDeadlinePassed email_message)
{
    ConfigParser settings;
    QString error = "";
    QSharedPointer<Email> email = QSharedPointer<Email>(new Email);
    QSharedPointer<User> user = QSharedPointer<User>();
    QSharedPointer<Task> task = QSharedPointer<Task>();
    MySQLHandler* db = new MySQLHandler(QUuid::createUuid().toString());

    if(db->init()) {
        user = UserDao::getUser(db, email_message.translator_id());
        task = TaskDao::getTask(db, email_message.task_id());

        if(!user || !task) {
            error = "Failed to generate UserClaimedTaskDeadlinePassed email: Unable to find relevant ";
            error += "data in the Database. Searched for User ID ";
            error += QString::number(email_message.translator_id()) + " and Task ID ";
            error += QString::number(email_message.task_id()) + ".";
        }
    } else {
        error = "Failed to generate user UserClaimedTaskDeadlinePassed: Unable to Connect to SQL Server.";
        error += " Check conf.ini for connection settings and make sure mysqld has been started.";
        qDebug() << "Unable to Connect to SQL Server. Check conf.ini and try again.";
    }

    if(error.compare("") == 0) {
        ctemplate::TemplateDictionary dict("user_claimed_task_deadline_exceeded");
        if(user->display_name() != "") {
            dict.ShowSection("USER_HAS_NAME");
            dict["USERNAME"] = user->display_name();
        } else {
            dict.ShowSection("NO_USER_NAME");
        }
        dict["TASK_TITLE"] = task->title();

        std::string email_body;
        QString template_location = QString(TEMPLATE_DIRECTORY) + "emails/user-claimed-task-deadline-passed.tpl";
        ctemplate::ExpandTemplate(template_location.toStdString(), ctemplate::DO_NOT_STRIP, &dict, &email_body);

        email->setSender(settings.get("site.system_email_address"));;
        email->addRecipient(QString::fromStdString(user->email()));
        email->setSubject("Task Claim Notification");
        email->setBody(QString::fromStdString(email_body));
    } else {
        email = this->generateErrorEmail(error);
    }

    delete db;

    return email;
}
*/
