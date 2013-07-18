#include "emailplugin.h"

#include <QDebug>
#include <QTimer>

#include <qxt/QxtNetwork/qxtmailmessage.h>
#include <qxt/QxtNetwork/qxtsmtp.h>

#include "Generators/TaskScoreEmailGenerator.h"
#include "Generators/OrgDeadlinePassedEmailGenerator.h"
#include "Generators/OrgMembershipAcceptedGenerator.h"
#include "Generators/OrgMembershipRefusedEmailGenerator.h"
#include "Generators/PasswordResetEmailGenerator.h"
#include "Generators/TaskArchivedEmailGenerator.h"
#include "Generators/TaskClaimedEmailGenerator.h"
#include "Generators/UserTaskClaimEmailGenerator.h"
#include "Generators/UserTaskDeadlineEmailGenerator.h"
#include "Generators/OrgFeedbackGenerator.h"
#include "Generators/UserFeedbackGenerator.h"
#include "Generators/UserTaskStreamEmailGenerator.h"
#include "Generators/TrackedTaskUploadedEmailGenerator.h"
#include "Generators/EmailVerificationGenerator.h"
#include "Generators/BannedLoginGenerator.h"
#include "Generators/ClaimedTaskSourceUpdatedGenerator.h"
#include "Generators/ClaimedTaskUploadedGenerator.h"
#include "Generators/OrgCreated_OrgEmail.h"
#include "Generators/OrgCreated_SiteAdmin.h"
#include "Generators/UserReferenceEmailGenerator.h"

#include "Smtp.h"
#include "IEmailGenerator.h"
#include "Common/ConfigParser.h"

#include "Common/MessagingClient.h"

Q_EXPORT_PLUGIN2(EmailPlugin, EmailPlugin)

EmailPlugin::EmailPlugin()
{
    ConfigParser settings;
    enabled = (QString::compare("y", settings.get("mail.enabled")) == 0);
}

void EmailPlugin::run()
{
    qDebug() << "EmailPlugin::Starting new Thread " << this->thread()->currentThreadId();
    ConfigParser settings;
    QString exchange = settings.get("messaging.exchange");
    QString topic = "email.#";
    QString queue = "email_queue";
    MessagingClient *client;

    this->registerEmailTypes();

    smtp = new Smtp();

    client = new MessagingClient();
    client->init();
    connect(client, SIGNAL(AMQPMessageReceived(AMQPMessage*)), this, SLOT(messageReveived(AMQPMessage*)));

    qDebug() << "EmailPlugin::Now consuming from " << exchange << " exchange";
    client->declareQueue(exchange, topic, queue);

    QTimer *message_queue_read_timer = new QTimer();
    connect(message_queue_read_timer, SIGNAL(timeout()), client, SLOT(consumeFromQueue()));
    message_queue_read_timer->start(settings.get("messaging.poll_rate").toInt());
}

void EmailPlugin::messageReveived(AMQPMessage *message)
{
    qDebug() << "EmailPlugin::Received Message";

    AMQPQueue *messageQueue = message->getQueue();
    if(messageQueue != NULL)
    {
        messageQueue->Ack(message->getDeliveryTag());
    }

    uint32_t length = 0;
    QString message_body = message->getMessage(&length);

    EmailMessage email_message;
    email_message.ParseFromString(message_body.toStdString());

    QString type = "EmailGenerator_" + QString::number(email_message.email_type());
    int classId = QMetaType::type(type.toLatin1());
    if (classId == 0) {
        qDebug() << "EmailGenerator: Invalid proto type: " << QString::number(email_message.email_type());
    } else {
        IEmailGenerator *emailGen = static_cast<IEmailGenerator *>(QMetaType::construct(classId));
        emailGen->setEmailQueue(smtp->getEmailQueue());
        emailGen->setProtoBody(message_body);
        emailGen->setAMQPMessage(message);
        this->mThreadPool->start(emailGen);
    }
}

