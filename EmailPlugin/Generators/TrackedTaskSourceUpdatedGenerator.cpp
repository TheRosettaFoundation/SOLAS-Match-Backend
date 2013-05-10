#include "TrackedTaskSourceUpdatedGenerator.h"

#include "Common/protobufs/emails/TrackedTaskSourceUpdated.pb.h"

TrackedTaskSourceUpdatedGenerator::TrackedTaskSourceUpdatedGenerator()
{
    // Default Constructor
}

void TrackedTaskSourceUpdatedGenerator::run()
{
    qDebug() << "EmailGenerator: Starting new thread for tracked task source updated email";

    TrackedTaskSourceUpdated emailMessage;
    emailMessage.ParseFromString(this->protoBody.toStdString());

    ConfigParser settings;
    QString error = "";
    QSharedPointer<Email> email = QSharedPointer<Email>(new Email());
    QSharedPointer<MySQLHandler> db = MySQLHandler::getInstance();
    QSharedPointer<User> user = UserDao::getUser(db, emailMessage.user_id());
    QSharedPointer<Task> task = TaskDao::getTask(db, emailMessage.task_id());
    QSharedPointer<User> translator = QSharedPointer<User>();
    if (emailMessage.has_translator_id()) {
        translator = UserDao::getUser(db, emailMessage.translator_id());
    }

    if (user.isNull() || task.isNull()) {
        error = "Unable to generate claimed task source updated email. Unable to find ";
        error += "relevant information in the DB, search for user id " + QString::number(emailMessage.user_id());
        error += " and task id " + QString::number(emailMessage.task_id());
    }

    if (error == "") {
        ctemplate::TemplateDictionary dict("claimed-task-source-updated");

        dict.SetValue("USERNAME", user->display_name());
        dict.SetValue("TASK_TITLE", task->title());

        if (!translator.isNull()) {
            ctemplate::TemplateDictionary *translatorSect = dict.AddSectionDictionary("TRANSLATOR_SECT");
            translatorSect->SetValue("TRANSLATOR_NAME", translator->display_name());
        }

        QString taskView = settings.get("site.url");
        taskView += "task/" + QString::number(task->id()) + "/view";
        dict.SetValue("TASK_VIEW", taskView.toStdString());

        QString projectView = settings.get("site.url");
        projectView += "project/" + QString::number(task->projectid()) + "/view";
        dict.SetValue("PROJECT_VIEW", projectView.toStdString());

        std::string email_body;
        QString template_location = QString(TEMPLATE_DIRECTORY) + "emails/tracked-task-source-updated.tpl";
        ctemplate::ExpandTemplate(template_location.toStdString(), ctemplate::DO_NOT_STRIP, &dict, &email_body);

        email->setSender(settings.get("site.system_email_address"));;
        email->addRecipient(QString::fromStdString(user->email()));
        email->setSubject("Tracked Task Updated");
        email->setBody(QString::fromStdString(email_body));
    } else {
        email = this->generateErrorEmail(error);
    }

    this->emailQueue->insert(email, currentMessage);
}
