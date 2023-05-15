#include "OrgCreated_SiteAdmin.h"
#include "Common/protobufs/emails/OrgCreatedSiteAdmin.pb.h"
using namespace  SolasMatch::Common::Protobufs::Emails;

void OrgCreate_SiteAdmin::run(int org_id, int admin_id)
{
    qDebug() << "OrgCreate_SiteAdmin org_id:" << org_id << "admin_id:" << admin_id;

    ConfigParser settings;
    QString error = "";
    QSharedPointer<MySQLHandler> db = MySQLHandler::getInstance();
    QSharedPointer<Organisation> org = OrganisationDao::getOrg(db, org_id);
    QSharedPointer<User> admin = UserDao::getUser(db, admin_id);

    if (admin.isNull() || org.isNull()) {
        error = "OrgCreate_SiteAdmin: Failed to generate org created email. Could not find ";
        error += "relevent data in the DB, searched for user " + QString::number(admin_id);
        error += " and org id " + QString::number(org_id);
    }

    if (error == "") {
        ctemplate::TemplateDictionary dict("org-created.site-admin");
        dict.SetValue("USERNAME", Email::htmlspecialchars(admin->display_name()));
        dict.SetValue("ORG_NAME", org->name());
        QString orgUrl = settings.get("site.url") + "org/" + QString::number(org->id()) + "/profile";
        dict.SetValue("ORG_URL", orgUrl.toStdString());
        dict.SetValue("SITE_NAME", std::string(settings.get("site.name").toLatin1().constData(), settings.get("site.name").toLatin1().length()));

        std::string email_body;
        QString templateLocation = QString(TEMPLATE_DIRECTORY) + "emails/org-created.site-admin.tpl";
        ctemplate::ExpandTemplate(templateLocation.toStdString(), ctemplate::DO_NOT_STRIP, &dict, &email_body);

        UserDao::queue_email(db, admin_id, QString::fromStdString(admin->email()), settings.get("site.name") + ": Organisation Created", QString::fromUtf8(email_body.c_str()));
        UserDao::log_email_sent(db, admin_id, 0, 0, org_id, 0, 0, 0, "org_created_to_site_admin");
    } else {
        this->generateErrorEmail(error);
    }
}
