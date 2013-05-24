#include "OrgCreated_OrgEmail.h"

#include "Common/protobufs/emails/OrgCreatedOrgAdmin.pb.h"
#include "Common/MySQLHandler.h"

OrgCreated_OrgEmail::OrgCreated_OrgEmail()
{
    // Default Constructor
}

void OrgCreated_OrgEmail::run()
{
    qDebug() << "IEmailGenerator: Generating OrgCreated_Org email";

    OrgCreatedOrgAdmin emailMessage;
    emailMessage.ParseFromString(this->protoBody.toStdString());

    ConfigParser settings;
    QString error = "";
    QSharedPointer<Email> email = QSharedPointer<Email>(new Email());
    QSharedPointer<MySQLHandler> db = MySQLHandler::getInstance();
    QSharedPointer<Organisation> org = OrganisationDao::getOrg(db, emailMessage.org_id());
    QSharedPointer<User> admin = UserDao::getUser(db, emailMessage.org_admin_id());

    if (admin.isNull() || org.isNull()) {
        error = "OrgCreated_OrgEmail: Failed to generate org created email. Could not find ";
        error += "relevent data in the DB, searched for user " + QString::number(emailMessage.org_admin_id());
        error += " and org id " + QString::number(emailMessage.org_id());
    }

    if (error == "") {
        ctemplate::TemplateDictionary dict("org-create.org-admin");
        dict.SetValue("USERNAME", admin->display_name());
        dict.SetValue("ORG_NAME", org->name());
        dict.SetValue("SITE_NAME", settings.get("site.name").toStdString());
        QString orgUrl = settings.get("site.url") + "org/" + QString::number(org->id()) + "/profile";
        dict.SetValue("ORG_URL", orgUrl.toStdString());
        QString dashboardUrl = settings.get("site.url") + "org/dashboard";
        dict.SetValue("DASHBOARD_URL", dashboardUrl.toStdString());

        std::string email_body;
        QString templateLocation = QString(TEMPLATE_DIRECTORY) + "emails/org-created.org-admin.tpl";
        ctemplate::ExpandTemplate(templateLocation.toStdString(), ctemplate::DO_NOT_STRIP, &dict, &email_body);

        email->setSender(settings.get("site.system_email_address"));
        email->addRecipient(QString::fromStdString(admin->email()));
        email->setSubject(settings.get("site.name") + ": Organisation Created");
        email->setBody(QString::fromStdString(email_body));
    } else {
        email = this->generateErrorEmail(error);
    }

    this->emailQueue->insert(email, currentMessage);
}
