#include "OrgCreated_SiteAdmin.h"
#include "Common/protobufs/emails/OrgCreatedSiteAdmin.pb.h"
using namespace  SolasMatch::Common::Protobufs::Emails;

OrgCreate_SiteAdmin::OrgCreate_SiteAdmin()
{
    // Default Constructor
}

void OrgCreate_SiteAdmin::run()
{
    qDebug() << "IEmailGenerator: Generating OrgCreated_SiteAdmin email";

    OrgCreatedSiteAdmin emailMessage;
    emailMessage.ParseFromString(this->protoBody);

    ConfigParser settings;
    QString error = "";
    QSharedPointer<Email> email = QSharedPointer<Email>(new Email());
    QSharedPointer<MySQLHandler> db = MySQLHandler::getInstance();
    QSharedPointer<Organisation> org = OrganisationDao::getOrg(db, emailMessage.org_id());
    QSharedPointer<User> admin = UserDao::getUser(db, emailMessage.site_admin_id());

    if (admin.isNull() || org.isNull()) {
        error = "OrgCreate_SiteAdmin: Failed to generate org created email. Could not find ";
        error += "relevent data in the DB, searched for user " + QString::number(emailMessage.site_admin_id());
        error += " and org id " + QString::number(emailMessage.org_id());
    }

    if (error == "") {
        ctemplate::TemplateDictionary dict("org-created.site-admin");
        dict.SetValue("USERNAME", Email::htmlspecialchars(admin->display_name()));
        dict.SetValue("ORG_NAME", org->name());
        QString orgUrl = settings.get("site.url") + "org/" + QString::number(org->id()) + "/profile";
        dict.SetValue("ORG_URL", orgUrl.toStdString());
        dict.SetValue("SITE_NAME", settings.get("site.name").toStdString());

        std::string email_body;
        QString templateLocation = QString(TEMPLATE_DIRECTORY) + "emails/org-created.site-admin.tpl";
        ctemplate::ExpandTemplate(templateLocation.toStdString(), ctemplate::DO_NOT_STRIP, &dict, &email_body);

        email->setSender(settings.get("site.system_email_address"));
        email->addRecipient(QString::fromStdString(admin->email()));
        email->setSubject(settings.get("site.name") + ": Organisation Created");
        email->setBody(QString::fromUtf8(email_body.c_str()));
    } else {
        email = this->generateErrorEmail(error);
    }

    this->emailQueue->insert(email, currentMessage);
}
