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

        std::string email_body;
        QString template_location;
        template_location = QString(TEMPLATE_DIRECTORY) + "emails/user-record-warning-deadline-passed.tpl";
        ctemplate::ExpandTemplate(template_location.toStdString(), ctemplate::DO_NOT_STRIP, &dict, &email_body);

        email->setSender(settings.get("site.system_email_address"));;
        email->addRecipient(QString::fromStdString(user->email()));
        email->setSubject(settings.get("site.name") + ": Please Complete Your Profile");
        email->setBody(QString::fromUtf8(email_body.c_str()));

        UserDao::insertWillBeDeletedUser(db, email_message.user_id());
    } else {
        email = this->generateErrorEmail(error);
    }

    if (sendMessage) this->emailQueue->insert(email, currentMessage);
}
