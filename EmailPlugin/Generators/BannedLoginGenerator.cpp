#include "BannedLoginGenerator.h"

#include <QDateTime>

#include "Common/Definitions.h"

static void BannedLoginGenerator::run(int user_id)
{
    qDebug() << "BannedLoginGenerator user_id:" << user_id;

    JSON emailMessage;
    emailMessage.ParseFromString(this->protoBody);

    ConfigParser settings;
    QString error = "";
    QSharedPointer<User> user = QSharedPointer<User>();
    QSharedPointer<BannedUser> banData = QSharedPointer<BannedUser>();
    QSharedPointer<Email> email = QSharedPointer<Email>(new Email());
    QSharedPointer<MySQLHandler> db = MySQLHandler::getInstance();

    user = UserDao::getUser(db, user_id);
    banData = UserDao::getBanData(db, user_id);

    if (user.isNull() || banData.isNull()) {
        error = "BannedLoginGenerator: Failed to generate banned login email. Could not find ";
        error += "relevent data in the DB, searched for user " + QString::number(user_id);
        error += " and ban data.";
    }

    if (error == "") {
        ctemplate::TemplateDictionary dict("BannedLogin");
        dict.SetValue("USERNAME", Email::htmlspecialchars(user->display_name()));
        dict.SetValue("SITE_NAME", std::string(settings.get("site.name").toLatin1().constData(), settings.get("site.name").toLatin1().length()));

        QDateTime banDate = QDateTime::fromString(QString::fromStdString(banData->banneddate()),
                "yyyy-MM-ddTHH:mm:ss.zzz");
        dict.SetValue("BAN_TIME", banDate.toString("d MMMM yyyy - hh:mm").toStdString());

        QString banLength = "";
        if (banData->bantype() == DAY) {
            banLength = "for one day";
        } else if (banData->bantype() == WEEK) {
            banLength = "for one week";
        } else if (banData->bantype() == MONTH) {
            banLength = "for one month";
        } else if (banData->bantype() == PERMANENT) {
            banLength = "permanently";
        }
        dict.SetValue("BAN_LENGTH", banLength.toStdString());

        if (banData->has_comment()) {
            ctemplate::TemplateDictionary *commentDict = dict.AddSectionDictionary("COMMENT_GIVEN");
            commentDict->SetValue("COMMENT", banData->comment());
        }

        std::string email_body;
        QString templateLocation = QString(TEMPLATE_DIRECTORY) + "emails/banned-login.tpl";
        ctemplate::ExpandTemplate(templateLocation.toStdString(), ctemplate::DO_NOT_STRIP, &dict, &email_body);

        UserDao::queue_email(db, user_id, QString::fromStdString(user->email()), settings.get("site.name") + ": Banned Notification", QString::fromUtf8(email_body.c_str()));
        UserDao::log_email_sent(db, user_id, 0, 0, 0, 0, 0, 0, "user_banned_to_volunteer");
    } else {
        IEmailGenerator::generateErrorEmail(error);
    }
}
