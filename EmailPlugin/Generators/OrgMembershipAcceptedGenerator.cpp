#include "OrgMembershipAcceptedGenerator.h"

#include "Common/ConfigParser.h"
#include "Common/MySQLHandler.h"

#include <QDebug>

#include <ctemplate/template.h>

#include "Common/MySQLHandler.h"
#include "Common/ConfigParser.h"

#include "Common/DataAccessObjects/UserDao.h"
#include "Common/DataAccessObjects/OrganisationDao.h"
#include "Common/DataAccessObjects/TaskDao.h"
#include "Common/DataAccessObjects/ProjectDao.h"

#include "Common/protobufs/models/User.pb.h"
#include "Common/protobufs/models/Task.pb.h"
#include "Common/protobufs/models/Project.pb.h"
#include "Common/protobufs/models/ArchivedTask.pb.h"
#include "Common/protobufs/models/Organisation.pb.h"

using namespace  SolasMatch::Common::Protobufs::Emails;

OrgMembershipAcceptedGenerator::OrgMembershipAcceptedGenerator()
{
    //default Constructor
}

void OrgMembershipAcceptedGenerator::run()
{
    qDebug() << "EmailGenerator - Generating OrgMembershipAccepted";
    OrgMembershipAccepted email_message;
    email_message.ParseFromString(protoBody);

    ConfigParser settings;
    QSharedPointer<Email> email = QSharedPointer<Email>(new Email());
    QSharedPointer<MySQLHandler> db = MySQLHandler::getInstance();
    QSharedPointer<Organisation> org = QSharedPointer<Organisation>();
    QSharedPointer<User> user = QSharedPointer<User>();
    QString error = "";


    user = UserDao::getUser(db, email_message.user_id());
    org = OrganisationDao::getOrg(db, email_message.org_id());
    if (user.isNull() || org.isNull()) {
        error = "Unable to generate OrgMembershipAccepted email. Unable to find objects ";
        error += "in the DB. Searched for user ID " + QString::number(email_message.user_id());
        error += " and org ID " + QString::number(email_message.org_id()) + ".";
    }

    if (error.compare("") == 0)
    {
        //No error generate the email
        ctemplate::TemplateDictionary dict("org_membership_accepted");
        if(user->display_name() != "") {
            dict.ShowSection("USER_HAS_NAME");
            dict.SetValue("USERNAME", Email::htmlspecialchars(user->display_name()));
        } else {
            dict.ShowSection("NO_USER_NAME");
        }
        dict.SetValue("ORG_NAME", org->name());
        dict.SetValue("SITE_NAME", std::string(settings.get("site.name").toLatin1().constData(), settings.get("site.name").toLatin1().length()));

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
        QString template_location = QString(TEMPLATE_DIRECTORY) + "emails/org-membership-accepted.tpl";
        ctemplate::ExpandTemplate(template_location.toStdString(), ctemplate::DO_NOT_STRIP, &dict, &email_body);

        email->setSender(settings.get("site.system_email_address"));
        email->addRecipient(QString::fromStdString(user->email()));
        email->setSubject(settings.get("site.name") + ": Organisation Membership Update");
        email->setBody(QString::fromUtf8(email_body.c_str()));
    } else {
        email = this->generateErrorEmail(error);
    }

    if (email) {
        this->emailQueue->insert(email, currentMessage);
    }
}
