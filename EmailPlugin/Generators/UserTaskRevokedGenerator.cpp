#include "UserTaskRevokedGenerator.h"

UserTaskRevokedGenerator::UserTaskRevokedGenerator()
{
    // Default Constructor
}

void UserTaskRevokedGenerator::run(int task_id, int claimant_id)
{
    qDebug() << "Email Generator - Generating UserTaskRevokedEmail";

    ConfigParser settings;
    QSharedPointer<MySQLHandler> db = MySQLHandler::getInstance();
    QList<QMap<QString, QVariant>> task_type_details = TaskDao::get_task_type_details(db);
    QSharedPointer<Task> task = TaskDao::getTask(db, task_id);
    QSharedPointer<User> user = UserDao::getUser(db, claimant_id);
    QString error;

    if (task.isNull() || user.isNull()) {
        error = "Unable to generate UserTaskRevokedEmail. Unable to find relevant data in the database. ";
        error += "Searched for user id " + QString::number(claimant_id) + " and task id ";
        error += QString::number(task_id) + ".";
    }

    if (error.compare("") == 0) {
        ctemplate::TemplateDictionary dict("UserTaskRevokedEmail");
        dict.SetValue("USERNAME", Email::htmlspecialchars(user->display_name()));
        dict.SetValue("SITE_NAME", std::string(settings.get("site.name").toLatin1().constData(), settings.get("site.name").toLatin1().length()));
        dict.SetValue("TASK_TITLE", Email::htmlspecialchars(task->title()));
        QString taskView = settings.get("site.url") + "task/" + QString::number(task->id()) + "/view";
        dict.SetValue("TASK_VIEW", taskView.toStdString());

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

        bool footer_enabled = (QString::compare("y", settings.get("email-footer.enabled")) == 0);
        if (footer_enabled)
        {
            QString donate_link = settings.get("email-footer.donate_link");
            ctemplate::TemplateDictionary* footer_dict = dict.AddIncludeDictionary("FOOTER");
            QString footer_location = QString(TEMPLATE_DIRECTORY) + "emails/footer.tpl";
            footer_dict -> SetValue("DONATE_LINK",donate_link.toStdString());
            footer_dict -> SetFilename(footer_location.toStdString());
        }

        std::string email_body;
        QString template_location = QString(TEMPLATE_DIRECTORY) + "emails/user-task-revoked.tpl";
        ctemplate::ExpandTemplate(template_location.toStdString(), ctemplate::DO_NOT_STRIP, &dict, &email_body);

        UserDao::queue_email(db, claimant_id, QString::fromStdString(user->email()), settings.get("site.name") + ": Task Revoked", QString::fromUtf8(email_body.c_str()));
//queue_email (int recipient_id, QString recipient_email, QString subject, QString body) also logged_time; Sender: settings.get("site.system_email_address")
        UserDao::log_email_sent(db, claimant_id, task_id, 0, 0, 0, 0, 0, "task_revoked_to_volunteer");
    } else {
        this->generateErrorEmail(error);
    }
}
