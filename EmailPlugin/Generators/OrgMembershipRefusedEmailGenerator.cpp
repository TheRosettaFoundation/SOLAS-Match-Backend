#include "OrgMembershipRefusedEmailGenerator.h"

#include "Common/protobufs/emails/JSON.h"

using namespace  SolasMatch::Common::Protobufs::Emails;

OrgMembershipRefusedEmailGenerator::OrgMembershipRefusedEmailGenerator()
{
    //default constructor
}

void OrgMembershipRefusedEmailGenerator::run()
{
    qDebug() << "EmailGenerator - Generating OrgMembershipRefused";
    JSON email_message;
    email_message.ParseFromString(this->protoBody);

    ConfigParser settings;
    QSharedPointer<Email> email = QSharedPointer<Email>(new Email());
    QSharedPointer<User> user = QSharedPointer<User>();
    QSharedPointer<Organisation> org = QSharedPointer<Organisation>();
    QSharedPointer<MySQLHandler> db = MySQLHandler::getInstance();
    QString error = "";

    user = UserDao::getUser(db, email_message.user_id());
    org = OrganisationDao::getOrg(db, email_message.org_id());

    if(user.isNull() || org.isNull())
    {
        error = "Unable to generate OrgMembershipRefused email. Unable to find objects ";
        error += "in the DB. Searched for user ID " + QString::number(email_message.user_id());
        error += " and org ID " + QString::number(email_message.org_id()) + ".";
    }

    if(error.compare("") == 0)
    {
        ctemplate::TemplateDictionary dict("org_membershipt_refused");
        if(user->display_name() != "") {
            dict.ShowSection("USER_HAS_NAME");
            dict.SetValue("USERNAME", Email::htmlspecialchars(user->display_name()));
        } else {
            dict.ShowSection("NO_USER_NAME");
        }
        dict.SetValue("ORG_NAME", org->name());
        dict.SetValue("SITE_NAME", std::string(settings.get("site.name").toLatin1().constData(), settings.get("site.name").toLatin1().length()));
        std::string email_body;
        QString template_location = QString(TEMPLATE_DIRECTORY) + "emails/org-membership-refused.tpl";
        ctemplate::ExpandTemplate(template_location.toStdString(), ctemplate::DO_NOT_STRIP, &dict, &email_body);

        email->setSender(settings.get("site.system_email_address"));
        email->addRecipient(QString::fromStdString(user->email()));
        email->setSubject(settings.get("site.name") + ": Organisation Membership Update");
        email->setBody(QString::fromUtf8(email_body.c_str()));
    } else {
        email = this->generateErrorEmail(error);
    }

    this->emailQueue->insert(email, currentMessage);
}
