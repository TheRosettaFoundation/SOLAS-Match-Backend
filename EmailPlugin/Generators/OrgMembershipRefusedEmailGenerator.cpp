#include "OrgMembershipRefusedEmailGenerator.h"

OrgMembershipRefusedEmailGenerator::OrgMembershipRefusedEmailGenerator()
{
    //default constructor
}

void OrgMembershipRefusedEmailGenerator::run()
{
    qDebug() << "EmailGenerator - Generating OrgMembershipRefused";
    OrgMembershipRefused email_message;
    email_message.ParseFromString(this->protoBody.toStdString());

    ConfigParser settings;
    QSharedPointer<Email> email = QSharedPointer<Email>(new Email());
    QSharedPointer<User> user = QSharedPointer<User>();
    QSharedPointer<Organisation> org = QSharedPointer<Organisation>();
    MySQLHandler *db = new MySQLHandler(QUuid::createUuid().toString());
    QString error = "";

    if(db->init()) {
        user = UserDao::getUser(db, email_message.user_id());
        org = OrganisationDao::getOrg(db, email_message.org_id());

        if(user.isNull() || org.isNull())
        {
            error = "Unable to generate OrgMembershipRefused email. Unable to find objects ";
            error += "in the DB. Searched for user ID " + QString::number(email_message.user_id());
            error += " and org ID " + QString::number(email_message.org_id()) + ".";
        }
    } else {
        error = "Unable to Connect to SQL Server. Check conf.ini for connection settings and make sure ";
        error += "mysqld has been started.";
        qDebug() << "Unable to Connect to SQL Server. Check conf.ini and try again.";
    }

    if(error.compare("") == 0)
    {
        ctemplate::TemplateDictionary dict("org_membershipt_refused");
        if(user->display_name() != "") {
            dict.ShowSection("USER_HAS_NAME");
            dict["USERNAME"] = user->display_name();
        } else {
            dict.ShowSection("NO_USER_NAME");
        }
        dict["ORG_NAME"] = org->name();
        std::string email_body;
        QString template_location = QString(TEMPLATE_DIRECTORY) + "emails/org-membership-refused.tpl";
        ctemplate::ExpandTemplate(template_location.toStdString(), ctemplate::DO_NOT_STRIP, &dict, &email_body);

        email->setSender(settings.get("site.system_email_address"));
        email->addRecipient(QString::fromStdString(user->email()));
        email->setSubject("SOLAS Match: Organisation Membership Update");
        email->setBody(QString::fromStdString(email_body));
    } else {
        email = this->generateErrorEmail(error);
    }

    delete db;

    this->emailQueue->enqueue(email);
}
