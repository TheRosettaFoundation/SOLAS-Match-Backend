#include "UserTaskRevokedGenerator.h"
using namespace  SolasMatch::Common::Protobufs::Emails;

UserTaskRevokedGenerator::UserTaskRevokedGenerator()
{
    // Default Constructor
}

void UserTaskRevokedGenerator::run()
{
    qDebug() << "Email Generator - Generating UserTaskRevokedEmail";
    UserTaskRevokedEmail emailMessage;
    emailMessage.ParseFromString(this->protoBody);

    ConfigParser settings;
    QSharedPointer<Email> email = QSharedPointer<Email>(new Email());
    QSharedPointer<MySQLHandler> db = MySQLHandler::getInstance();
    QSharedPointer<Task> task = TaskDao::getTask(db, emailMessage.task_id());
    QSharedPointer<User> user = UserDao::getUser(db, emailMessage.user_id());
    QString error;

    if (task.isNull() || user.isNull()) {
        error = "Unable to generate UserTaskRevokedEmail. Unable to find relevant data in the database. ";
        error += "Searched for user id " + QString::number(emailMessage.user_id()) + " and task id ";
        error += QString::number(emailMessage.task_id()) + ".";
    }

    if (error.compare("") == 0) {
        ctemplate::TemplateDictionary dict("UserTaskRevokedEmail");
        dict.SetValue("USERNAME", user->display_name());
        dict.SetValue("SITE_NAME", settings.get("site.name").toStdString());
        dict.SetValue("TASK_TITLE", task->title());
        QString taskView = settings.get("site.url") + "task/" + QString::number(task->id()) + "/view";
        dict.SetValue("TASK_VIEW", taskView.toStdString());

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
                task_type = "Proofreading";
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

        bool footer_enabled = (QString::compare("y", settings.get("email-footer.enabled")) == 0);
        if (footer_enabled)
        {
            QString donate_link = settings.get("email-footer.donate_link");
            ctemplate::TemplateDictionary* footer_dict = dict.AddIncludeDictionary("FOOTER");
            QString footer_location = QString(TEMPLATE_DIRECTORY) + "emails/footer.tpl";
            footer_dict -> SetValue("DONATE_LINK",donate_link.toStdString());
            footer_dict -> SetFilename(footer_location.toStdString());
        }

        std::string email_body;
        QString template_location = QString(TEMPLATE_DIRECTORY) + "emails/user-task-revoked.tpl";
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
