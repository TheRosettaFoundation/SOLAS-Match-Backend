#include "TaskTranslationUploadedEmailGenerator.h"

TaskTranslationUploadedEmailGenerator::TaskTranslationUploadedEmailGenerator()
{
    //Default Constructor
}

void TaskTranslationUploadedEmailGenerator::run()
{
    qDebug() << "EmailGenerator - Generating TaskTranslationUploaded";

    TaskTranslationUploaded email_message;
    email_message.ParseFromString(this->protoBody.toStdString());

    ConfigParser settings;
    QString error = "";
    QSharedPointer<Email> email = QSharedPointer<Email>(new Email());
    QSharedPointer<User> user = QSharedPointer<User>();
    QSharedPointer<User> translator = QSharedPointer<User>();
    QSharedPointer<Task> task = QSharedPointer<Task>();
    QSharedPointer<Project> project = QSharedPointer<Project>();
    QSharedPointer<Organisation> org = QSharedPointer<Organisation>();
    MySQLHandler *db = new MySQLHandler(QUuid::createUuid().toString());

    if(db->init()) {
        user = UserDao::getUser(db, email_message.user_id());
        translator = UserDao::getUser(db, email_message.translator_id());
        task = TaskDao::getTask(db, email_message.task_id());

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

    } else {
        error = "Failed to generate task translation uploaded email: Unable to Connect to SQL Server.";
        error += " Check conf.ini for connection settings and make sure mysqld has been started.";
        qDebug() << "Unable to Connect to SQL Server. Check conf.ini and try again.";
    }

    if(error.compare("") == 0) {
        ctemplate::TemplateDictionary dict("task_translation_uploaded");
        if(user->display_name() != "") {
            dict.ShowSection("USER_HAS_NAME");
            dict["USERNAME"] = user->display_name();
        } else {
            dict.ShowSection("NO_USER_NAME");
        }
        dict["TRANSLATOR_NAME"] = translator->display_name();
        dict["TASK_TITLE"] = task->title();
        dict["ORG_NAME"] = org->name();

        QString dash_url = settings.get("site.url");
        dash_url += "client/dashboard";
        dict["DASHBOARD_URL"] = dash_url.toStdString();

        std::string email_body;
        QString template_location = QString(TEMPLATE_DIRECTORY) + "emails/task-translation-uploaded.tpl";
        ctemplate::ExpandTemplate(template_location.toStdString(), ctemplate::DO_NOT_STRIP, &dict, &email_body);

        email->setSender(settings.get("site.system_email_address"));;
        email->addRecipient(QString::fromStdString(user->email()));
        email->setSubject("Task Translation Uploaded Notification");
        email->setBody(QString::fromStdString(email_body));
    } else {
        email = this->generateErrorEmail(error);
    }

    delete db;

    this->emailQueue->enqueue(email);
}
