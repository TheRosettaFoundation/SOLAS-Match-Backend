#include "PootleProjectCreatedGenerator.h"

#include "Common/protobufs/emails/PootleProjectCreated.pb.h"

PootleProjectCreatedGenerator::PootleProjectCreatedGenerator()
{
    // Default ctor
}

void PootleProjectCreatedGenerator::run()
{
    qDebug() << "IEmailGenerator: Generating Pootle Project Created Email";

    PootleProjectCreated emailMessage;
    emailMessage.ParseFromString(this->protoBody.toStdString());

    ConfigParser settings;
    QString error = "";
    QSharedPointer<Email> email = QSharedPointer<Email>(new Email());
    QSharedPointer<MySQLHandler> db = MySQLHandler::getInstance();
    QSharedPointer<User> user = UserDao::getUser(db, emailMessage.user_id());
    QSharedPointer<Task> task = TaskDao::getTask(db, emailMessage.task_id());

    if (user.isNull() || task.isNull()) {
        error = "PootleProjectCreatedEmail generation failed. Unable to find relevant data in the DB. ";
        error += "Searched for user " + QString::number(emailMessage.user_id()) + " and task ";
        error += QString::number(emailMessage.task_id());
    }

    if (error == "") {
        ctemplate::TemplateDictionary dict("PootleProjectCreated");
        dict.SetValue("USERNAME", user->display_name());

        QString taskView = settings.get("site.url") + "task/" + QString::number(task->id()) + "/view";
        dict.SetValue("TASK_VIEW", taskView.toStdString());
        dict.SetValue("TASK_NAME", task->title());
        dict.SetValue("POOTLE_LINK", emailMessage.link());
        dict.SetValue("SITE_NAME", settings.get("site.name").toStdString());

        std::string email_body;
        QString template_location = QString(TEMPLATE_DIRECTORY) + "emails/pootle-project-created.tpl";
        ctemplate::ExpandTemplate(template_location.toStdString(), ctemplate::DO_NOT_STRIP, &dict, &email_body);

        email->setSender(settings.get("site.system_email_address"));;
        email->addRecipient(QString::fromStdString(user->email()));
        email->setSubject(settings.get("site.name") + ": Pootle Project Created");
        email->setBody(QString::fromUtf8(email_body.c_str()));
    } else {
        email = this->generateErrorEmail(error);
    }

    this->emailQueue->insert(email, currentMessage);
}
