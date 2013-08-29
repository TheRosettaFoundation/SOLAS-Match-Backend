#include "ClaimedTaskUploadedGenerator.h"

#include "Common/protobufs/emails/ClaimedTaskUploaded.pb.h"

ClaimedTaskUploadedGenerator::ClaimedTaskUploadedGenerator()
{
    // Default Constructor
}

void ClaimedTaskUploadedGenerator::run()
{
    qDebug() << "EmailGenerator: Starting new thread for tracked task source updated email";

    ClaimedTaskUploaded emailMessage;
    emailMessage.ParseFromString(this->protoBody.toStdString());

    ConfigParser settings;
    QString error = "";
    QSharedPointer<Email> email = QSharedPointer<Email>(new Email());
    QSharedPointer<MySQLHandler> db = MySQLHandler::getInstance();
    QSharedPointer<User> user = UserDao::getUser(db, emailMessage.user_id());
    QSharedPointer<Task> task = TaskDao::getTask(db, emailMessage.task_id());
    QSharedPointer<Project> project = QSharedPointer<Project>();
    QSharedPointer<Organisation> org = QSharedPointer<Organisation>();

    if (user.isNull() || task.isNull()) {
        error = "Unable to generate claimed task uploaded email. Unable to find relevant data ";
        error += "in the DB, searched for user id " + QString::number(emailMessage.user_id());
        error += " and task id " + QString::number(emailMessage.task_id());
    } else {
        project = ProjectDao::getProject(db, task->projectid());

        if (project.isNull()) {
            error += "Unable to generate claimed task uploaded email. Unable to find relevant data ";
            error += "in the DB, searched for project id " + task->projectid();
        } else {
            org = OrganisationDao::getOrg(db, project->organisationid());

            if (org.isNull()) {
                error += "Unable to generate claimed task uploaded email. Unable to find relevant data ";
                error += "in the DB, searched for organisation id " + project->organisationid();
            }
        }
    }

    if (error == "") {
        ctemplate::TemplateDictionary dict("claimed-task-uploaded");

        dict.SetValue("USERNAME", user->display_name());
        dict.SetValue("SITE_NAME", settings.get("site.name").toStdString());
        dict.SetValue("TASK_TITLE", task->title());
        dict.SetValue("ORG_NAME", org->name());
        QString uploadUrl = settings.get("site.url");
        uploadUrl += "task/" + QString::number(task->id()) + "/id";
        dict.SetValue("TASK_UPLOAD", uploadUrl.toStdString());

        std::string email_body;
        QString template_location = QString(TEMPLATE_DIRECTORY) + "emails/claimed-task-uploaded.tpl";
        ctemplate::ExpandTemplate(template_location.toStdString(), ctemplate::DO_NOT_STRIP, &dict, &email_body);

        email->setSender(settings.get("site.system_email_address"));;
        email->addRecipient(QString::fromStdString(user->email()));
        email->setSubject(settings.get("site.name") + ": Task Successfully Uploaded");
        email->setBody(QString::fromUtf8(email_body.c_str()));
    } else {
        email = this->generateErrorEmail(error);
    }

    this->emailQueue->insert(email, currentMessage);
}
