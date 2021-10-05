#include "UserRecordWarningDeadlinePassedEmailGenerator.h"

#include <QDateTime>

using namespace  SolasMatch::Common::Protobufs::Emails;

UserRecordWarningDeadlinePassedEmailGenerator::UserRecordWarningDeadlinePassedEmailGenerator()
{
    //Default Constructor
}

void UserRecordWarningDeadlinePassedEmailGenerator::run()
{
    qDebug() << "EmailGenerator: Generating UserRecordWarningDeadlinePassed email";

    UserRecordWarningDeadlinePassed email_message;
    email_message.ParseFromString(this->protoBody);

    ConfigParser settings;
    QString error = "";
    QSharedPointer<Email> email = QSharedPointer<Email>(new Email);
    QSharedPointer<User> user = QSharedPointer<User>();
    QSharedPointer<MySQLHandler> db = MySQLHandler::getInstance();
    bool sendMessage = true;


    user = UserDao::getUser(db, email_message.user_id());
    if (!user) {
        error = "Failed to generate UserRecordWarningDeadlinePassed email: Unable to find User for user_id: ";
        error += QString::number(email_message.user_id());
    }

    if (error.compare("") == 0) {
        ctemplate::TemplateDictionary dict("user-record-warning-deadline-passed");
        if(user->display_name() != "") {
            dict.ShowSection("USER_HAS_NAME");
            dict.SetValue("USERNAME", Email::htmlspecialchars(user->display_name()));
        } else {
            dict.ShowSection("NO_USER_NAME");
        }
        dict.SetValue("SITE_NAME", std::string(settings.get("site.name").toLatin1().constData(), settings.get("site.name").toLatin1().length()));

        QString deadline = QDateTime::fromString(QString::fromStdString(task->deadline()), "yyyy-MM-ddTHH:mm:ss").toString("d MMMM yyyy - hh:mm");
        dict.SetValue("DEADLINE_TIME", deadline.toStdString());

        bool footer_enabled=(QString::compare("y", settings.get("email-footer.enabled")) == 0);
        if (footer_enabled) {
            QString donate_link = settings.get("email-footer.donate_link");
            ctemplate::TemplateDictionary* footer_dict = dict.AddIncludeDictionary("FOOTER");
            QString footer_location = QString(TEMPLATE_DIRECTORY) + "emails/footer.tpl";
            footer_dict -> SetValue("DONATE_LINK",donate_link.toStdString());
            footer_dict -> SetFilename(footer_location.toStdString());
        }

        std::string email_body;
        QString template_location;
        template_location = QString(TEMPLATE_DIRECTORY) + "emails/user-record-warning-deadline-passed.tpl";
        ctemplate::ExpandTemplate(template_location.toStdString(), ctemplate::DO_NOT_STRIP, &dict, &email_body);

        email->setSender(settings.get("site.system_email_address"));;
        email->addRecipient(QString::fromStdString(user->email()));
        email->setSubject(settings.get("site.name") + ": Task Overdue");
        email->setBody(QString::fromUtf8(email_body.c_str()));
    } else {
        email = this->generateErrorEmail(error);
    }

    if (sendMessage) this->emailQueue->insert(email, currentMessage);
}
