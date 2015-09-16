#include "TaskScoreEmailGenerator.h"
using namespace  SolasMatch::Common::Protobufs::Emails;

void TaskScoreEmailGenerator::run()
{
    qDebug() << "EmailGenerator - Generating TaskScoreEmail";
    TaskScoreEmail email_message;
    email_message.ParseFromString(this->protoBody);

    QSharedPointer<Email> email = QSharedPointer<Email>(new Email());
    ConfigParser settings;

    QStringList admins = settings.get("mail.admin_emails").split(",");
    foreach(QString admin, admins) {
        email->addRecipient(admin.trimmed());
    }

    email->setSender(settings.get("site.system_email_address"));
    email->setSubject(settings.get("site.name") + ": User Task Score Results");
    email->setBody(QString::fromUtf8(email_message.body().c_str()));

    this->emailQueue->insert(email, currentMessage);
}
