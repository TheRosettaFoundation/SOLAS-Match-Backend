#include "TaskArchivedEmailGenerator.h"

using namespace  SolasMatch::Common::Protobufs::Emails;

static void TaskArchivedEmailGenerator::run(int user_id, int task_id)
{
    qDebug() << "TaskArchivedEmailGenerator user_id:" << QString::number(user_id) << "task_id:" << QString::number(task_id);

    ConfigParser settings;
    QString error = "";
    QSharedPointer<User> user = QSharedPointer<User>();
    QSharedPointer<Organisation> org = QSharedPointer<Organisation>();
    QSharedPointer<ArchivedTask> task = QSharedPointer<ArchivedTask>();
    QSharedPointer<Project> project = QSharedPointer<Project>();
    QSharedPointer<MySQLHandler> db = MySQLHandler::getInstance();

    user = UserDao::getUser(db, user_id);
    task = TaskDao::getArchivedTask(db, task_id);

    if(!user.isNull() && !task.isNull()) {
        project = ProjectDao::getProject(db, task->projectid());

        if(!project.isNull()) {
            org = OrganisationDao::getOrg(db, project->organisationid());
            if(org.isNull()) {
                error = "Failed to Generate task archived email. Unable to find relevent information ";
                error += "in the Database. Unable to locate org with id " + QString::number(project->organisationid());
                error += ".";
            }
        } else {
            error = "Failed to Generate task archived email. Unable to find relevent information ";
            error += "in the Database. Searched for project ID " + QString::number(task->projectid());
        }
    } else {
        error = "Failed to Generate task archived email. Unable to find relevent information ";
        error += "in the Database. Searched for user ID " + QString::number(user_id);
        error += ", task ID " + QString::number(task_id) + ".";
    }

    if(error.compare("") == 0) {
        ctemplate::TemplateDictionary dict("task_archived");
        if(user->display_name() != "") {
            dict.ShowSection("USER_HAS_NAME");
            dict.SetValue("USERNAME", Email::htmlspecialchars(user->display_name()));
        } else {
            dict.ShowSection("NO_USER_NAME");
        }
        dict.SetValue("TASK_TITLE", Email::htmlspecialchars(task->title()));
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
        QString template_location = QString(TEMPLATE_DIRECTORY) + "emails/task-archived.tpl";
        ctemplate::ExpandTemplate(template_location.toStdString(), ctemplate::DO_NOT_STRIP, &dict, &email_body);

        UserDao::queue_email(db, user_id, QString::fromStdString(user->email()), settings.get("site.name") + ": Task Updated", QString::fromUtf8(email_body.c_str()));
        UserDao::log_email_sent(db, user_id, task_id, task->projectid(), project->organisationid(), 0, 0, 0, "task_archived_to_subscribed_admin");
    } else {
        this->generateErrorEmail(error);
    }
}
