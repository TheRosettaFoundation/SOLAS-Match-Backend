#include "TaskClaimedEmailGenerator.h"

using namespace  SolasMatch::Common::Protobufs::Emails;

static void TaskClaimedEmailGenerator::run(int user_id, int task_id, int claimant_id)
{
    qDebug() << "TaskClaimedEmailGenerator user_id:" << user_id << "task_id:" << QString::number(task_id) << "claimant_id:" << QString::number(claimant_id);

    ConfigParser settings;
    QString error = "";
    QSharedPointer<User> user = QSharedPointer<User>();
    QSharedPointer<User> translator = QSharedPointer<User>();
    QSharedPointer<Task> task = QSharedPointer<Task>();
    QSharedPointer<MySQLHandler> db = MySQLHandler::getInstance();
    QList<QMap<QString, QVariant>> task_type_details = TaskDao::get_task_type_details(db);

    user = UserDao::getUser(db, user_id);
    translator = UserDao::getUser(db, claimant_id);
    task = TaskDao::getTask(db, task_id);

    if(user.isNull() || translator.isNull() || task.isNull()) {
        error = "Failed to generate task claimed email: Unable to find relevant ";
        error += "information in the database. Searched for user ID ";
        error += QString::number(user_id) + ", translator ID ";
        error += QString::number(claimant_id) + " and task ID ";
        error += QString::number(task_id) + ".";
    }

    if(error.compare("") == 0) {
        ctemplate::TemplateDictionary dict("task_claimed");
        if(user->display_name() != "") {
            dict.ShowSection("USER_HAS_NAME");
            dict.SetValue("USERNAME", Email::htmlspecialchars(user->display_name()));
        } else {
            dict.ShowSection("NO_USER_NAME");
        }
        dict.SetValue("TASK_TITLE", Email::htmlspecialchars(task->title()));
        dict.SetValue("TRANSLATOR_NAME", Email::htmlspecialchars(translator->display_name()));
        dict.SetValue("SITE_NAME", std::string(settings.get("site.name").toLatin1().constData(), settings.get("site.name").toLatin1().length()));

        QString user_profile_url = settings.get("site.url");
        user_profile_url += QString::number(translator->id()) + "/profile";
        dict.SetValue("USER_PROFILE_URL",user_profile_url.toStdString());

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
        QString template_location = QString(TEMPLATE_DIRECTORY) + "emails/task-claimed.tpl";
        ctemplate::ExpandTemplate(template_location.toStdString(), ctemplate::DO_NOT_STRIP, &dict, &email_body);

        UserDao::queue_email(db, user_id, QString::fromStdString(user->email()), settings.get("site.name") + ": Task Claim Notification", QString::fromUtf8(email_body.c_str()));
        UserDao::log_email_sent(db, user_id, task_id, 0, 0, claimant_id, 0, 0, "task_claimed_to_subscribed_admin");
    } else {
        this->generateErrorEmail(error);
    }
}
