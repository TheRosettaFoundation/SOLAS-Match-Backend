#include "OrgFeedbackGenerator.h"
#include <QDebug>
#include "Common/protobufs/emails/OrgFeedback.pb.h"

#include "Common/protobufs/emails/JSON.h"

using namespace  SolasMatch::Common::Protobufs::Emails;

OrgFeedbackGenerator::OrgFeedbackGenerator()
{
    // Default Constructor
}

void OrgFeedbackGenerator::run()
{
    qDebug() << "EmailGenerator: Generating org feedback email";

    JSON email_message;
    email_message.ParseFromString(this->protoBody);

    ConfigParser settings;
    QString error = "";
    QSharedPointer<MySQLHandler> db = MySQLHandler::getInstance();
    QSharedPointer<Email> email = QSharedPointer<Email>(new Email);
    QSharedPointer<User> sender = UserDao::getUser(db, email_message.user_id());
    QSharedPointer<User> claimant = UserDao::getUser(db, email_message.claimant_id());
    QSharedPointer<Task> task = TaskDao::getTask(db, email_message.task_id());
    QSharedPointer<Project> project = QSharedPointer<Project>();
    QSharedPointer<Organisation> org = QSharedPointer<Organisation>();
    QString feedback = email_message.feedback().data();

    if (sender.isNull() || task.isNull() || claimant.isNull()) {
        error = "Failed to generate OrgFeedback email: Unable to find relevant ";
        error += "data in the Database. Searched for claimant ID ";
        error += QString::number(email_message.claimant_id()) + ", Task ID ";
        error += QString::number(email_message.task_id()) + " and user ID ";
        error += QString::number(email_message.user_id());
    } else {
        project = ProjectDao::getProject(db, task->projectid());

        if (project.isNull()) {
            error = "Failed to generate OrgFeedback email: Unable to find relevant ";
            error += " data in the DB. Searched for project id ";
            error += QString::number(task->projectid());
        } else {
            org = OrganisationDao::getOrg(db, project->organisationid());

            if (org.isNull()) {
                error = "Failed to generate OrgFeedback email: Unable to find relevant ";
                error += " data in the DB. Searched for org id ";
                error += QString::number(project->organisationid());
            }
        }
    }

    if(error.compare("") == 0) {
        ctemplate::TemplateDictionary dict("feedbackEmail");
        dict.SetValue("SENDERNAME", Email::htmlspecialchars(sender->display_name()));
        dict.SetValue("USERNAME", Email::htmlspecialchars(claimant->display_name()));
        dict.SetValue("ORG_NAME", org->name());
        QString taskView = settings.get("site.url") + "task/" + QString::number(task->id()) + "/view";
        dict.SetValue("TASK_VIEW", taskView.toStdString());
        dict.SetValue("TASKTITLE", Email::htmlspecialchars(task->title()));
        dict.SetValue("FEEDBACK", Email::uiCleanseHTMLNewlineAndTabs(feedback.toStdString()));
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
        QString template_location = QString(TEMPLATE_DIRECTORY) + "emails/org-feedback.tpl";
        ctemplate::ExpandTemplate(template_location.toStdString(), ctemplate::DO_NOT_STRIP, &dict, &email_body);

        email->setSender(settings.get("site.system_email_address"));;
        email->addRecipient(QString::fromStdString(claimant->email()));
        email->setSubject(settings.get("site.name") + ": Organisation Feedback");
        email->setBody(QString::fromUtf8(email_body.c_str()));
        UserDao::log_email_sent(db, email_message.claimant_id(), email_message.task_id(), task->projectid(), project->organisationid(), 0, email_message.user_id(), 0, "admin_feedback_to_volunteer");
    } else {
        email = this->generateErrorEmail(error);
    }

    this->emailQueue->insert(email, currentMessage);
}
