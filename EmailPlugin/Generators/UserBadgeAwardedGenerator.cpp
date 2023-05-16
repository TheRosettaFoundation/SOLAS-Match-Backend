#include "UserBadgeAwardedGenerator.h"
#include "Common/DataAccessObjects/BadgeDao.h"

void UserBadgeAwardedGenerator::run(int user_id, int badge_id)
{
    qDebug() << "UserBadgeAwardedGenerator user_id:" << user_id << "badge_id:" << badge_id;

    ConfigParser settings;
    QString error = "";
    QSharedPointer<MySQLHandler> db = MySQLHandler::getInstance();
    QSharedPointer<User> user = UserDao::getUser(db, user_id);
    QSharedPointer<Badge> badge = BadgeDao::getBadge(db, badge_id);
    QSharedPointer<Organisation> org = QSharedPointer<Organisation>();

    if (user.isNull() || badge.isNull()) {
        error = "Failed to generate user awarded badge email, unable to find relevant data in the ";
        error += "DB. Searched for user id " + QString::number(user_id) + " and ";
        error += "badge id " + QString::number(badge_id);
    }

    if (error.length() == 0) {
        ctemplate::TemplateDictionary dict("user_badge_awarded");

        //workaround until the code is properly internationalized
        QString badge_title = "";
        QString orgView = "";
        QString orgName = "";

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
            default:
                if (badge->owner_id() != 0) {
                    badge_title = QString::fromStdString(badge->title());

                    org = OrganisationDao::getOrg(db, badge->owner_id());

                    if (!org.isNull()) {
                        QString siteLocation = settings.get("site.url");
                        orgView = siteLocation + "org/" + QString::number(org->id()) + "/profile/";
                        orgName = QString::fromStdString(org->name());
                    }
                }
        }

        dict.SetValue("USERNAME", Email::htmlspecialchars(user->display_name()));
        dict.SetValue("BADGE_NAME", Email::htmlspecialchars(badge_title.toStdString()));
        dict.SetValue("SITE_NAME", std::string(settings.get("site.name").toLatin1().constData(), settings.get("site.name").toLatin1().length()));
        dict.SetValue("ORG_VIEW", orgView.toStdString());
        dict.SetValue("ORG_NAME", orgName.toStdString());

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
        if (badge_title == "Registered") {
            template_location = QString(TEMPLATE_DIRECTORY) + "emails/user-badge-awarded-registration.tpl";
        }
        if (badge->owner_id() != 0) {
            template_location = QString(TEMPLATE_DIRECTORY) + "emails/user-badge-awarded-organisation.tpl";
        }

        ctemplate::ExpandTemplate(template_location.toStdString(), ctemplate::DO_NOT_STRIP, &dict, &email_body);

        if (badge_title == "Registered") {
            UserDao::queue_email(db, user_id, QString::fromStdString(user->email()), settings.get("site.name") + ": Thank you for completing your profile", QString::fromUtf8(email_body.c_str()));
            UserDao::log_email_sent(db, user_id, 0, 0, 0, 0, 0, badge_id, "profile_completed_to_volunteer");
        } else {
            UserDao::queue_email(db, user_id, QString::fromStdString(user->email()), settings.get("site.name") + ": Achievement Awarded", QString::fromUtf8(email_body.c_str()));
            UserDao::log_email_sent(db, user_id, 0, 0, badge->owner_id(), 0, 0, badge_id, "achievement_awarded_to_volunteer");
        }
    } else {
        IEmailGenerator::generateErrorEmail(error);
    }
}
