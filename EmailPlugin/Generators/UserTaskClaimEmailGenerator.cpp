#include "UserTaskClaimEmailGenerator.h"

UserTaskClaimEmailGenerator::UserTaskClaimEmailGenerator()
{
    //Default Constructor
}

void UserTaskClaimEmailGenerator::run()
{
    qDebug() << "EmailGenerator - Generating UserTaskClaim";

    UserTaskClaim email_message;
    email_message.ParseFromString(this->protoBody.toStdString());

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
            dict["USERNAME"] = user->display_name();
        } else {
            dict.ShowSection("NO_USER_NAME");
        }

        QString task_url = settings.get("site.url");
        task_url += "task/" + QString::number(task->id()) + "/id";
        dict["TASK_PAGE"] = task_url.toStdString();

        std::string email_body;
        QString template_location = QString(TEMPLATE_DIRECTORY) + "emails/user-task-claim.tpl";
        ctemplate::ExpandTemplate(template_location.toStdString(), ctemplate::DO_NOT_STRIP, &dict, &email_body);

        email->setSender(settings.get("site.system_email_address"));;
        email->addRecipient(QString::fromStdString(user->email()));
        email->setSubject("Task Claim Notification");
        email->setBody(QString::fromStdString(email_body));
    } else {
        email = this->generateErrorEmail(error);
    }

    this->emailQueue->insert(email, currentMessage);
}
