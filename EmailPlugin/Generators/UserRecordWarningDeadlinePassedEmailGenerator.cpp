#include "UserRecordWarningDeadlinePassedEmailGenerator.h"

#include <QDateTime>

using namespace  SolasMatch::Common::Protobufs::Emails;

UserRecordWarningDeadlinePassedEmailGenerator::UserRecordWarningDeadlinePassedEmailGenerator()
{
    //Default Constructor
}

void UserRecordWarningDeadlinePassedEmailGenerator::run()
{
    qDebug() << "EmailGenerator: Generating UserRecordWarningDeadlinePassed email";

    UserRecordWarningDeadlinePassed email_message;
    email_message.ParseFromString(this->protoBody);

    ConfigParser settings;
    QString error = "";
    QSharedPointer<Email> email = QSharedPointer<Email>(new Email);
    QSharedPointer<User> user = QSharedPointer<User>();
    QSharedPointer<Task> task = QSharedPointer<Task>();
    QSharedPointer<MySQLHandler> db = MySQLHandler::getInstance();
    bool sendMessage = true;


    user = UserDao::getUser(db, email_message.translator_id());
    task = TaskDao::getTask(db, email_message.task_id());

    if(!user || !task) {
        error = "Failed to generate UserRecordWarningDeadlinePassed email: Unable to find relevant ";
        error += "data in the Database. Searched for User ID ";
        error += QString::number(email_message.translator_id()) + " and Task ID ";
        error += QString::number(email_message.task_id()) + ".";
    }

    if(error.compare("") == 0) {
        ctemplate::TemplateDictionary dict("user_claimed_task_late_warning_deadline_passed");
        if(user->display_name() != "") {
            dict.ShowSection("USER_HAS_NAME");
            dict.SetValue("USERNAME", Email::htmlspecialchars(user->display_name()));
        } else {
            dict.ShowSection("NO_USER_NAME");
        }
        dict.SetValue("TASK_TITLE", Email::htmlspecialchars(task->title()));
        dict.SetValue("SITE_NAME", std::string(settings.get("site.name").toLatin1().constData(), settings.get("site.name").toLatin1().length()));

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
                if (!memsource_task.isEmpty()) {
                    dict.ShowSection("REVISING");
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

        QString deadline = QDateTime::fromString(QString::fromStdString(task->deadline()), "yyyy-MM-ddTHH:mm:ss").toString("d MMMM yyyy - hh:mm");
        dict.SetValue("DEADLINE_TIME", deadline.toStdString());

        QString uploadUrl = settings.get("site.url");
        uploadUrl += "task/" + QString::number(task->id()) + "/id";
        dict.SetValue("TASK_UPLOAD", uploadUrl.toStdString());

        dict.SetValue("MATECAT", TaskDao::get_matecat_url(db, task, memsource_task));

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

      if (!memsource_task.isEmpty()) {
          if (task->tasktype() == 3) { // Revising
              if (!TaskDao::is_task_translated_in_memsource(db, task)) sendMessage = false;
//if (!TaskDao::is_task_translated_in_memsource(db, task)) qDebug() << "UserRecord NOT send warning:" << QString::number(task->id());//(**)
//else  qDebug() << "UserRecord send warning:" << QString::number(task->id());//(**)
          }

          template_location = QString(TEMPLATE_DIRECTORY) + "emails/user-claimed-task-late-warning-deadline-passed-memsource.tpl";
      } else {
        if (TaskDao::is_chunked_task(db, task->id())) {
            if (task->tasktype() == 3) {
                QSharedPointer<Task> translationTask = TaskDao::getMatchingTask(db, task->id(), TRANSLATION);
                if (!translationTask.isNull()) {
                    if (translationTask->taskstatus() != COMPLETE) {
                        sendMessage = false;
                    }
                }
            }

            template_location = QString(TEMPLATE_DIRECTORY) + "emails/user-claimed-task-late-warning-deadline-passed-chunk.tpl";
        } else {
            template_location = QString(TEMPLATE_DIRECTORY) + "emails/user-claimed-task-late-warning-deadline-passed.tpl";
        }
      }
        ctemplate::ExpandTemplate(template_location.toStdString(), ctemplate::DO_NOT_STRIP, &dict, &email_body);

        email->setSender(settings.get("site.system_email_address"));;
        email->addRecipient(QString::fromStdString(user->email()));
        email->setSubject(settings.get("site.name") + ": Task Overdue");
        email->setBody(QString::fromUtf8(email_body.c_str()));
    } else {
        email = this->generateErrorEmail(error);
    }

    if (sendMessage) this->emailQueue->insert(email, currentMessage);
}
