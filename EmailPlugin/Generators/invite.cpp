#include "invite.h"
#include "Common/MySQLHandler.h"
#include "Common/Definitions.h"

void invite::run(int special_registration_id)
{
    qDebug() << "invite special_registration_id:" << special_registration_id;

    ConfigParser settings;
    QString error = "";
    QSharedPointer<MySQLHandler> db = MySQLHandler::getInstance();
    QMap<QString, QVariant> special_registration = UserDao::get_special_registration_record(db, special_registration_id, settings.get("site.reg_key"));
    if (special_registration.isEmpty()) error = "invite: Failed to generate invite email. Could not find special_registration record in the DB, searched for special_registration_id: " + QString::number(special_registration_id);

    if (error == "") {
        unsigned long long int roles = special_registration["roles"].toULongLong();
        QString email   = special_registration["email"].toString();
        int org_id      = special_registration["org_id"].toInt();
        int admin_id    = special_registration["admin_id"].toInt();
        QString url     = special_registration["url"].toString();

        QSharedPointer<User> admin = UserDao::getUser(db, admin_id);
        QMap<QString, QVariant> personal = UserDao::getUserPersonalInfo(db, admin_id);

        std::string email_body;

        ctemplate::TemplateDictionary dict("invite_org");

        QString invite_link = settings.get("site.url") + url;
        dict.SetValue("INVITE_LINK", invite_link.toStdString());
        dict.SetValue("SENDER_NAME", Email::htmlspecialchars((personal["firstName"].toString() + ' ' + personal["lastName"].toString()).toStdString()));
        dict.SetValue("SENDER_EMAIL", admin->email());
        dict.SetValue("RECIPIENT_EMAIL", email.toStdString());

        if (org_id == 0) {
            if (roles&SITE_ADMIN) {
                QString templateLocation = QString(TEMPLATE_DIRECTORY) + "emails/invite_SITE_ADMIN.tpl";
                ctemplate::ExpandTemplate(templateLocation.toStdString(), ctemplate::DO_NOT_STRIP, &dict, &email_body);

                UserDao::queue_email(db, 0, email, "Invitation to join the TWB platform as an admin", QString::fromUtf8(email_body.c_str()));
                UserDao::log_email_sent(db, 0, 0, 0, 0, 0, admin_id, 0, "invite_to_SITE_ADMIN");
            } else if (roles&PROJECT_OFFICER) {
                QString templateLocation = QString(TEMPLATE_DIRECTORY) + "emails/invite_PROJECT_OFFICER.tpl";
                ctemplate::ExpandTemplate(templateLocation.toStdString(), ctemplate::DO_NOT_STRIP, &dict, &email_body);

                UserDao::queue_email(db, 0, email, "Invitation to join the TWB platform as a project officer", QString::fromUtf8(email_body.c_str()));
                UserDao::log_email_sent(db, 0, 0, 0, 0, 0, admin_id, 0, "invite_to_PROJECT_OFFICER");
            } else if (roles&COMMUNITY_OFFICER) {
                QString templateLocation = QString(TEMPLATE_DIRECTORY) + "emails/invite_COMMUNITY_OFFICER.tpl";
                ctemplate::ExpandTemplate(templateLocation.toStdString(), ctemplate::DO_NOT_STRIP, &dict, &email_body);

                UserDao::queue_email(db, 0, email, "Invitation to join the TWB platform as a community officer", QString::fromUtf8(email_body.c_str()));
                UserDao::log_email_sent(db, 0, 0, 0, 0, 0, admin_id, 0, "invite_to_COMMUNITY_OFFICER");
            }
        } else {
            QSharedPointer<Organisation> org = OrganisationDao::getOrg(db, org_id);
            dict.SetValue("ORG_NAME", org->name());

            if (roles&NGO_ADMIN) {
                QString templateLocation = QString(TEMPLATE_DIRECTORY) + "emails/invite_NGO_ADMIN.tpl";
                ctemplate::ExpandTemplate(templateLocation.toStdString(), ctemplate::DO_NOT_STRIP, &dict, &email_body);

                UserDao::queue_email(db, 0, email, "Invitation to join the TWB platform as an organization admin", QString::fromUtf8(email_body.c_str()));
                UserDao::log_email_sent(db, 0, 0, 0, org_id, 0, admin_id, 0, "invite_to_NGO_ADMIN");
            } else if (roles&NGO_PROJECT_OFFICER) {
                QString templateLocation = QString(TEMPLATE_DIRECTORY) + "emails/invite_NGO_PROJECT_OFFICER.tpl";
                ctemplate::ExpandTemplate(templateLocation.toStdString(), ctemplate::DO_NOT_STRIP, &dict, &email_body);

                UserDao::queue_email(db, 0, email, "Invitation to join the TWB platform as an organization project officer", QString::fromUtf8(email_body.c_str()));
                UserDao::log_email_sent(db, 0, 0, 0, org_id, 0, admin_id, 0, "invite_to_NGO_PROJECT_OFFICER");
            }else if (roles&NGO_LINGUIST) {
                QString templateLocation = QString(TEMPLATE_DIRECTORY) + "emails/invite_NGO_LINGUIST.tpl";
                ctemplate::ExpandTemplate(templateLocation.toStdString(), ctemplate::DO_NOT_STRIP, &dict, &email_body);

                UserDao::queue_email(db, 0, email, "Invitation to join the TWB platform as an organization linguist", QString::fromUtf8(email_body.c_str()));
                UserDao::log_email_sent(db, 0, 0, 0, org_id, 0, admin_id, 0, "invite_to_NGO_LINGUIST");
            }
        }
    } else {
        IEmailGenerator::generateErrorEmail(error);
    }
}
