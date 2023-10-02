#include "invite.h"
#include "Common/MySQLHandler.h"

void invite::run(int special_registration_id)
{
    qDebug() << "invite special_registration_id:" << special_registration_id;

    ConfigParser settings;
    QString error = "";
    QSharedPointer<MySQLHandler> db = MySQLHandler::getInstance();
    QMap<QString, QVariant> special_registration = UserDao::get_special_registration_record(db, special_registration_id)
    if (special_registration.isEmpty()) error = "invite: Failed to generate invite email. Could not find special_registration record in the DB, searched for special_registration_id: " + QString::number(special_registration_id);

    if (error == "") {
        ULongLong roles = special_registration["roles"].toULongLong();
        QString email   = special_registration["email"].toString();
        int org_id      = special_registration["org_id"].toInt();
        int admin_id    = special_registration["admin_id"].toInt();
        if (org_id == 0) {
            QString invite_link = settings.get("site.url") + "org/" + QString::number(org->id()) + "/profile";
            dict.SetValue("INVITE_LINK", invite_link.toStdString());

            std::string email_body;
            QString templateLocation = QString(TEMPLATE_DIRECTORY) + "emails/invite_site.tpl";
            ctemplate::ExpandTemplate(templateLocation.toStdString(), ctemplate::DO_NOT_STRIP, &dict, &email_body);

            UserDao::queue_email(db, 0, email, settings.get("site.name") + ": Invitation to Join TWB Platform as Admin", QString::fromUtf8(email_body.c_str()));
            UserDao::log_email_sent(db, 0, 0, 0, 0, 0, admin_id, 0, "invite_to_site");
        } else {
            QSharedPointer<Organisation> org = OrganisationDao::getOrg(db, org_id);
            ctemplate::TemplateDictionary dict("invite_org");
            dict.SetValue("ORG_NAME", org->name());

            QString invite_link = settings.get("site.url") + "org/" + QString::number(org->id()) + "/profile";
            dict.SetValue("INVITE_LINK", invite_link.toStdString());

            std::string email_body;
            QString templateLocation = QString(TEMPLATE_DIRECTORY) + "emails/invite_org.tpl";
            ctemplate::ExpandTemplate(templateLocation.toStdString(), ctemplate::DO_NOT_STRIP, &dict, &email_body);

            UserDao::queue_email(db, 0, email, settings.get("site.name") + ": Invitation to Join Organization", QString::fromUtf8(email_body.c_str()));
            UserDao::log_email_sent(db, 0, 0, 0, org_id, 0, admin_id, 0, "invite_to_org");
        }
    } else {
        IEmailGenerator::generateErrorEmail(error);
    }
}
