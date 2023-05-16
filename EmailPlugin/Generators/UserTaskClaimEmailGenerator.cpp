#include "UserTaskClaimEmailGenerator.h"

void UserTaskClaimEmailGenerator::run(int user_id, int task_id)
{
    qDebug() << "UserTaskClaimEmailGenerator user_id:" << user_id << "task_id:" << QString::number(task_id);

    ConfigParser settings;
    QString error = "";
    QSharedPointer<User> user = QSharedPointer<User>();
    QSharedPointer<Task> task = QSharedPointer<Task>();
    QSharedPointer<MySQLHandler> db = MySQLHandler::getInstance();
    QList<QMap<QString, QVariant>> task_type_details = TaskDao::get_task_type_details(db);

    user = UserDao::getUser(db, user_id);
    task = TaskDao::getTask(db, task_id);

    if(user.isNull() || task.isNull()) {
        error = "Failed to generate UserTaskClaim email: Unable to find relevant ";
        error += "data in the Database. Searched for User ID ";
        error += QString::number(user_id) + " and Task ID ";
        error += QString::number(task_id) + ".";
    }

    if(error.compare("") == 0) {
        ctemplate::TemplateDictionary dict("user_task_claim");
        if(user->display_name() != "") {
            dict.ShowSection("USER_HAS_NAME");
            dict.SetValue("USERNAME", Email::htmlspecialchars(user->display_name()));
        } else {
            dict.ShowSection("NO_USER_NAME");
        }

        QString task_url = settings.get("site.url");
        task_url += "task/" + QString::number(task->id()) + "/view";
        dict.SetValue("TASK_PAGE", task_url.toStdString());
        dict.SetValue("SITE_NAME", std::string(settings.get("site.name").toLatin1().constData(), settings.get("site.name").toLatin1().length()));
        dict.SetValue("TASK_TITLE", Email::htmlspecialchars(task->title()));

        QMap<QString, QVariant> memsource_task = TaskDao::get_memsource_task(db, task->id());

        std::string task_type = "Invalid Type";
        for (int i = 0; i < task_type_details.size(); i++) {
            QMap<QString, QVariant> task_type_detail = task_type_details[i];
            if (task->tasktype() == task_type_detail["type_enum"].toInt()) {
                task_type = task_type_detail["type_text"].toString().toStdString();
                if (TaskDao::is_task_translated_in_memsource(db, task)) {
                    dict.ShowSection(task_type_detail["show_section"].toString().toStdString());
                } else {
                    dict.ShowSection(task_type_detail["show_section"].toString().toStdString() + "_WAIT");
                }
            }
        }
        dict.SetValue("TASK_TYPE", task_type);

        Locale taskSourceLocale =  task->sourcelocale();
        Locale taskTargetLocale = task->targetlocale();
        dict.SetValue("SOURCE_LANGUAGE",taskSourceLocale.languagename());
        dict.SetValue("TARGET_LANGUAGE",taskTargetLocale.languagename());

        dict.SetValue("MATECAT", TaskDao::get_matecat_url(db, task, memsource_task));

        QString notificationPhrase = "";
        if (TaskDao::is_chunked_task(db, task->id())) {
            if (task->tasktype() == 3) {
                QSharedPointer<Task> translationTask = TaskDao::getMatchingTask(db, task->id(), TRANSLATION);
                if (!translationTask.isNull()) {
                    if (translationTask->taskstatus() != COMPLETE) {
                        notificationPhrase = ", after you receive a notification that it has been translated";
                    }
                }
            }
        }
        dict.SetValue("NOTIFICATION_PHRASE", notificationPhrase.toStdString());

        QSharedPointer<Project> project = ProjectDao::getProject(db, task->projectid());
        dict.SetValue("COMMUNITY", ProjectDao::discourse_parameterize(project->title(), task->projectid()));

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
        QString template_location;
        if (TaskDao::is_chunked_task(db, task->id())) {
            template_location = QString(TEMPLATE_DIRECTORY) + "emails/user-task-claim-chunk.tpl";
        } else {
          if (task->title().length() == 8 && task->title().find("Test") == 0) { // Verification Task
            template_location = QString(TEMPLATE_DIRECTORY) + "emails/user-task-claim-verification.tpl";
          } else {
           if (!memsource_task.isEmpty()) {
            template_location = QString(TEMPLATE_DIRECTORY) + "emails/user-task-claim-memsource.tpl";
           } else {
            template_location = QString(TEMPLATE_DIRECTORY) + "emails/user-task-claim.tpl";
           }
          }
        }
        ctemplate::ExpandTemplate(template_location.toStdString(), ctemplate::DO_NOT_STRIP, &dict, &email_body);

        if (task->title().length() == 8 && task->title().find("Test") == 0) { // Verification Task
            UserDao::queue_email(db, user_id, QString::fromStdString(user->email()), settings.get("site.name") + ": Test to become a Verified Translator", QString::fromUtf8(email_body.c_str()));
        } else {
            UserDao::queue_email(db, user_id, QString::fromStdString(user->email()), settings.get("site.name") + ": Task Claim Notification", QString::fromUtf8(email_body.c_str()));
        }
        UserDao::log_email_sent(db, user_id, task_id, 0, 0, 0, 0, 0, "task_claimed_to_volunteer");
    } else {
        IEmailGenerator::generateErrorEmail(error);
    }
}
