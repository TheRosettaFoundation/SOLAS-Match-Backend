#include "invite.h"
#include "Common/MySQLHandler.h"

void invite::run(int special_registration_id)
{
    qDebug() << "invite special_registration_id:" << special_registration_id;

    ConfigParser settings;
    QString error = "";
    QSharedPointer<MySQLHandler> db = MySQLHandler::getInstance();
[[[
UserDao::get_special_registration_record(db, special_registration_id)
CREATE TABLE IF NOT EXISTS `special_registrations` (
  id           INT UNSIGNED NOT NULL AUTO_INCREMENT,
  roles        BIGINT UNSIGNED NOT NULL,
  email        VARCHAR(128) COLLATE utf8mb4_unicode_ci NOT NULL,
  used         INT UNSIGNED NOT NULL,  # 0 => no, 1 => yes, 2 => yes but email mismatch so became LINGUIST
  org_id       INT UNSIGNED NOT NULL,
  admin_id     INT UNSIGNED NOT NULL,
  user_id      INT UNSIGNED NOT NULL,
  date_created DATETIME DEFAULT NULL,
  date_expires DATETIME DEFAULT NULL,
  date_used    DATETIME DEFAULT NULL,
  PRIMARY KEY (id),
  KEY         (email),
  KEY         (org_id),
  CONSTRAINT FK_special_registrations_Users FOREIGN KEY (user_id) REFERENCES Users (id) ON UPDATE CASCADE ON DELETE CASCADE
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_unicode_ci;
]]]
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
        IEmailGenerator::generateErrorEmail(error);
    }
}
