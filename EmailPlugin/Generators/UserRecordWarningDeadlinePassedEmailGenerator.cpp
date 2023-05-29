#include "UserRecordWarningDeadlinePassedEmailGenerator.h"

#include <QDateTime>

void UserRecordWarningDeadlinePassedEmailGenerator::run(int user_id)
{
    // qDebug() << "EmailGenerator: Generating UserRecordWarningDeadlinePassed email";

    ConfigParser settings;
    QString error = "";
    QSharedPointer<User> user = QSharedPointer<User>();
    QSharedPointer<MySQLHandler> db = MySQLHandler::getInstance();
    bool sendMessage = true;

    user = UserDao::getUser(db, user_id);
    if (!user) {
        error = "Failed to generate UserRecordWarningDeadlinePassed email: Unable to find User for user_id: ";
        error += QString::number(user_id);
    }

    if (error.compare("") == 0) {
        ctemplate::TemplateDictionary dict("user-record-warning-deadline-passed");
        if(user->display_name() != "") {
            dict.ShowSection("USER_HAS_NAME");
            dict.SetValue("USERNAME", Email::htmlspecialchars(user->display_name()));
        } else {
            dict.ShowSection("NO_USER_NAME");
        }
        QString profileUrl = settings.get("site.url");
        profileUrl += QString::number(user->id()) + "/privateProfile/";
        dict.SetValue("PROFILE_URL", profileUrl.toStdString());

        std::string email_body;
        QString template_location;
        template_location = QString(TEMPLATE_DIRECTORY) + "emails/user-record-warning-deadline-passed.tpl";
        ctemplate::ExpandTemplate(template_location.toStdString(), ctemplate::DO_NOT_STRIP, &dict, &email_body);

        UserDao::insertWillBeDeletedUser(db, user_id);

        if (sendMessage) {
            UserDao::queue_email(db, user_id, QString::fromStdString(user->email()), settings.get("site.name") + ": Complete your registration", QString::fromUtf8(email_body.c_str()), LOW);
            UserDao::log_email_sent(db, user_id, 0, 0, 0, 0, 0, 0, "profile_reminder_to_volunteer");
        }
    } else {
        IEmailGenerator::generateErrorEmail(error);
    }
}
