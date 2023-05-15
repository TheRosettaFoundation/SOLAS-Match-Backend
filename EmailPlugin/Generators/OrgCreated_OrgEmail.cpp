#include "OrgCreated_OrgEmail.h"
#include "Common/MySQLHandler.h"
using namespace  SolasMatch::Common::Protobufs::Emails;

void OrgCreated_OrgEmail::run(int org_id, int admin_id)
{
    qDebug() << "OrgCreated_OrgEmail org_id:" << org_id << "admin_id:" << admin_id;

    ConfigParser settings;
    QString error = "";
    QSharedPointer<MySQLHandler> db = MySQLHandler::getInstance();
    QSharedPointer<Organisation> org = OrganisationDao::getOrg(db, org_id);
    QSharedPointer<User> admin = UserDao::getUser(db, admin_id);

    if (admin.isNull() || org.isNull()) {
        error = "OrgCreated_OrgEmail: Failed to generate org created email. Could not find ";
        error += "relevent data in the DB, searched for user " + QString::number(admin_id);
        error += " and org id " + QString::number(org_id);
    }

    if (error == "") {
        ctemplate::TemplateDictionary dict("org-create.org-admin");
        dict.SetValue("USERNAME", Email::htmlspecialchars(admin->display_name()));
        dict.SetValue("ORG_NAME", org->name());
        dict.SetValue("SITE_NAME", std::string(settings.get("site.name").toLatin1().constData(), settings.get("site.name").toLatin1().length()));
        QString orgUrl = settings.get("site.url") + "org/" + QString::number(org->id()) + "/profile";
        dict.SetValue("ORG_URL", orgUrl.toStdString());
        QString dashboardUrl = settings.get("site.url") + "org/dashboard";
        dict.SetValue("DASHBOARD_URL", dashboardUrl.toStdString());

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
        QString templateLocation = QString(TEMPLATE_DIRECTORY) + "emails/org-created.org-admin.tpl";
        ctemplate::ExpandTemplate(templateLocation.toStdString(), ctemplate::DO_NOT_STRIP, &dict, &email_body);

        UserDao::queue_email(db, admin_id, QString::fromStdString(admin->email()), settings.get("site.name") + ": Organisation Created", QString::fromUtf8(email_body.c_str()));
        UserDao::log_email_sent(db, admin_id, 0, 0, org_id, 0, 0, 0, "org_created_to_org_admin");
    } else {
        this->generateErrorEmail(error);
    }
}
