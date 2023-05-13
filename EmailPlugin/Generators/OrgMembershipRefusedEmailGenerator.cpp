#include "OrgMembershipRefusedEmailGenerator.h"

using namespace  SolasMatch::Common::Protobufs::Emails;


static void OrgMembershipRefusedEmailGenerator::run(int user_id, int org_id)
{
    qDebug() << "OrgMembershipRefusedEmailGenerator user_id:" << user_id << "org_id:" << org_id;

    ConfigParser settings;
    QSharedPointer<User> user = QSharedPointer<User>();
    QSharedPointer<Organisation> org = QSharedPointer<Organisation>();
    QSharedPointer<MySQLHandler> db = MySQLHandler::getInstance();
    QString error = "";

    user = UserDao::getUser(db, user_id);
    org = OrganisationDao::getOrg(db, org_id);

    if(user.isNull() || org.isNull())
    {
        error = "Unable to generate OrgMembershipRefused email. Unable to find objects ";
        error += "in the DB. Searched for user ID " + QString::number(user_id);
        error += " and org ID " + QString::number(org_id) + ".";
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

        UserDao::queue_email(db, user_id, QString::fromStdString(user->email()), settings.get("site.name") + ": Organisation Membership Update", QString::fromUtf8(email_body.c_str()));
        UserDao::log_email_sent(db, user_id, 0, 0, org_id, 0, 0, 0, "org_membership_refused_to_volunteer");
    } else {
        this->generateErrorEmail(error);
    }
}
