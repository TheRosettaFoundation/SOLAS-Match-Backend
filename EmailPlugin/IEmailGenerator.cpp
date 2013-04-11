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
