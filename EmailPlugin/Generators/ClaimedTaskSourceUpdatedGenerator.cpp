#include "ClaimedTaskSourceUpdatedGenerator.h"
#include "Common/protobufs/emails/ClaimedTaskSourceUpdated.pb.h"
using namespace  SolasMatch::Common::Protobufs::Emails;
ClaimedTaskSourceUpdatedGenerator::ClaimedTaskSourceUpdatedGenerator()
{
    // Default Constructor
}

void ClaimedTaskSourceUpdatedGenerator::run()
{
    qDebug() << "EmailGenerator: Starting new thread for tracked task source updated email";

    ClaimedTaskSourceUpdated emailMessage;
    emailMessage.ParseFromString(this->protoBody);

    ConfigParser settings;
    QString error = "";
    QSharedPointer<Email> email = QSharedPointer<Email>(new Email());
    QSharedPointer<MySQLHandler> db = MySQLHandler::getInstance();
    QSharedPointer<User> user = QSharedPointer<User>();
    QSharedPointer<Task> task = QSharedPointer<Task>();

    user = UserDao::getUser(db, emailMessage.user_id());
    task = TaskDao::getTask(db, emailMessage.task_id());

    if (user.isNull() || task.isNull()) {
        error = "Failed to generate claimed task source updated email.";
        error += "Unable to find relevant data in the DB, searched for user id ";
        error += QString::number(emailMessage.user_id()) + " and task id ";
        error += QString::number(emailMessage.task_id());
    }

    if (error == "") {
        ctemplate::TemplateDictionary dict("claimed-task-source-updated");

        dict.SetValue("USERNAME", Email::htmlspecialchars(user->display_name()));
        dict.SetValue("SITE_NAME", std::string(settings.get("site.name").toLatin1().constData(), settings.get("site.name").toLatin1().length()));
        dict.SetValue("TASK_TITLE", Email::htmlspecialchars(task->title()));
        QString uploadUrl = settings.get("site.url");
        uploadUrl += "task/" + QString::number(task->id()) + "/id";
        dict.SetValue("TASK_UPLOAD", uploadUrl.toStdString());

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
        QString template_location = QString(TEMPLATE_DIRECTORY) + "emails/claimed-task-source-updated.tpl";
        ctemplate::ExpandTemplate(template_location.toStdString(), ctemplate::DO_NOT_STRIP, &dict, &email_body);

        email->setSender(settings.get("site.system_email_address"));;
        email->addRecipient(QString::fromStdString(user->email()));
        email->setSubject(settings.get("site.name") + ": Task Source File Updated");
        email->setBody(QString::fromUtf8(email_body.c_str()));
    } else {
        email = this->generateErrorEmail(error);
    }

    this->emailQueue->insert(email, currentMessage);
}
