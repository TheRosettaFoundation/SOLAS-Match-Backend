#include "UserBadgeAwardedGenerator.h"
#include "Common/protobufs/emails/UserBadgeAwardedEmail.pb.h"
#include "Common/DataAccessObjects/BadgeDao.h"
using namespace  SolasMatch::Common::Protobufs::Emails;

UserBadgeAwardedGenerator::UserBadgeAwardedGenerator()
{
    // Default Constructor
}

void UserBadgeAwardedGenerator::run()
{
    qDebug() << "EmailGenerator: generating user badge awarded email";
    UserBadgeAwardedEmail emailMessage;
    emailMessage.ParseFromString(this->protoBody.toStdString());

    ConfigParser settings;
    QString error = "";
    QSharedPointer<Email> email = QSharedPointer<Email>(new Email());
    QSharedPointer<MySQLHandler> db = MySQLHandler::getInstance();
    QSharedPointer<User> user = UserDao::getUser(db, emailMessage.user_id());
    QSharedPointer<Badge> badge = BadgeDao::getBadge(db, emailMessage.badge_id());

    if (user.isNull() || badge.isNull()) {
        error = "Failed to generate user awarded badge email, unable to find relevant data in the ";
        error += "DB. Searched for user id " + QString::number(emailMessage.user_id()) + " and ";
        error += "badge id " + QString::number(emailMessage.badge_id());
    }

    if (error.length() == 0) {
        ctemplate::TemplateDictionary dict("user_badge_awarded");

        //workaround until the code is properly internationalized
        QString badge_title = "";
        switch(badge->id())
        {
            case 3:
                badge_title = "Profile-Filler";
                break;
            case 4:
                badge_title = "Registered";
                break;
            case 5:
                badge_title = "Native-Language";
                break;
            case 6:
                badge_title = "Translator";
                break;
            case 7:
                badge_title = "Proofreader";
                break;
            case 8:
                badge_title = "Interpreter";
                break;
            case 9:
                badge_title = "Polyglot";
                break;
        }

        dict.SetValue("USERNAME", user->display_name());
        dict.SetValue("BADGE_NAME", badge_title.toStdString());
        dict.SetValue("SITE_NAME", settings.get("site.name").toStdString());

        bool footer_enabled=(QString::compare("y", settings.get("email-footer.enabled")) == 0);
        if (footer_enabled)
        {
            QString donate_link = settings.get("email-footer.donate_link");
            ctemplate::TemplateDictionary* footer_dict = dict.AddIncludeDictionary("FOOTER");
            QString footer_location = QString(TEMPLATE_DIRECTORY) + "emails/footer.tpl";
            footer_dict -> SetValue("DONATE_LINK",donate_link.toStdString());
            footer_dict -> SetFilename(footer_location.toStdString());
        }

        std::string email_body;
        QString template_location = QString(TEMPLATE_DIRECTORY) + "emails/user-badge-awarded.tpl";
        ctemplate::ExpandTemplate(template_location.toStdString(), ctemplate::DO_NOT_STRIP, &dict, &email_body);

        email->setSender(settings.get("site.system_email_address"));;
        email->addRecipient(QString::fromStdString(user->email()));
        email->setSubject(settings.get("site.name") + ": Badge Awarded");
        email->setBody(QString::fromUtf8(email_body.c_str()));
    } else {
        email = this->generateErrorEmail(error);
    }

    this->emailQueue->insert(email, currentMessage);
}
