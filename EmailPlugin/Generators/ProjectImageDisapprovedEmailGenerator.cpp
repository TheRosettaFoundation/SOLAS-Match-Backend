#include "ProjectImageDisapprovedEmailGenerator.h"

#include "Common/protobufs/emails/JSON.h"

using namespace  SolasMatch::Common::Protobufs::Emails;

ProjectImageDisapprovedEmailGenerator::ProjectImageDisapprovedEmailGenerator()
{
}

void ProjectImageDisapprovedEmailGenerator::run()
{
    qDebug() << "EmailGenerator: Generating Project Image Disapproved Email";
    JSON email_message;
    email_message.ParseFromString(this->protoBody);

    ConfigParser settings;
    QSharedPointer<MySQLHandler> db = MySQLHandler::getInstance();
    QSharedPointer<Email> email = QSharedPointer<Email>(new Email());
    QSharedPointer<Project> project = ProjectDao::getProject(db, email_message.project_id());
    QSharedPointer<User> user = QSharedPointer<User>();
    user = UserDao::getUser(db, email_message.user_id());
    QSharedPointer<Organisation> org = QSharedPointer<Organisation>();
    QString error = "";

    if (project.isNull()) {
        error = "Project image disapproved email generation failed. Unable to find  project with id " +
                QString::number(email_message.project_id());
    } else {
        org = OrganisationDao::getOrg(db, project->organisationid());

        if (org.isNull()) {
            error = "Project image disapproved email generation failed. Unable to find org with id " +
                    QString::number(project->organisationid());
        }

        if (!project->imageuploaded()) {
            error = "Project image disapproved email generation failed. Invalid project image upload status :" +
                    QString::number(project->imageuploaded());
        }
    }

    if (user.isNull()) {
        error = "Project image disapproved email generation failed.: Unable to find relevant ";
        error += "data in the Database. Searched for User ID (org admin)";
        error += QString::number(email_message.user_id()) + ".";
    }

    if (error.compare("") == 0) {
        QString siteLocation = settings.get("site.url");

        ctemplate::TemplateDictionary dict("projectImageDisapproved");
        dict.SetValue("SITE_NAME", std::string(settings.get("site.name").toLatin1().constData(), settings.get("site.name").toLatin1().length()));
        QString projectView = siteLocation + "project/" + QString::number(project->id()) + "/view/";
        dict.SetValue("PROJECT_VIEW", projectView.toStdString());
        dict.SetValue("PROJECT_TITLE", Email::htmlspecialchars(project->title()));

        if(user->display_name() != "") {
            dict.ShowSection("USER_HAS_NAME");
            dict.SetValue("USERNAME", Email::htmlspecialchars(user->display_name()));
        } else {
            dict.ShowSection("NO_USER_NAME");
        }

        std::string email_body;
        QString template_location = QString(TEMPLATE_DIRECTORY) + "emails/project-image-disapproved.tpl";
        ctemplate::ExpandTemplate(template_location.toStdString(), ctemplate::DO_NOT_STRIP, &dict, &email_body);
        QString projectTitle = QString::fromLatin1(project->title().c_str());

        email->setSender(settings.get("site.system_email_address"));;
        email->addRecipient(QString::fromStdString(user->email()));
        email->setSubject(settings.get("site.name") + ": Project image has been disapproved [Project - " + projectTitle + "]");
        email->setBody(QString::fromUtf8(email_body.c_str()));
    }	else {
        email = this->generateErrorEmail(error);
    }

    this->emailQueue->insert(email, currentMessage);
}