void EmailPlugin::registerEmailTypes()
{
    QString name = "";
    name = "EmailGenerator_" + QString::number(EmailMessage::TaskScoreEmail);
    qRegisterMetaType<TaskScoreEmailGenerator>(name.toLatin1());
    name = "EmailGenerator_" + QString::number(EmailMessage::OrgMembershipAccepted);
    qRegisterMetaType<OrgMembershipAcceptedGenerator>(name.toLatin1());
    name = "EmailGenerator_" + QString::number(EmailMessage::OrgMembershipRefused);
    qRegisterMetaType<OrgMembershipRefusedEmailGenerator>(name.toLatin1());
    name = "EmailGenerator_" + QString::number(EmailMessage::PasswordResetEmail);
    qRegisterMetaType<PasswordResetEmailGenerator>(name.toLatin1());
    name = "EmailGenerator_" + QString::number(EmailMessage::TaskArchived);
    qRegisterMetaType<TaskArchivedEmailGenerator>(name.toLatin1());
    name = "EmailGenerator_" + QString::number(EmailMessage::TrackedTaskUploaded);
    qRegisterMetaType<TrackedTaskUploadedEmailGenerator>(name.toLatin1());
    name = "EmailGenerator_" + QString::number(EmailMessage::TaskClaimed);
    qRegisterMetaType<TaskClaimedEmailGenerator>(name.toLatin1());
    name = "EmailGenerator_" + QString::number(EmailMessage::UserTaskClaim);
    qRegisterMetaType<UserTaskClaimEmailGenerator>(name.toLatin1());
    name = "EmailGenerator_" + QString::number(EmailMessage::OrgTaskDeadlinePassed);
    qRegisterMetaType<OrgDeadlinePassedMailGenerator>(name.toLatin1());
    name = "EmailGenerator_" + QString::number(EmailMessage::UserClaimedTaskDeadlinePassed);
    qRegisterMetaType<UserTaskDeadlineEmailGenerator>(name.toLatin1());
    name = "EmailGenerator_" + QString::number(EmailMessage::UserTaskStreamEmail);
    qRegisterMetaType<UserTaskStreamEmailGenerator>(name.toLatin1());
    name = "EmailGenerator_" + QString::number(EmailMessage::EmailVerification);
    qRegisterMetaType<EmailVerificationGenerator>(name.toLatin1());
    name = "EmailGenerator_" + QString::number(EmailMessage::BannedLogin);
    qRegisterMetaType<BannedLoginGenerator>(name.toLatin1());
    name = "EmailGenerator_" + QString::number(EmailMessage::ClaimedTaskSourceUpdated);
    qRegisterMetaType<ClaimedTaskSourceUpdatedGenerator>(name.toLatin1());
    name = "EmailGenerator_" + QString::number(EmailMessage::ClaimedTaskUploaded);
    qRegisterMetaType<ClaimedTaskUploadedGenerator>(name.toLatin1());
    name = "EmailGenerator_" + QString::number(EmailMessage::OrgFeedback);
    qRegisterMetaType<OrgFeedbackGenerator>(name.toLatin1());
    name = "EmailGenerator_" + QString::number(EmailMessage::UserFeedback);
    qRegisterMetaType<UserFeedbackGenerator>(name.toLatin1());
    name = "EmailGenerator_" + QString::number(EmailMessage::OrgCreatedSiteAdmin);
    qRegisterMetaType<OrgCreate_SiteAdmin>(name.toLatin1());
    name = "EmailGenerator_" + QString::number(EmailMessage::OrgCreatedOrgAdmin);
    qRegisterMetaType<OrgCreated_OrgEmail>(name.toLatin1());
    name = "EmailGenerator_" + QString::number(EmailMessage::UserReferenceEmail);
    qRegisterMetaType<UserReferenceEmailGenerator>(name.toLatin1());
}

void EmailPlugin::setThreadPool(QThreadPool *tp)
{
    this->mThreadPool = tp;
}

bool EmailPlugin::isEnabled()
{
    return enabled;
}
