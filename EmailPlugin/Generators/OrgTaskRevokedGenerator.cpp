#include "OrgTaskRevokedGenerator.h"

OrgTaskRevokedGenerator::OrgTaskRevokedGenerator()
{
    // Default Constructor
}

void OrgTaskRevokedGenerator::run()
{
    qDebug() << "Email Generator - Generating OrgTaskRevokedEmail";
    OrgTaskRevokedEmail emailMessage;
    emailMessage.ParseFromString(this->protoBody.toStdString());

    ConfigParser settings;
    QSharedPointer<Email> email = QSharedPointer<Email>(new Email());
    QSharedPointer<MySQLHandler> db = MySQLHandler::getInstance();
    QSharedPointer<User> user = UserDao::getUser(db, emailMessage.user_id());
    QSharedPointer<Task> task = TaskDao::getTask(db, emailMessage.task_id());
    QSharedPointer<User> claimant = UserDao::getUser(db, emailMessage.claimant_id());
    QString error = "";

    if (user.isNull() || task.isNull() || claimant.isNull()) {
        error = "Unable to generate OrgTaskRevokedEmail. Unable to find relevant data in the database. ";
        error += "Searched for user ids " + QString::number(emailMessage.user_id()) + " and ";
        error += QString::number(emailMessage.claimant_id()) + " and task id ";
        error += QString::number(emailMessage.task_id()) + ".";
    }

    if (error.compare("") == 0) {
        ctemplate::TemplateDictionary dict("OrgTaskRevoked");
        dict.SetValue("USERNAME", user->display_name());
        dict.SetValue("TASK_TITLE", task->title());
        QString taskView = settings.get("site.url") + "task/" + QString::number(task->id()) + "/view";
        dict.SetValue("TASK_VIEW", taskView.toStdString());
        QString userProfile = settings.get("site.url") + QString::number(claimant->id()) + "/profile";
        dict.SetValue("USER_PROFILE", userProfile.toStdString());
        dict.SetValue("CLAIMANT_NAME", claimant->display_name());
        dict.SetValue("SITE_NAME", settings.get("site.name").toStdString());

        std::string email_body;
        QString template_location = QString(TEMPLATE_DIRECTORY) + "emails/org-task-revoked.tpl";
        ctemplate::ExpandTemplate(template_location.toStdString(), ctemplate::DO_NOT_STRIP, &dict, &email_body);

        email->setSender(settings.get("site.system_email_address"));
        email->addRecipient(QString::fromStdString(user->email()));
        email->setSubject(settings.get("site.name") + ": Task Revoked");
        email->setBody(QString::fromUtf8(email_body.c_str()));
    } else {
        email = this->generateErrorEmail(error);
    }
    this->emailQueue->insert(email, currentMessage);
}
