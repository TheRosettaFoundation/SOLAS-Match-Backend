#include "UserTaskClaimEmailGenerator.h"

#include "Common/protobufs/emails/JSON.h"

using namespace  SolasMatch::Common::Protobufs::Emails;

UserTaskClaimEmailGenerator::UserTaskClaimEmailGenerator()
{
    //Default Constructor
}

void UserTaskClaimEmailGenerator::run()
{
    qDebug() << "EmailGenerator - Generating UserTaskClaim";

    JSON email_message;
    email_message.ParseFromString(this->protoBody);

    ConfigParser settings;
    QString error = "";
    QSharedPointer<Email> email = QSharedPointer<Email>(new Email());
    QSharedPointer<User> user = QSharedPointer<User>();
    QSharedPointer<Task> task = QSharedPointer<Task>();
    QSharedPointer<MySQLHandler> db = MySQLHandler::getInstance();

    user = UserDao::getUser(db, email_message.user_id());
    task = TaskDao::getTask(db, email_message.task_id());

    if(user.isNull() || task.isNull()) {
        error = "Failed to generate UserTaskClaim email: Unable to find relevant ";
        error += "data in the Database. Searched for User ID ";
        error += QString::number(email_message.user_id()) + " and Task ID ";
        error += QString::number(email_message.task_id()) + ".";
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
        task_url += "task/" + QString::number(task->id()) + "/id";
        dict.SetValue("TASK_PAGE", task_url.toStdString());
        dict.SetValue("SITE_NAME", std::string(settings.get("site.name").toLatin1().constData(), settings.get("site.name").toLatin1().length()));
        dict.SetValue("TASK_TITLE", Email::htmlspecialchars(task->title()));

        QMap<QString, QVariant> memsource_task = TaskDao::get_memsource_task(db, task->id());

        QString task_type = "Translation";
        switch(task->tasktype())
        {
            case 1:
                task_type = "Segmentation";
                dict.ShowSection("SEGMENTATION");
                break;
            case 2:
                task_type = "Translation";
                dict.ShowSection("TRANSLATION");
                break;
            case 3:
                task_type = "Revising";
                if (!memsource_task.isNull()) {
                    if (TaskDao::is_task_translated_in_memsource(db, task)) {
                        dict.ShowSection("REVISING");
                    } else {
                        dict.ShowSection("REVISING_WAIT");
                    }
                } else {
                if (TaskDao::is_task_translated_in_matecat(db, task->id())) {
                dict.ShowSection("REVISING");
                } else {
                    dict.ShowSection("REVISING_NO_MATECAT");
                }
                }
                break;
            case 4:
                task_type = "Desegmentation";
                dict.ShowSection("SEGMENTATION");
                break;
        }

        dict.SetValue("TASK_TYPE", task_type.toStdString());

        Locale taskSourceLocale =  task->sourcelocale();
        Locale taskTargetLocale = task->targetlocale();
        dict.SetValue("SOURCE_LANGUAGE",taskSourceLocale.languagename());
        dict.SetValue("TARGET_LANGUAGE",taskTargetLocale.languagename());

        dict.SetValue("MATECAT", TaskDao::get_matecat_url(db, task));

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
           if (!memsource_task.isNull()) {
            template_location = QString(TEMPLATE_DIRECTORY) + "emails/user-task-claim-memsource.tpl";
           } else {
            template_location = QString(TEMPLATE_DIRECTORY) + "emails/user-task-claim.tpl";
           }
          }
        }
        ctemplate::ExpandTemplate(template_location.toStdString(), ctemplate::DO_NOT_STRIP, &dict, &email_body);

        email->setSender(settings.get("site.system_email_address"));;
        email->addRecipient(QString::fromStdString(user->email()));

        if (task->title().length() == 8 && task->title().find("Test") == 0) { // Verification Task
            email->setSubject(settings.get("site.name") + ": Test to become a Verified Translator");
        } else {
        email->setSubject(settings.get("site.name") + ": Task Claim Notification");
        }
        email->setBody(QString::fromUtf8(email_body.c_str()));
    } else {
        email = this->generateErrorEmail(error);
    }

    this->emailQueue->insert(email, currentMessage);
}
