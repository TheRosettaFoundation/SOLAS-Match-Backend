#include "ProjectImageStatusChangedEmailGenerator.h"
using namespace  SolasMatch::Common::Protobufs::Emails;

ProjectImageStatusChangedEmailGenerator::ProjectImageStatusChangedEmailGenerator()
{
    // Default ctor
}

void ProjectImageStatusChangedEmailGenerator::run()
{
    qDebug() << "EmailGenerator: Generating Project Image Approval Status Updated Email";
    ProjectImageStatusChangedEmail email_message;
    email_message.ParseFromString(this->protoBody.toStdString());


    ConfigParser settings;
    QSharedPointer<MySQLHandler> db = MySQLHandler::getInstance();
    QSharedPointer<Project> project = ProjectDao::getProject(db, email_message.project_id());
    QSharedPointer<Organisation> org = QSharedPointer<Organisation>();
       QString error = "";

    if (project.isNull()) {
        error = "Project image approval status updated email generation failed. Unable to find  project with id " +
                QString::number(email_message.project_id());
    } else {
        org = OrganisationDao::getOrg(db, project->organisationid());

        if (org.isNull()) {
            error = "Project image approval status updated email generation failed. Unable to find org with id " +
                    QString::number(project->organisationid());
        }

        if (!project->imageuploaded()) {
            error = "Project image approval status updated email generation failed. Invalid project image upload status :" +
                    QString::number(project->imageuploaded());
        }
    }

    if (error.compare("") == 0) {
        QList<QSharedPointer<User> > users = OrganisationDao::getOrgAdmins(db, project->organisationid());

        QString siteLocation = settings.get("site.url");
        QString siteName = settings.get("site.name");
        foreach (QSharedPointer<User> user, users) {
            QSharedPointer<Email> email = QSharedPointer<Email>(new Email);
            ctemplate::TemplateDictionary dict("projectImageStatusUpdated");
            dict.SetValue("SITE_NAME", siteName.toStdString());
            QString projectView = siteLocation + "project/" + QString::number(project->id()) + "/view/";
            dict.SetValue("PROJECT_VIEW", projectView.toStdString());
            dict.SetValue("PROJECT_TITLE", project->title());
            dict.SetValue("USERNAME", user->display_name());

            std::string email_body;
            QString template_location;
            QString approved;
            const char* projectTitle = project->title().c_str();

            if (project->imageapproved()) {
                approved = "Approved";
                template_location = QString(TEMPLATE_DIRECTORY) + "emails/project-image-approved.tpl";
            } else {
                approved = "Dissaproved";
                template_location = QString(TEMPLATE_DIRECTORY) + "emails/project-image-disapproved.tpl";
            }

            ctemplate::ExpandTemplate(template_location.toStdString(), ctemplate::DO_NOT_STRIP, &dict, &email_body);
            email->setSender(settings.get("site.system_email_address"));
            email->addRecipient(QString::fromStdString(user->email()));
            email->setSubject(settings.get("site.name") + ": Project Image Has Been " + approved + " [Project - " + projectTitle + "]");
            email->setBody(QString::fromUtf8(email_body.c_str()));
            this->emailQueue->insert(email, currentMessage);
        }


    }	else {
        QSharedPointer<Email> email = QSharedPointer<Email>(new Email);
        email = this->generateErrorEmail(error);
        this->emailQueue->insert(email, currentMessage);
    }
}
