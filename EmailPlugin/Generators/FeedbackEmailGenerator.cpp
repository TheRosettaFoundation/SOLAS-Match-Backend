#include "FeedbackEmailGenerator.h"

FeedbackEmailGenerator::FeedbackEmailGenerator()
{
    //Default Constructor
}

void FeedbackEmailGenerator::run()
{
    qDebug() << "EmailGenerator: Generating FeedbackEmail";

    FeedbackEmail email_message;
    email_message.ParseFromString(this->protoBody.toStdString());

    ConfigParser settings;
    QString error = "";
    QSharedPointer<Email> email = QSharedPointer<Email>(new Email);
    QSharedPointer<User> user = QSharedPointer<User>();
    QSharedPointer<Task> task = QSharedPointer<Task>();
    QString feedback;
    MySQLHandler* db = new MySQLHandler(QUuid::createUuid().toString());

    if (db->init()) {
        user = UserDao::getUser(db, email_message.userid().Get(0));
        task = TaskDao::getTask(db, email_message.taskid());
        feedback = email_message.feedback().data();

        if (user.isNull() || task.isNull()) {
            error = "Failed to generate UserClaimedTaskDeadlinePassed email: Unable to find relevant ";
            error += "data in the Database. Searched for User ID ";
            error += QString::number(email_message.userid().Get(0)) + " and Task ID ";
            error += QString::number(email_message.taskid()) + ".";
        }
    } else {
        error = "Failed to generate FeedbackEmail: Unable to Connect to SQL Server.";
        error += " Check conf.ini for connection settings and make sure mysqld has been started.";
        qDebug() << "Unable to Connect to SQL Server. Check conf.ini and try again.";
    }

    if(error.compare("") == 0) {
        ctemplate::TemplateDictionary dict("feedbackEmail");
        if(user->display_name() != "") {
            dict.ShowSection("USER_HAS_NAME");
            dict["USERNAME"] = user->display_name();
        } else {
            dict.ShowSection("NO_USER_NAME");
        }
        dict["TASKTITLE"] = task->title();
        dict["FEEDBACK"] = feedback.toStdString();

        std::string email_body;
        QString template_location = QString(TEMPLATE_DIRECTORY) + "emails/feedback.tpl";
        ctemplate::ExpandTemplate(template_location.toStdString(), ctemplate::DO_NOT_STRIP, &dict, &email_body);

        email->setSender(settings.get("site.system_email_address"));;
        email->addRecipient(QString::fromStdString(user->email()));
        email->setSubject("Feedback");
        email->setBody(QString::fromStdString(email_body));
    } else {
        email = this->generateErrorEmail(error);
    }

    delete db;

    this->emailQueue->enqueue(email);
}
