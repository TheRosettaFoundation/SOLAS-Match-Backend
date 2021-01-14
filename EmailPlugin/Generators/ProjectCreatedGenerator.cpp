#include "ProjectCreatedGenerator.h"
using namespace  SolasMatch::Common::Protobufs::Emails;

ProjectCreatedGenerator::ProjectCreatedGenerator()
{
    // Default ctor
}

void ProjectCreatedGenerator::run()
{
    qDebug() << "EmailGenerator: Generating Project Created Email";

    ProjectCreatedEmail email_message;
    email_message.ParseFromString(this->protoBody);

    ConfigParser settings;
    QString error = "";
    QSharedPointer<MySQLHandler> db = MySQLHandler::getInstance();
    QSharedPointer<Email> email = QSharedPointer<Email>(new Email());
    QSharedPointer<Project> project = ProjectDao::getProject(db, email_message.project_id());
    QSharedPointer<Organisation> org = QSharedPointer<Organisation>();

    if (project.isNull()) {
        error = "Project created generation failed. Unable to find  project with id " +
                QString::number(email_message.project_id());
    } else {
        qDebug() << "EmailGenerator: Project Created Email Debugging: " << QString::number(email_message.project_id());
        org = OrganisationDao::getOrg(db, project->organisationid());

        if (org.isNull()) {
            error = "Project created generation failed. Unable to find org with id " +
                    QString::number(project->organisationid());
        }
    }

    if (error.compare("") == 0) {
        QString siteLocation = settings.get("site.url");
        QString siteName = settings.get("site.name");

        ctemplate::TemplateDictionary dict("projectCreated");
        dict.SetValue("SITE_NAME", std::string(settings.get("site.name").toLatin1().constData(), settings.get("site.name").toLatin1().length()));
        QString projectView = siteLocation + "project/" + QString::number(project->id()) + "/view/";
        dict.SetValue("PROJECT_VIEW", projectView.toStdString());
        dict.SetValue("PROJECT_TITLE", Email::htmlspecialchars(project->title()));
        QString orgView = siteLocation + "org/" + QString::number(org->id()) + "/profile/";
        dict.SetValue("ORG_VIEW", orgView.toStdString());
        dict.SetValue("ORG_NAME", org->name());
        dict.SetValue("COMMUNITY", ProjectDao::discourse_parameterize(project->title(), project->id()));
        std::string email_body;
        QString template_location = QString(TEMPLATE_DIRECTORY) + "emails/project-created.tpl";
        ctemplate::ExpandTemplate(template_location.toStdString(), ctemplate::DO_NOT_STRIP, &dict, &email_body);

        email->setSender(settings.get("site.system_email_address"));
        email->addRecipient(QString::fromStdString(email_message.recipient_email()));
        email->setSubject(siteName + ": Project Created");
        email->setBody(QString::fromUtf8(email_body.c_str()));
    } else {
        email = this->generateErrorEmail(error);
    }

    this->emailQueue->insert(email, currentMessage);
}
