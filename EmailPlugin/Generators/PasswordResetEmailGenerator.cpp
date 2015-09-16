#include "PasswordResetEmailGenerator.h"
using namespace  SolasMatch::Common::Protobufs::Emails;

PasswordResetEmailGenerator::PasswordResetEmailGenerator()
{
    //Default Constructor
}

void PasswordResetEmailGenerator::run()
{
    qDebug() << "EmailGenerator - Generating PasswordResetEmail";

    PasswordResetEmail email_message;
    email_message.ParseFromString(this->protoBody);

    ConfigParser settings;
    QSharedPointer<Email> email = QSharedPointer<Email>(new Email());
    QString uuid = "";
    QString error = "";
    QSharedPointer<User> user = QSharedPointer<User>();
    QSharedPointer<MySQLHandler> db = MySQLHandler::getInstance();

    user = UserDao::getUser(db, email_message.user_id());

    if(user.isNull()) {
        error = "Password Reset email generation failed. Unable to find ";
        error += "data in the DB. Looking for user id " + QString::number(email_message.user_id());
    } else {
        uuid = UserDao::getPasswordResetUuid(db, QString::fromStdString(user->email()));

        if (uuid.compare("") == 0) {
            error = "Password Reset email generation failed. Unable to find ";
            error += " uuid in the db, searched by email " + QString::fromStdString(user->email());
        }
    }

    if(error.compare("") == 0) {
        QString page_url = settings.get("site.url");
        page_url += uuid;
        page_url += "/password/reset";

        ctemplate::TemplateDictionary dict("password_reset");
        if(user->display_name() != "") {
            dict.ShowSection("USER_HAS_NAME");
            dict.SetValue("USERNAME", user->display_name());
        } else {
            dict.ShowSection("NO_USER_NAME");
        }
        dict.SetValue("URL", page_url.toStdString());
        dict.SetValue("SITE_NAME", settings.get("site.name").toStdString());
        std::string email_body;
        QString template_location = QString(TEMPLATE_DIRECTORY) + "emails/password-reset.tpl";
        ctemplate::ExpandTemplate(template_location.toStdString(), ctemplate::DO_NOT_STRIP, &dict, &email_body);

        email->setSender(settings.get("site.system_email_address"));
        email->addRecipient(QString::fromStdString(user->email()));
        email->setSubject(settings.get("site.name") + ": Password Reset");
        email->setBody(QString::fromUtf8(email_body.c_str()));
    } else {
        email = this->generateErrorEmail(error);
    }

    this->emailQueue->insert(email, currentMessage);
}
