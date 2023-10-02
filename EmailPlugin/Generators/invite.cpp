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
        QString email = special_registration["email"].toString();
        int org_id = special_registration["org_id"].toInt();
        if (org_id == 0) {







        } else {
            QSharedPointer<Organisation> org = OrganisationDao::getOrg(db, org_id);


            ctemplate::TemplateDictionary dict("invite_org");
            dict.SetValue("ORG_NAME", org->name());
            QString orgUrl = settings.get("site.url") + "org/" + QString::number(org->id()) + "/profile";
            dict.SetValue("ORG_URL", orgUrl.toStdString());

            QString dashboardUrl = settings.get("site.url") + "org/dashboard";
            dict.SetValue("DASHBOARD_URL", dashboardUrl.toStdString());

            QString donate_link = settings.get("email-footer.donate_link");
            ctemplate::TemplateDictionary* footer_dict = dict.AddIncludeDictionary("FOOTER");
            QString footer_location = QString(TEMPLATE_DIRECTORY) + "emails/footer.tpl";
            footer_dict -> SetValue("DONATE_LINK",donate_link.toStdString());
            footer_dict -> SetFilename(footer_location.toStdString());

            std::string email_body;
            QString templateLocation = QString(TEMPLATE_DIRECTORY) + "emails/org-created.org-admin.tpl";
            ctemplate::ExpandTemplate(templateLocation.toStdString(), ctemplate::DO_NOT_STRIP, &dict, &email_body);

            UserDao::queue_email(db, admin_id, QString::fromStdString(admin->email()), settings.get("site.name") + ": Organisation Created", QString::fromUtf8(email_body.c_str()));
            UserDao::log_email_sent(db, admin_id, 0, 0, org_id, 0, 0, 0, "org_created_to_org_admin");
        }
    } else {
        IEmailGenerator::generateErrorEmail(error);
    }
}
