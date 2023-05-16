#include "UserTaskCancelledEmailGenerator.h"

static void UserTaskCancelledEmailGenerator::run(int user_id, int task_id)
{
    qDebug() << "UserTaskCancelledEmailGenerator user_id:" << QString::number(user_id) << "task_id:" << QString::number(task_id);

    ConfigParser settings;
    QString error = "";
    QSharedPointer<User> user = QSharedPointer<User>();
    QSharedPointer<Task> task = QSharedPointer<Task>();
    QSharedPointer<MySQLHandler> db = MySQLHandler::getInstance();
    QList<QMap<QString, QVariant>> task_type_details = TaskDao::get_task_type_details(db);

    user = UserDao::getUser(db, user_id);
    task = TaskDao::getTask(db, task_id);

    if(user.isNull() || task.isNull()) {
        error = "Failed to generate UserTaskCancelled email: Unable to find relevant ";
        error += "information in the database. Searched for user ID ";
        error += QString::number(user_id) + " and task ID ";
        error += QString::number(task_id) + ".";
    }

    if(error.compare("") == 0) {
        ctemplate::TemplateDictionary dict("user_task_cancelled");
        dict.SetValue("USERNAME", Email::htmlspecialchars(user->display_name()));

        QString task_url = settings.get("site.url");
        task_url += "task/" + QString::number(task->id()) + "/view";
        dict.SetValue("TASK_PAGE", task_url.toStdString());
        dict.SetValue("SITE_NAME", std::string(settings.get("site.name").toLatin1().constData(), settings.get("site.name").toLatin1().length()));
        dict.SetValue("TASK_TITLE", Email::htmlspecialchars(task->title()));

        std::string task_type = "Invalid Type";
        for (int i = 0; i < task_type_details.size(); i++) {
            QMap<QString, QVariant> task_type_detail = task_type_details[i];
            if (task->tasktype() == task_type_detail["type_enum"].toInt()) task_type = task_type_detail["type_text"].toString().toStdString();
        }
        dict.SetValue("TASK_TYPE", task_type);

        Locale taskSourceLocale =  task->sourcelocale();
        Locale taskTargetLocale = task->targetlocale();
        dict.SetValue("SOURCE_LANGUAGE",taskSourceLocale.languagename());
        dict.SetValue("TARGET_LANGUAGE",taskTargetLocale.languagename());

        QSharedPointer<Project> project = ProjectDao::getProject(db, task->projectid());
        dict.SetValue("COMMUNITY", ProjectDao::discourse_parameterize(project->title(), task->projectid()));

        if (!TaskDao::is_task_translated_in_memsource(db, task)) dict.ShowSection("CLAIMED");
        else                                                     dict.ShowSection("IN_PROGRESS");

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
        QString template_location = QString(TEMPLATE_DIRECTORY) + "emails/user-task-cancelled.tpl";
        ctemplate::ExpandTemplate(template_location.toStdString(), ctemplate::DO_NOT_STRIP, &dict, &email_body);

        UserDao::queue_email(db, user_id, QString::fromStdString(user->email()), settings.get("site.name") + ": Your task was cancelled - we are sorry for the inconvenience!", QString::fromUtf8(email_body.c_str()));
        UserDao::log_email_sent(db, user_id, task_id, 0, 0, 0, 0, 0, "task_cancelled_to_volunteer");
    } else {
        IEmailGenerator::generateErrorEmail(error);
    }
}
