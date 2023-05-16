#include "EmailVerificationGenerator.h"

static void EmailVerificationGenerator::run(int user_id)
{
    qDebug() << "EmailVerificationGenerator user_id:" << user_id;

    ConfigParser settings;
    QString error = "";
    QString uniqueId = "";
    QSharedPointer<User> user = QSharedPointer<User>();
    QSharedPointer<MySQLHandler> db = MySQLHandler::getInstance();

    uniqueId = UserDao::getRegistrationId(db, user_id);
    user = UserDao::getUser(db, user_id);

    if (uniqueId == "" || user.isNull()) {
        error = "EmailVerificationGenerator - Unable to find user data for user "
                + QString::number(user_id);
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

        UserDao::queue_email(db, user_id, QString::fromStdString(user->email()), settings.get("site.name") + ": Your email verification", QString::fromUtf8(email_body.c_str()));
        UserDao::log_email_sent(db, user_id, 0, 0, 0, 0, 0, 0, "email_verification_to_volunteer");
    } else {
        IEmailGenerator::generateErrorEmail(error);
    }
}
