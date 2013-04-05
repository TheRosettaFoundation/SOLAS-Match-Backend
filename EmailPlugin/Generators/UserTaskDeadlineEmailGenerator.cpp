#include "UserTaskDeadlineEmailGenerator.h"

UserTaskDeadlineEmailGenerator::UserTaskDeadlineEmailGenerator()
{
    //Default Constructor
}

void UserTaskDeadlineEmailGenerator::run()
{
    qDebug() << "EmailGenerator: Generating UserClaimedTaskDeadlinePassed email";

    UserClaimedTaskDeadlinePassed email_message;
    email_message.ParseFromString(this->protoBody.toStdString());

    ConfigParser settings;
    QString error = "";
    QSharedPointer<Email> email = QSharedPointer<Email>(new Email);
    QSharedPointer<User> user = QSharedPointer<User>();
    QSharedPointer<Task> task = QSharedPointer<Task>();
    MySQLHandler* db = new MySQLHandler(QUuid::createUuid().toString());

    if(db->init()) {
        user = UserDao::getUser(db, email_message.translator_id());
        task = TaskDao::getTask(db, email_message.task_id());

        if(!user || !task) {
            error = "Failed to generate UserClaimedTaskDeadlinePassed email: Unable to find relevant ";
            error += "data in the Database. Searched for User ID ";
            error += QString::number(email_message.translator_id()) + " and Task ID ";
            error += QString::number(email_message.task_id()) + ".";
        }
    } else {
        error = "Failed to generate user UserClaimedTaskDeadlinePassed: Unable to Connect to SQL Server.";
        error += " Check conf.ini for connection settings and make sure mysqld has been started.";
        qDebug() << "Unable to Connect to SQL Server. Check conf.ini and try again.";
    }

    if(error.compare("") == 0) {
        ctemplate::TemplateDictionary dict("user_claimed_task_deadline_exceeded");
        if(user->display_name() != "") {
            dict.ShowSection("USER_HAS_NAME");
            dict["USERNAME"] = user->display_name();
        } else {
            dict.ShowSection("NO_USER_NAME");
        }
        dict["TASK_TITLE"] = task->title();

        std::string email_body;
        QString template_location = QString(TEMPLATE_DIRECTORY) + "emails/user-claimed-task-deadline-passed.tpl";
        ctemplate::ExpandTemplate(template_location.toStdString(), ctemplate::DO_NOT_STRIP, &dict, &email_body);

        email->setSender(settings.get("site.system_email_address"));;
        email->addRecipient(QString::fromStdString(user->email()));
        email->setSubject("Task Claim Notification");
        email->setBody(QString::fromStdString(email_body));
    } else {
        email = this->generateErrorEmail(error);
    }

    delete db;

    this->emailQueue->enqueue(email);
}
