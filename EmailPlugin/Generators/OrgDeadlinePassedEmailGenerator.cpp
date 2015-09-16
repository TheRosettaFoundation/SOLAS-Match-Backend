#include "OrgDeadlinePassedEmailGenerator.h"
using namespace  SolasMatch::Common::Protobufs::Emails;

OrgDeadlinePassedMailGenerator::OrgDeadlinePassedMailGenerator()
{
    //Default Constructor
}

void OrgDeadlinePassedMailGenerator::run()
{
    qDebug() << "EmailGenerator - Generating OrgTaskDeadlinePassed";

    OrgTaskDeadlinePassed email_message;
    email_message.ParseFromString(this->protoBody);

    ConfigParser settings;
    QString error = "";
    QSharedPointer<Email> email = QSharedPointer<Email>(new Email());
    QSharedPointer<User> user = QSharedPointer<User>();
    QSharedPointer<User> translator = QSharedPointer<User>();
    QSharedPointer<Task> task = QSharedPointer<Task>();
    QSharedPointer<MySQLHandler> db = MySQLHandler::getInstance();

    translator = UserDao::getUser(db, email_message.translator_id());
    task = TaskDao::getTask(db, email_message.task_id());
    user = UserDao::getUser(db, email_message.user_id());

    if(user.isNull() || task.isNull() || translator.isNull()) {
        error = "OrgTaskDeadlinePassed generation failed. Data missing from the DB.";
        error += "Searched for user ID " + QString::number(email_message.translator_id());
        error += " and " + QString::number(email_message.user_id());
        error += " and task ID " + QString::number(email_message.task_id());
    }

    if(error.compare("") == 0) {
        ctemplate::TemplateDictionary dict("OrgTaskDeadlinePassed");
        if(user->display_name() != "") {
            dict.ShowSection("USER_HAS_NAME");
            dict.SetValue("USERNAME", user->display_name());
        } else {
            dict.ShowSection("NO_USER_NAME");
        }
        dict.SetValue("TASK_TITLE", task->title());
        dict.SetValue("SITE_NAME", settings.get("site.name").toStdString());

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
        QString template_location = QString(TEMPLATE_DIRECTORY) + "emails/org-task-deadline-passed.tpl";
        ctemplate::ExpandTemplate(template_location.toStdString(), ctemplate::DO_NOT_STRIP, &dict, &email_body);

        email->setSender(settings.get("site.system_email_address"));
        email->addRecipient(QString::fromStdString(user->email()));
        email->setSubject(settings.get("site.name") + ": Task Update");
        email->setBody(QString::fromUtf8(email_body.c_str()));
    } else {
        email = this->generateErrorEmail(error);
    }

    this->emailQueue->insert(email, currentMessage);
}
