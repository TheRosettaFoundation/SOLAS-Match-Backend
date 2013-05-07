#include "BannedLoginGenerator.h"

#include <QDateTime>

#include "Common/protobufs/models/BannedUser.pb.h"

BannedLoginGenerator::BannedLoginGenerator()
{
    // Default Constructor
}

void BannedLoginGenerator::run()
{
    qDebug() << "IEmailGenerator: Generating BannedLogin email";

    BannedLogin emailMessage;
    emailMessage.ParseFromString(this->protoBody.toStdString());

    ConfigParser settings;
    QString error = "";
    QSharedPointer<User> user = QSharedPointer<User>();
    QSharedPointer<BannedUser> banData = QSharedPointer<BannedUser>();
    QSharedPointer<Email> email = QSharedPointer<Email>(new Email());
    QSharedPointer<MySQLHandler> db = MySQLHandler::getInstance();

    user = UserDao::getUser(db, emailMessage.user_id());
    banData = UserDao::getBanData(db, emailMessage.user_id());

    if (user.isNull() || banData.isNull()) {
        error = "BannedLoginGenerator: Failed to generate banned login email. Could not find ";
        error += "relevent data in the DB, searched for user " + QString::number(emailMessage.user_id());
        error += " and ban data.";
    }

    if (error == "") {
        ctemplate::TemplateDictionary dict("BannedLogin");
        dict["USERNAME"] = user->display_name();

        QDateTime banDate = QDateTime::fromString(QString::fromStdString(banData->banneddate()),
                "yyyy-MM-ddTHH:mm:ss");
        dict["BAN_TIME"] = banDate.toString("d MMMM yyyy - hh:mm").toStdString();

        qDebug() << "Ban Type: " << QString::fromStdString(banData->bantype());

        QString banLength = "";
        if (banData->bantype() == "Day") {
            banLength = "for one day";
        } else if (banData->bantype() == "Week") {
            banLength = "for one week";
        } else if (banData->bantype() == "Month") {
            banLength = "for one month";
        } else if (banData->bantype() == "Permanent") {
            banLength = "permanently";
        }
        dict["BAN_LENGTH"] = banLength.toStdString();

        if (banData->has_comment()) {
            ctemplate::TemplateDictionary *commentDict = dict.AddSectionDictionary("COMMENT_GIVEN");
            commentDict->SetValue("COMMENT", banData->comment());
        }

        std::string email_body;
        QString templateLocation = QString(TEMPLATE_DIRECTORY) + "emails/banned-login.tpl";
        ctemplate::ExpandTemplate(templateLocation.toStdString(), ctemplate::DO_NOT_STRIP, &dict, &email_body);

        email->setSender(settings.get("site.system_email_address"));;
        email->addRecipient(QString::fromStdString(user->email()));
        email->setSubject("Banned Login");
        email->setBody(QString::fromStdString(email_body));
    } else {
        email = this->generateErrorEmail(error);
    }

    this->emailQueue->insert(email, currentMessage);
}
