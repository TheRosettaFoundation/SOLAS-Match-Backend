#include "PasswordResetEmailGenerator.h"

void PasswordResetEmailGenerator::run(int user_id)
{
    qDebug() << "PasswordResetEmailGenerator user_id" << user_id;

    ConfigParser settings;
    QString uuid = "";
    QString error = "";
    QSharedPointer<User> user = QSharedPointer<User>();
    QSharedPointer<MySQLHandler> db = MySQLHandler::getInstance();

    user = UserDao::getUser(db, user_id);

    if(user.isNull()) {
        error = "Password Reset email generation failed. Unable to find ";
        error += "data in the DB. Looking for user id " + QString::number(user_id);
    } else {
        uuid = UserDao::get_password_reset_request_uuid(db, user_id);
        if (uuid.compare("") == 0) {
            error = "Password Reset email generation failed. Unable to find uuid in the db, searched by user_id " + QString::number(user_id);
        }
    }

    if(error.compare("") == 0) {
        QString page_url = settings.get("site.url");
        page_url += uuid;
        page_url += "/password/reset";

        ctemplate::TemplateDictionary dict("password_reset");
        if(user->display_name() != "") {
            dict.ShowSection("USER_HAS_NAME");
            dict.SetValue("USERNAME", Email::htmlspecialchars(user->display_name()));
        } else {
            dict.ShowSection("NO_USER_NAME");
        }
        dict.SetValue("URL", page_url.toStdString());
        dict.SetValue("SITE_NAME", std::string(settings.get("site.name").toLatin1().constData(), settings.get("site.name").toLatin1().length()));
        std::string email_body;
        QString template_location = QString(TEMPLATE_DIRECTORY) + "emails/password-reset.tpl";
        ctemplate::ExpandTemplate(template_location.toStdString(), ctemplate::DO_NOT_STRIP, &dict, &email_body);

        UserDao::queue_email(db, user_id, QString::fromStdString(user->email()), settings.get("site.name") + ": Password Reset", QString::fromUtf8(email_body.c_str()));
        UserDao::log_email_sent(db, user_id, 0, 0, 0, 0, 0, 0, "password_reset_to_volunteer");
    } else {
        IEmailGenerator::generateErrorEmail(error);
    }
}
