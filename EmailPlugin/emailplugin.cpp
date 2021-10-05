#include "emailplugin.h"

#include <QDebug>
#include <QTimer>

#include "qxtmailmessage.h"
#include "qxtsmtp.h"

#include "Generators/TaskScoreEmailGenerator.h"
#include "Generators/OrgDeadlinePassedEmailGenerator.h"
#include "Generators/OrgMembershipAcceptedGenerator.h"
#include "Generators/OrgMembershipRefusedEmailGenerator.h"
#include "Generators/PasswordResetEmailGenerator.h"
#include "Generators/TaskArchivedEmailGenerator.h"
#include "Generators/TaskClaimedEmailGenerator.h"
#include "Generators/UserTaskClaimEmailGenerator.h"
#include "Generators/UserTaskDeadlineEmailGenerator.h"
#include "Generators/UserClaimedTaskEarlyWarningDeadlinePassedEmailGenerator.h"
#include "Generators/UserClaimedTaskLateWarningDeadlinePassedEmailGenerator.h"
#include "Generators/UserRecordWarningDeadlinePassedEmailGenerator.h"
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
#include "Generators/UserBadgeAwardedGenerator.h"
#include "Generators/UserTaskRevokedGenerator.h"
#include "Generators/OrgTaskRevokedGenerator.h"
#include "Generators/ProjectCreatedGenerator.h"
#include "Generators/NewImageUploadedEmailGenerator.h"
#include "Generators/ProjectImageRemovedEmailGenerator.h"
#include "Generators/NewImageUploadedEmailGenerator.h"
#include "Generators/ProjectImageApprovedEmailGenerator.h"
#include "Generators/ProjectImageDisapprovedEmailGenerator.h"

#include "Smtp.h"
#include "IEmailGenerator.h"
#include "Common/ConfigParser.h"

#include "Common/MessagingClient.h"

#include "Common/protobufs/emails/JSON.h"

using namespace SolasMatch::Common::Protobufs::Emails;

//QT4.8 (see Q_PLUGIN_METADATA for QT5) Q_EXPORT_PLUGIN2(EmailPlugin, EmailPlugin)

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
    char *body = message->getMessage(&length);

  if (JSON::isJSON(std::string(body, length))) {
    JSON email_message;
    email_message.ParseFromString(std::string(body, length));

    QString type = "EmailGenerator_" + QString::number(email_message.email_type());
    int classId = QMetaType::type(type.toLatin1());
    if (classId == 0) {
        qDebug() << "EmailGenerator JSON: Invalid proto type: " << QString::number(email_message.email_type());
    } else {
        IEmailGenerator *emailGen = static_cast<IEmailGenerator *>(QMetaType::create(classId));
        emailGen->setEmailQueue(smtp->getEmailQueue());
        emailGen->setProtoBody(std::string(body, length));
        emailGen->setAMQPMessage(message);
        this->mThreadPool->start(emailGen);
    }
  } else {
    EmailMessage email_message;
    email_message.ParseFromString(std::string(body, length));

    QString type = "EmailGenerator_" + QString::number(email_message.email_type());
    int classId = QMetaType::type(type.toLatin1());
    if (classId == 0) {
        qDebug() << "EmailGenerator: Invalid proto type: " << QString::number(email_message.email_type());
    } else {
        IEmailGenerator *emailGen = static_cast<IEmailGenerator *>(QMetaType::create(classId));
        emailGen->setEmailQueue(smtp->getEmailQueue());
        emailGen->setProtoBody(std::string(body, length));
        emailGen->setAMQPMessage(message);
        this->mThreadPool->start(emailGen);
    }
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
    name = "EmailGenerator_" + QString::number(EmailMessage::UserClaimedTaskEarlyWarningDeadlinePassed);
    qRegisterMetaType<UserClaimedTaskEarlyWarningDeadlinePassedEmailGenerator>(name.toLatin1());
    name = "EmailGenerator_" + QString::number(EmailMessage::UserClaimedTaskLateWarningDeadlinePassed);
    qRegisterMetaType<UserClaimedTaskLateWarningDeadlinePassedEmailGenerator>(name.toLatin1());
    name = "EmailGenerator_" + QString::number(EmailMessage::UserRecordWarningDeadlinePassed);
    qRegisterMetaType<UserRecordWarningDeadlinePassedEmailGenerator>(name.toLatin1());
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
    name = "EmailGenerator_" + QString::number(EmailMessage::UserBadgeAwardedEmail);
    qRegisterMetaType<UserBadgeAwardedGenerator>(name.toLatin1());
    name = "EmailGenerator_" + QString::number(EmailMessage::UserTaskRevokedEmail);
    qRegisterMetaType<UserTaskRevokedGenerator>(name.toLatin1());
    name = "EmailGenerator_" + QString::number(EmailMessage::OrgTaskRevokedEmail);
    qRegisterMetaType<OrgTaskRevokedGenerator>(name.toLatin1());
    name = "EmailGenerator_" + QString::number(EmailMessage::ProjectCreated);
    qRegisterMetaType<ProjectCreatedGenerator>(name.toLatin1());
    name = "EmailGenerator_" + QString::number(EmailMessage::ProjectImageUploadedEmail);
    qRegisterMetaType<NewImageUploadedEmailGenerator>(name.toLatin1());
    name = "EmailGenerator_" + QString::number(EmailMessage::ProjectImageRemovedEmail);
    qRegisterMetaType<ProjectImageRemovedEmailGenerator>(name.toLatin1());
    name = "EmailGenerator_" + QString::number(EmailMessage::ProjectImageApprovedEmail);
    qRegisterMetaType<ProjectImageApprovedEmailGenerator>(name.toLatin1());
    name = "EmailGenerator_" + QString::number(EmailMessage::ProjectImageDisapprovedEmail);
    qRegisterMetaType<ProjectImageDisapprovedEmailGenerator>(name.toLatin1());
}

void EmailPlugin::setThreadPool(QThreadPool *tp)
{
    this->mThreadPool = tp;
}

bool EmailPlugin::isEnabled()
{
    return enabled;
}
