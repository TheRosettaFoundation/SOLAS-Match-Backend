#include "OrgTaskRevokedGenerator.h"

static void OrgTaskRevokedGenerator::run(int task_id, int user_id, int claimant_id)
{
    qDebug() << "OrgTaskRevokedGenerator task_id:" << task_id << "user_id:" << user_id << "claimant_id:" << claimant_id;

    ConfigParser settings;
    QSharedPointer<MySQLHandler> db = MySQLHandler::getInstance();
    QList<QMap<QString, QVariant>> task_type_details = TaskDao::get_task_type_details(db);
    QSharedPointer<User> user = UserDao::getUser(db, user_id);
    QSharedPointer<Task> task = TaskDao::getTask(db, task_id);
    QSharedPointer<User> claimant = UserDao::getUser(db, claimant_id);
    QString error = "";

    if (user.isNull() || task.isNull() || claimant.isNull()) {
        error = "Unable to generate OrgTaskRevokedEmail. Unable to find relevant data in the database. ";
        error += "Searched for user ids " + QString::number(user_id) + " and ";
        error += QString::number(claimant_id) + " and task id ";
        error += QString::number(task_id) + ".";
    }

    if (error.compare("") == 0) {
        ctemplate::TemplateDictionary dict("OrgTaskRevoked");
        dict.SetValue("USERNAME", Email::htmlspecialchars(user->display_name()));
        dict.SetValue("TASK_TITLE", Email::htmlspecialchars(task->title()));
        QString taskView = settings.get("site.url") + "task/" + QString::number(task->id()) + "/view";
        dict.SetValue("TASK_VIEW", taskView.toStdString());
        QString userProfile = settings.get("site.url") + QString::number(claimant->id()) + "/profile";
        dict.SetValue("USER_PROFILE", userProfile.toStdString());
        dict.SetValue("CLAIMANT_NAME", Email::htmlspecialchars(claimant->display_name()));
        dict.SetValue("SITE_NAME", std::string(settings.get("site.name").toLatin1().constData(), settings.get("site.name").toLatin1().length()));

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
        QString template_location = QString(TEMPLATE_DIRECTORY) + "emails/org-task-revoked.tpl";
        ctemplate::ExpandTemplate(template_location.toStdString(), ctemplate::DO_NOT_STRIP, &dict, &email_body);

        UserDao::queue_email(db, user_id, QString::fromStdString(user->email()), settings.get("site.name") + ": Task Revoked", QString::fromUtf8(email_body.c_str()));
        UserDao::log_email_sent(db, user_id, task_id, 0, 0, claimant_id, 0, 0, "task_revoked_to_subscribed_admin");
    } else {
        this->generateErrorEmail(error);
    }
}
