#include "emailplugin.h"

#include <QDebug>
#include <QTimer>

#include <qxt/QxtNetwork/qxtmailmessage.h>
#include <qxt/QxtNetwork/qxtsmtp.h>

#include "Smtp.h"
#include "EmailGenerator.h"
#include "Common/protobufs/emails/TaskScoreEmail.pb.h"
#include "Common/protobufs/emails/OrgMembershipAccepted.pb.h"
#include "Common/protobufs/emails/OrgMembershipRefused.pb.h"
#include "Common/protobufs/emails/PasswordReset.pb.h"
#include "Common/protobufs/emails/TaskArchived.pb.h"
#include "Common/protobufs/emails/TaskClaimed.pb.h"
#include "Common/protobufs/emails/TaskTranslationUploaded.pb.h"
#include "Common/protobufs/emails/UserTaskClaim.pb.h"

#include "Common/MessagingClient.h"

Q_EXPORT_PLUGIN2(EmailPlugin, EmailPlugin)

EmailPlugin::EmailPlugin()
{
}

void EmailPlugin::run()
{
    qDebug() << "EmailPlugin::Starting new Thread " << this->thread()->currentThreadId();
    QString exchange = "SOLAS_MATCH";
    QString topic = "email.#";
    QString queue = "email_queue";
    MessagingClient *client;

    client = new MessagingClient();
    client->init();
    connect(client, SIGNAL(AMQPMessageReceived(AMQPMessage*)), this, SLOT(messageReveived(AMQPMessage*)));

    try {
        qDebug() << "EmailPlugin::Now consuming from " << exchange << " exchange";
        client->declareQueue(exchange, topic, queue);

        QTimer *message_queue_read_timer = new QTimer();
        connect(message_queue_read_timer, SIGNAL(timeout()), client, SLOT(consumeFromQueue()));
        message_queue_read_timer->start(50);
    } catch(AMQPException e) {
        qDebug() << "ERROR: " << QString::fromStdString(e.getMessage());
    }
}

void EmailPlugin::messageReveived(AMQPMessage *message)
{
    qDebug() << "Received Message";

    uint32_t length = 0;
    QString message_body = message->getMessage(&length);

    EmailMessage email_message;
    email_message.ParseFromString(message_body.toStdString());

    EmailGenerator emailGen;
    Email *email =  NULL;

    switch (email_message.email_type()) {
        case (EmailMessage::TaskScoreEmail) :
        {
            TaskScoreEmail email_type;
            email_type.ParseFromString(message_body.toStdString());

            email = emailGen.generateEmail(email_type);
            break;
        }
        case (EmailMessage::OrgMembershipAccepted):
        {
            OrgMembershipAccepted email_type;
            email_type.ParseFromString(message_body.toStdString());

            email = emailGen.generateEmail(email_type);
            break;
        }
        case (EmailMessage::OrgMembershipRefused):
        {
            OrgMembershipRefused email_type;
            email_type.ParseFromString(message_body.toStdString());

            email = emailGen.generateEmail(email_type);
            break;
        }
        case (EmailMessage::PasswordReset):
        {
            PasswordReset email_type;
            email_type.ParseFromString(message_body.toStdString());

            email = emailGen.generateEmail(email_type);
            break;
        }
        case (EmailMessage::TaskArchived):
        {
            TaskArchived email_type;
            email_type.ParseFromString(message_body.toStdString());

            email = emailGen.generateEmail(email_type);
            break;
        }
        case (EmailMessage::TaskClaimed):
        {
            TaskClaimed email_type;
            email_type.ParseFromString(message_body.toStdString());

            email = emailGen.generateEmail(email_type);
            break;
        }
        case (EmailMessage::TaskTranslationUploaded):
        {
            TaskTranslationUploaded email_type;
            email_type.ParseFromString(message_body.toStdString());

            email = emailGen.generateEmail(email_type);
            break;
        }
        case (EmailMessage::UserTaskClaim):
        {
            UserTaskClaim email_type;
            email_type.ParseFromString(message_body.toStdString());

            email = emailGen.generateEmail(email_type);
            break;
        }
        default:
        {
            qDebug() << "Invalid email type";
            break;
        }
    }

    if(email) {
        //Send Email
        smtp = new Smtp(email);
        connect(smtp, SIGNAL(complete()), this, SLOT(deleteSmtp()));
        delete email;

        //Ack message
        AMQPQueue *messageQueue = message->getQueue();
        if(messageQueue != NULL)
        {
            messageQueue->Ack(message->getDeliveryTag());
        }
    }
}

void EmailPlugin::deleteSmtp()
{
    qDebug() << "Deleting SMTP";
    delete smtp;
}

void EmailPlugin::setThreadPool(QThreadPool *tp)
{
    this->mThreadPool = tp;
}
