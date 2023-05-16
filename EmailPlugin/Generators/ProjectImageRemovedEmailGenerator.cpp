#include "ProjectImageRemovedEmailGenerator.h"

static void ProjectImageRemovedEmailGenerator::run(project_id)
{
    qDebug() << "ProjectImageRemovedEmailGenerator project_id:" << project_id;

    ConfigParser settings;
    QSharedPointer<MySQLHandler> db = MySQLHandler::getInstance();
    QSharedPointer<Project> project = ProjectDao::getProject(db, project_id);
    QSharedPointer<Organisation> org = QSharedPointer<Organisation>();
    QString error = "";

    if (project.isNull()) {
        error = "Project image removed email generation failed. Unable to find project with id " +
                QString::number(project_id);
    } else {
        org = OrganisationDao::getOrg(db, project->organisationid());

        if (org.isNull()) {
            error = "Project image removed email generation failed. Unable to find org with id " +
                    QString::number(project->organisationid());
        }

        if (!project->imageuploaded()) {
            error = "Project image removed email generation failed. Invalid project image upload status :" +
                    QString::number(project->imageuploaded());
        }
    }

    if (error.compare("") == 0) {
        QString siteLocation = settings.get("site.url");

        ctemplate::TemplateDictionary dict("projectImageRemoved");
        dict.SetValue("SITE_NAME", std::string(settings.get("site.name").toLatin1().constData(), settings.get("site.name").toLatin1().length()));
        QString projectView = siteLocation + "project/" + QString::number(project->id()) + "/view/";
        dict.SetValue("PROJECT_VIEW", projectView.toStdString());
        dict.SetValue("PROJECT_TITLE", Email::htmlspecialchars(project->title()));
        QString orgView = siteLocation + "org/" + QString::number(org->id()) + "/profile/";
        dict.SetValue("ORG_VIEW", orgView.toStdString());
        dict.SetValue("ORG_NAME", org->name());
        std::string email_body;
        QString template_location = QString(TEMPLATE_DIRECTORY) + "emails/project-image-removed.tpl";
        ctemplate::ExpandTemplate(template_location.toStdString(), ctemplate::DO_NOT_STRIP, &dict, &email_body);
        QString projectTitle = QString::fromLatin1(project->title().c_str());
        QStringList admins = settings.get("mail.admin_emails").split(",");
        foreach(QString admin, admins) {
            UserDao::queue_email(db, 0, admin.trimmed(), settings.get("site.name") + ": Project Image Removed [Project - " + projectTitle + "]", QString::fromUtf8(email_body.c_str()));
        }
        UserDao::log_email_sent(db, 0, 0, project_id, project->organisationid(), 0, 0, 0, "image_removed_to_admin_emails_list");
    }	else {
        IEmailGenerator::generateErrorEmail(error);
    }
}
