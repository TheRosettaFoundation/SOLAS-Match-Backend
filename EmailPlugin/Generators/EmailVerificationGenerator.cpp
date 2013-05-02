#include "EmailVerificationGenerator.h"

EmailVerificationGenerator::EmailVerificationGenerator()
{
    // Default Constructor
}

void EmailVerificationGenerator::run()
{
    qDebug() << "EmailGenerator::Generating Email Verification email";

    EmailVerification emailMessage;
    emailMessage.ParseFromString(this->protoBody.toStdString());

    ConfigParser settings;
    QString error = "";
    QString uniqueId = "";
    QSharedPointer<User> user = QSharedPointer<User>();
    QSharedPointer<Email> email = QSharedPointer<Email>(new Email);
    QSharedPointer<MySQLHandler> db = MySQLHandler::getInstance();

    uniqueId = UserDao::getRegistrationId(db, emailMessage.user_id());
    user = UserDao::getUser(db, emailMessage.user_id());

    qDebug() << "Unique ID is " << uniqueId;

    if (uniqueId == "" || user.isNull()) {
        error = "EmailVerificationGenerator - Unable to find user data for user "
                + QString::number(emailMessage.user_id());
    } else {
        qDebug() << "uniqueId is not \"\"";
        qDebug() << "uniqueId is " << uniqueId;
    }

    if (error == "") {
        ctemplate::TemplateDictionary dict("registrationEmail");
        QString url = settings.get("site.url");
        url += "user/" + uniqueId + "/verification";
        dict["URL"] = url.toStdString();

        std::string email_body;
        QString template_location = QString(TEMPLATE_DIRECTORY) + "emails/registration-email.tpl";
        ctemplate::ExpandTemplate(template_location.toStdString(), ctemplate::DO_NOT_STRIP, &dict, &email_body);

        email->setSender(settings.get("site.system_email_address"));;
        email->addRecipient(QString::fromStdString(user->email()));
        email->setSubject("SOLAS Match - Registration");
        email->setBody(QString::fromStdString(email_body));
    } else {
        email = this->generateErrorEmail(error);
    }

    this->emailQueue->insert(email, currentMessage);
}
