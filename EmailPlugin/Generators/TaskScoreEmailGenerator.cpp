#include "TaskScoreEmailGenerator.h"

void TaskScoreEmailGenerator::run()
{
    qDebug() << "EmailGenerator - Generating TaskScoreEmail";
    TaskScoreEmail email_message;
    email_message.ParseFromString(this->protoBody.toStdString());

    QSharedPointer<Email> email = QSharedPointer<Email>(new Email());
    ConfigParser settings;

    QStringList admins = settings.get("mail.admin_emails").split(",");
    foreach(QString admin, admins) {
        email->addRecipient(admin.trimmed());
    }

    email->setSender(settings.get("site.system_email_address"));
    email->setSubject("User Task Score Results");
    email->setBody(QString::fromStdString(email_message.body()));
    this->emailQueue->enqueue(email);
}
