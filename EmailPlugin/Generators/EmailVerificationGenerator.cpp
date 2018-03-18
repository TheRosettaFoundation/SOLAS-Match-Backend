#include "EmailVerificationGenerator.h"
using namespace  SolasMatch::Common::Protobufs::Emails;

EmailVerificationGenerator::EmailVerificationGenerator()
{
    // Default Constructor
}

void EmailVerificationGenerator::run()
{
    qDebug() << "EmailGenerator::Generating Email Verification email";

    EmailVerification emailMessage;
    emailMessage.ParseFromString(this->protoBody);

    ConfigParser settings;
    QString error = "";
    QString uniqueId = "";
    QSharedPointer<User> user = QSharedPointer<User>();
    QSharedPointer<Email> email = QSharedPointer<Email>(new Email);
    QSharedPointer<MySQLHandler> db = MySQLHandler::getInstance();

    uniqueId = UserDao::getRegistrationId(db, emailMessage.user_id());
    user = UserDao::getUser(db, emailMessage.user_id());

    if (uniqueId == "" || user.isNull()) {
        error = "EmailVerificationGenerator - Unable to find user data for user "
                + QString::number(emailMessage.user_id());
    }

    if (error == "") {
        ctemplate::TemplateDictionary dict("registrationEmail");
        QString url = settings.get("site.url");
        url += "user/" + uniqueId + "/verification";
        dict.SetValue("URL", url.toStdString());
        dict.SetValue("SITE_NAME", std::string(settings.get("site.name").toLatin1().constData(), settings.get("site.name").toLatin1().length()));

        std::string email_body;
        QString template_location = QString(TEMPLATE_DIRECTORY) + "emails/registration-email.tpl";
        ctemplate::ExpandTemplate(template_location.toStdString(), ctemplate::DO_NOT_STRIP, &dict, &email_body);

        email->setSender(settings.get("site.system_email_address"));;
        email->addRecipient(QString::fromStdString(user->email()));
        email->setSubject(settings.get("site.name") + " - Registration");
        email->setBody(QString::fromUtf8(email_body.c_str()));
    } else {
        email = this->generateErrorEmail(error);
    }

    this->emailQueue->insert(email, currentMessage);
}
