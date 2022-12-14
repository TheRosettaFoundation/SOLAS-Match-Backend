#include "UserTaskCancelledEmailGenerator.h"

#include "Common/protobufs/emails/JSON.h"

using namespace  SolasMatch::Common::Protobufs::Emails;

UserTaskCancelledEmailGenerator::UserTaskCancelledEmailGenerator()
{
    //Default Constructor
}

void UserTaskCancelledEmailGenerator::run()
{
    qDebug() << "EmailGenerator - Generating UserTaskCancelled";

    JSON email_message;
    email_message.ParseFromString(this->protoBody);

    ConfigParser settings;
    QString error = "";
    QSharedPointer<Email> email = QSharedPointer<Email>(new Email());
    QSharedPointer<User> user = QSharedPointer<User>();
    QSharedPointer<Task> task = QSharedPointer<Task>();
    QSharedPointer<MySQLHandler> db = MySQLHandler::getInstance();
    QList<QMap<QString, QVariant>> task_type_details = TaskDao::get_task_type_details(db);

    user = UserDao::getUser(db, email_message.user_id());
    task = TaskDao::getTask(db, email_message.task_id());

    if(user.isNull() || task.isNull()) {
        error = "Failed to generate UserTaskCancelled email: Unable to find relevant ";
        error += "information in the database. Searched for user ID ";
        error += QString::number(email_message.user_id()) + " and task ID ";
        error += QString::number(email_message.task_id()) + ".";
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

        email->setSender(settings.get("site.system_email_address"));;
        email->addRecipient(QString::fromStdString(user->email()));
        email->setSubject(settings.get("site.name") + ": Your task was cancelled - we are sorry for the inconvenience!");
        email->setBody(QString::fromUtf8(email_body.c_str()));
    } else {
        email = this->generateErrorEmail(error);
    }

    this->emailQueue->insert(email, currentMessage);
}
