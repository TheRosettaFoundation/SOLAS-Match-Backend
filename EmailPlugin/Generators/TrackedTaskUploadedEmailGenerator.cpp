#include "TrackedTaskUploadedEmailGenerator.h"
using namespace  SolasMatch::Common::Protobufs::Emails;

TrackedTaskUploadedEmailGenerator::TrackedTaskUploadedEmailGenerator()
{
    //Default Constructor
}

void TrackedTaskUploadedEmailGenerator::run()
{
    qDebug() << "EmailGenerator - Generating TrackedTaskUploaded email";

    TrackedTaskUploaded email_message;
    email_message.ParseFromString(this->protoBody);

    ConfigParser settings;
    QString error = "";
    QSharedPointer<Email> email = QSharedPointer<Email>(new Email());
    QSharedPointer<MySQLHandler> db = MySQLHandler::getInstance();
    QSharedPointer<User> user = UserDao::getUser(db, email_message.user_id());
    QSharedPointer<User> translator = UserDao::getUser(db, email_message.translator_id());
    QSharedPointer<Task> task = TaskDao::getTask(db, email_message.task_id());
    QSharedPointer<Project> project = QSharedPointer<Project>();
    QSharedPointer<Organisation> org = QSharedPointer<Organisation>();

    if(user.isNull() || translator.isNull() || task.isNull()) {
        error = "Failed to generate task translation uploaded email. Unable ";
        error += "to find relevant inforamtion in the Database. Searched for ";
        error += "User ID " + QString::number(email_message.user_id()) + ", ";
        error += "Translator ID " + QString::number(email_message.translator_id());
        error += " and task and project identified by task ID ";
        error += QString::number(email_message.task_id()) + ".";
    } else {
        project = ProjectDao::getProject(db, task->projectid());

        if (project.isNull()) {
            error = "Failed to generate task translation uploaded email. Unable ";
            error += "to find relevant inforamtion in the Database. Could not find ";
            error += "project with ID " + QString::number(task->projectid());
        } else {
            org = OrganisationDao::getOrg(db, project->organisationid());

            if(org.isNull()) {
                error = "Failed to generate task translation uploaded email. Unable ";
                error += "to find relevant inforamtion in the Database. Could not find ";
                error += "Organisation with ID " + QString::number(project->organisationid()) + ".";
            }
        }
    }

    if(error.compare("") == 0) {
        ctemplate::TemplateDictionary dict("tracked-task-uploaded");

        dict.SetValue("USERNAME", Email::htmlspecialchars(user->display_name()));
        dict.SetValue("TRANSLATOR_NAME", Email::htmlspecialchars(translator->display_name()));
        dict.SetValue("TASK_TITLE", Email::htmlspecialchars(task->title()));
        dict.SetValue("ORG_NAME", org->name());
        dict.SetValue("SITE_NAME", std::string(settings.get("site.name").toLatin1().constData(), settings.get("site.name").toLatin1().length()));

        QString task_type = "Translation";
        switch(task->tasktype())
        {
            case 1:
                task_type = "Segmentation";
                break;
            case 2:
                task_type = "Translation";
                break;
            case 3:
                task_type = "Revising";
                break;
            case 4:
                task_type = "Desegmentation";
                break;
        }

        dict.SetValue("TASK_TYPE", task_type.toStdString());

        Locale taskSourceLocale =  task->sourcelocale();
        Locale taskTargetLocale = task->targetlocale();
        dict.SetValue("SOURCE_LANGUAGE",taskSourceLocale.languagename());
        dict.SetValue("TARGET_LANGUAGE",taskTargetLocale.languagename());


        QString reviewUrl = settings.get("site.url");
        reviewUrl += "org/" + QString::number(org->id()) + "/task/" + QString::number(task->id()) + "/review";
        dict.SetValue("TASK_REVIEW", reviewUrl.toStdString());

        QString dash_url = settings.get("site.url");
        dash_url += "org/dashboard";
        dict.SetValue("DASHBOARD_URL", dash_url.toStdString());

        QString taskView = settings.get("site.url");
        taskView += "task/" + QString::number(task->id()) + "/view";
        dict.SetValue("TASK_VIEW", taskView.toStdString());

        QString projectView = settings.get("site.url");
        projectView += "project/" + QString::number(task->projectid()) + "/view";
        dict.SetValue("PROJECT_VIEW", projectView.toStdString());

        QMap<QString, QVariant> memsource_task = TaskDao::get_memsource_task(db, task->id());

        if (TaskDao::is_chunked_task(db, task->id())) {
            dict.SetValue("MATECAT_REVISION", TaskDao::getMatecatRevisionURL(db, task));
        }

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

        bool is_revisor_for_split_memsource_task = false;
        if (!memsource_task.isEmpty()) {
            if (task->tasktype() == 2) { // Translation
                QList<QSharedPointer<Task> > revision_tasks = TaskDao::get_matching_revision_memsource_tasks(db, task);
                foreach (QSharedPointer<Task> revision_task, revision_tasks) {
//qDebug() << "TrackedTaskUploadedEmailGenerator Matching Revision Task:" << QString::number(revision_task->id());//(**)
                    QSharedPointer<User> revisionClaimer = TaskDao::getUserClaimedTask(db, revision_task->id());
                    if (!revisionClaimer.isNull()) {
                        if (user->id() == revisionClaimer->id()) {
//qDebug() << "TrackedTaskUploadedEmailGenerator tracked-task-uploaded-notify-revisor-memsource for revisionClaimer->id():" << QString::number(revisionClaimer->id());//(**)
                            is_revisor_for_split_memsource_task = true;
                            dict.SetValue("MATECAT_REVISION", TaskDao::get_matecat_url(db, revision_task, TaskDao::get_memsource_task(db, revision_task->id())));
                        }
                    }
                }
            }
        }

        if (is_revisor_for_split_memsource_task) {
            template_location = QString(TEMPLATE_DIRECTORY) + "emails/tracked-task-uploaded-notify-revisor-memsource.tpl";
        } else {
        if (TaskDao::is_chunked_task(db, task->id())) {
            template_location = QString(TEMPLATE_DIRECTORY) + "emails/tracked-task-uploaded-chunk.tpl";
        } else {
            template_location = QString(TEMPLATE_DIRECTORY) + "emails/tracked-task-uploaded.tpl";
        }
        }
        ctemplate::ExpandTemplate(template_location.toStdString(), ctemplate::DO_NOT_STRIP, &dict, &email_body);

        email->setSender(settings.get("site.system_email_address"));;
        email->addRecipient(QString::fromStdString(user->email()));
        email->setSubject(settings.get("site.name") + ": Task Completed Notification");
        email->setBody(QString::fromUtf8(email_body.c_str()));
    } else {
        email = this->generateErrorEmail(error);
    }

    this->emailQueue->insert(email, currentMessage);
}
