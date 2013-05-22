#include "UserFeedbackGenerator.h"

#include <QDebug>

#include "Common/protobufs/emails/UserFeedback.pb.h"

UserFeedbackGenerator::UserFeedbackGenerator()
{
    // Default Constructor
}

void UserFeedbackGenerator::run()
{
    qDebug() << "EmailGenerator: Generating user feedback email";

    UserFeedback emailMessage;
    emailMessage.ParseFromString(this->protoBody.toStdString());

    ConfigParser settings;
    QString error = "";
    QSharedPointer<MySQLHandler> db = MySQLHandler::getInstance();
    QSharedPointer<Email> email = QSharedPointer<Email>(new Email);
    QSharedPointer<User> claimant = UserDao::getUser(db, emailMessage.claimant_id());
    QSharedPointer<Task> task = TaskDao::getTask(db, emailMessage.task_id());
    QSharedPointer<Project> project = QSharedPointer<Project>();
    QSharedPointer<Organisation> org = QSharedPointer<Organisation>();
    QString feedback = emailMessage.feedback().data();

    if (task.isNull() || claimant.isNull()) {
        error = "Failed to generate UserClaimedTaskDeadlinePassed email: Unable to find relevant ";
        error += "data in the Database. Searched for claimant ID ";
        error += QString::number(emailMessage.claimant_id()) + ", Task ID ";
        error += QString::number(emailMessage.task_id());
    } else {
        project = ProjectDao::getProject(db, task->projectid());

        if (project.isNull()) {
            error = "Failed to generate UserClaimedTaskDeadlinePassed email: Unable to find relevant ";
            error += " data in the DB. Searched for project id ";
            error += QString::number(task->projectid());
        } else {
            org = OrganisationDao::getOrg(db, project->organisationid());

            if (org.isNull()) {
                error = "Failed to generate UserClaimedTaskDeadlinePassed email: Unable to find relevant ";
                error += " data in the DB. Searched for org id ";
                error += QString::number(project->organisationid());
            }
        }
    }

    if(error.compare("") == 0) {
        bool isTracked = true;
        QList<QSharedPointer<User> > users = TaskDao::getSubscribedUsers(db, task->id());
        if (users.count() < 1) {
            isTracked = false;
            users = OrganisationDao::getOrgAdmins(db, org->id());
        }

        foreach (QSharedPointer<User> user, users) {
            email = QSharedPointer<Email>(new Email);
            ctemplate::TemplateDictionary dict("userFeedback");
            dict.SetValue("USERNAME", user->display_name());
            dict.SetValue("FEEDBACK", feedback.toStdString());
            dict.SetValue("ORG_NAME", org->name());
            dict.SetValue("SITE_NAME", settings.get("site.name").toStdString());
            if (isTracked) {
                dict.ShowSection("TRACKING_USER");
                dict.SetValue("CLAIMANT_NAME", claimant->display_name());
            } else {
                dict.ShowSection("ORG_ADMIN");
                dict.SetValue("CLAIMANT_NAME", claimant->display_name());
            }

            std::string email_body;
            QString template_location = QString(TEMPLATE_DIRECTORY) + "emails/user-feedback.tpl";
            ctemplate::ExpandTemplate(template_location.toStdString(), ctemplate::DO_NOT_STRIP, &dict, &email_body);

            email->setSender(settings.get("site.system_email_address"));;
            email->addRecipient(QString::fromStdString(user->email()));
            email->setSubject(settings.get("site.name") + ": Volunteer Feedback");
            email->setBody(QString::fromStdString(email_body));
            this->emailQueue->insert(email, currentMessage);
        }
    } else {
        email = this->generateErrorEmail(error);
        this->emailQueue->insert(email, currentMessage);
    }
}
