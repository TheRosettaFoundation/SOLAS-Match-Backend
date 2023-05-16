#include "OrgMembershipAcceptedGenerator.h"

#include "Common/ConfigParser.h"
#include "Common/MySQLHandler.h"

#include <QDebug>

#include <ctemplate/template.h>

#include "Common/DataAccessObjects/UserDao.h"
#include "Common/DataAccessObjects/OrganisationDao.h"
#include "Common/DataAccessObjects/TaskDao.h"
#include "Common/DataAccessObjects/ProjectDao.h"

#include "Common/protobufs/models/User.pb.h"
#include "Common/protobufs/models/Task.pb.h"
#include "Common/protobufs/models/Project.pb.h"
#include "Common/protobufs/models/ArchivedTask.pb.h"
#include "Common/protobufs/models/Organisation.pb.h"

void OrgMembershipAcceptedGenerator::run(int user_id, int org_id)
{
    qDebug() << "OrgMembershipAcceptedGenerator user_id:" << user_id << "org_id:" << org_id;

    ConfigParser settings;
    QSharedPointer<MySQLHandler> db = MySQLHandler::getInstance();
    QSharedPointer<Organisation> org = QSharedPointer<Organisation>();
    QSharedPointer<User> user = QSharedPointer<User>();
    QString error = "";

    user = UserDao::getUser(db, user_id);
    org = OrganisationDao::getOrg(db, org_id);
    if (user.isNull() || org.isNull()) {
        error = "Unable to generate OrgMembershipAccepted email. Unable to find objects ";
        error += "in the DB. Searched for user ID " + QString::number(user_id);
        error += " and org ID " + QString::number(org_id) + ".";
    }

    if (error.compare("") == 0)
    {
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

        UserDao::queue_email(db, user_id, QString::fromStdString(user->email()), settings.get("site.name") + ": Organisation Membership Update", QString::fromUtf8(email_body.c_str()));
        UserDao::log_email_sent(db, user_id, 0, 0, org_id, 0, 0, 0, "org_membership_accepted_to_volunteer");
    } else {
        IEmailGenerator::generateErrorEmail(error);
    }
}
