#include "OrgDeadlinePassedEmailGenerator.h"

void OrgDeadlinePassedMailGenerator::run(int user_id, int task_id)
{
    qDebug() << "EmailGenerator - Generating OrgTaskDeadlinePassed";

    ConfigParser settings;
    QString error = "";
    QSharedPointer<User> user = QSharedPointer<User>();
    QSharedPointer<Task> task = QSharedPointer<Task>();
    QSharedPointer<MySQLHandler> db = MySQLHandler::getInstance();

    task = TaskDao::getTask(db, task_id);
    user = UserDao::getUser(db, user_id);

    if (user.isNull() || task.isNull()) {
        error = "OrgTaskDeadlinePassed generation failed. Data missing from the DB.";
        error += " Searched for user ID " + QString::number(user_id);
        error += " and task ID " + QString::number(task_id);
    }

    if(error.compare("") == 0) {
        ctemplate::TemplateDictionary dict("OrgTaskDeadlinePassed");
        if(user->display_name() != "") {
            dict.ShowSection("USER_HAS_NAME");
            dict.SetValue("USERNAME", Email::htmlspecialchars(user->display_name()));
        } else {
            dict.ShowSection("NO_USER_NAME");
        }
        dict.SetValue("TASK_TITLE", Email::htmlspecialchars(task->title()));
        QString taskView = settings.get("site.url") + "task/" + QString::number(task->id()) + "/view";
        dict.SetValue("TASK_VIEW", taskView.toStdString());
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
        QString template_location = QString(TEMPLATE_DIRECTORY) + "emails/org-task-deadline-passed.tpl";
        ctemplate::ExpandTemplate(template_location.toStdString(), ctemplate::DO_NOT_STRIP, &dict, &email_body);

        UserDao::queue_email(db, user_id, QString::fromStdString(user->email()), settings.get("site.name") + ": Task Update", QString::fromUtf8(email_body.c_str()), LOW);
        UserDao::log_email_sent(db, user_id, task_id, 0, 0, 0, 0, 0, "deadline_passed_to_subscribed_admin");
    } else {
        IEmailGenerator::generateErrorEmail(error);
    }
}
