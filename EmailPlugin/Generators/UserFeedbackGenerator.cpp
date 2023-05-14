#include "UserFeedbackGenerator.h"
#include <QDebug>

using namespace  SolasMatch::Common::Protobufs::Emails;

void UserFeedbackGenerator::run(int claimant_id, int task_id, QString feedback)
{
    qDebug() << "UserFeedbackGenerator claimant_id:" << QString::number(claimant_id) << "task_id:" << QString::number(task_id);

    ConfigParser settings;
    QString error = "";
    QSharedPointer<MySQLHandler> db = MySQLHandler::getInstance();
    QSharedPointer<User> claimant = UserDao::getUser(db, claimant_id);
    QSharedPointer<Task> task = TaskDao::getTask(db, task_id);
    QSharedPointer<Project> project = QSharedPointer<Project>();
    QSharedPointer<Organisation> org = QSharedPointer<Organisation>();

    if (task.isNull() || claimant.isNull()) {
        error = "Failed to generate UserFeedback email: Unable to find relevant ";
        error += "data in the Database. Searched for claimant ID ";
        error += QString::number(claimant_id) + ", Task ID ";
        error += QString::number(task_id);
    } else {
        project = ProjectDao::getProject(db, task->projectid());

        if (project.isNull()) {
            error = "Failed to generate UserFeedback email: Unable to find relevant ";
            error += " data in the DB. Searched for project id ";
            error += QString::number(task->projectid());
        } else {
            org = OrganisationDao::getOrg(db, project->organisationid());

            if (org.isNull()) {
                error = "Failed to generate UserFeedback email: Unable to find relevant ";
                error += " data in the DB. Searched for org id ";
                error += QString::number(project->organisationid());
            }
        }
    }

    if(error.compare("") == 0) {
        QList<QSharedPointer<User> > users = TaskDao::getSubscribedUsers(db, task->id());

        foreach (QSharedPointer<User> user, users) {
            email = QSharedPointer<Email>(new Email);
            ctemplate::TemplateDictionary dict("userFeedback");
            dict.SetValue("USERNAME", Email::htmlspecialchars(user->display_name()));
            dict.SetValue("FEEDBACK", Email::htmlspecialchars(feedback.toStdString()));
            dict.SetValue("ORG_NAME", org->name());
            QString taskView = settings.get("site.url") + "task/" + QString::number(task->id()) + "/view";
            dict.SetValue("TASK_VIEW", taskView.toStdString());
            dict.SetValue("TASK_TITLE", Email::htmlspecialchars(task->title()));
            dict.SetValue("SITE_NAME", std::string(settings.get("site.name").toLatin1().constData(), settings.get("site.name").toLatin1().length()));
            dict.SetValue("CLAIMANT_NAME", Email::htmlspecialchars(claimant->display_name()));

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
            QString template_location = QString(TEMPLATE_DIRECTORY) + "emails/user-feedback.tpl";
            ctemplate::ExpandTemplate(template_location.toStdString(), ctemplate::DO_NOT_STRIP, &dict, &email_body);

            UserDao::queue_email(db, user->id(), QString::fromStdString(user->email()), settings.get("site.name") + ": Volunteer Feedback", QString::fromUtf8(email_body.c_str()));
            UserDao::log_email_sent(db, user->id(), task_id, task->projectid(), project->organisationid(), claimant_id, 0, 0, "volunteer_feedback_to_subscribed_admin");
        }
    } else {
        this->generateErrorEmail(error);
    }
}
