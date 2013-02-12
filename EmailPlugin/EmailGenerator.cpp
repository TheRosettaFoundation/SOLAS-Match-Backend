#include "EmailGenerator.h"

#include <QDebug>
#include <QStringList>
#include <QUuid>
#include <ctemplate/template.h>

#include "Common/MySQLHandler.h"
#include "Common/ConfigParser.h"

#include "Common/DataAccessObjects/UserDao.h"
#include "Common/DataAccessObjects/OrganisationDao.h"
#include "Common/DataAccessObjects/TaskDao.h"
#include "Common/DataAccessObjects/ProjectDao.h"

#include "Common/protobufs/models/User.pb.h"
#include "Common/protobufs/models/Task.pb.h"
#include "Common/protobufs/models/Project.pb.h"
#include "Common/protobufs/models/ArchivedTask.pb.h"
#include "Common/protobufs/models/Organisation.pb.h"

#define TEMPLATE_DIRECTORY "/etc/SOLAS-Match/templates/"

EmailGenerator::EmailGenerator()
{
    //Empty constructor
}

QSharedPointer<Email> EmailGenerator::generateEmail(TaskScoreEmail email_message)
{
    qDebug() << "EmailGenerator - Generating TaskScoreEmail";

    QSharedPointer<Email> email = QSharedPointer<Email>(new Email());
    ConfigParser settings;

    QStringList admins = settings.get("mail.admin_emails").split(",");
    foreach(QString admin, admins) {
        email->addRecipient(admin.trimmed());
    }

    email->setSender(settings.get("site.system_email_address"));
    email->setSubject("User Task Score Results");
    email->setBody(QString::fromStdString(email_message.body()));
    return email;
}

QSharedPointer<Email> EmailGenerator::generateEmail(OrgMembershipAccepted email_message)
{
    qDebug() << "EmailGenerator - Generating OrgMembershipAccepted";

    ConfigParser settings;
    QSharedPointer<Email> email = QSharedPointer<Email>(new Email());
    MySQLHandler *db = new MySQLHandler(QUuid::createUuid().toString());
    QSharedPointer<Organisation> org = QSharedPointer<Organisation>();
    QSharedPointer<User> user = QSharedPointer<User>();
    QString error = "";

    if(db->init()) {
        user = UserDao::getUser(db, email_message.user_id());
        org = OrganisationDao::getOrg(db, email_message.org_id());
        if(user.isNull() || org.isNull()) {
            error = "Unable to generate OrgMembershipAccepted email. Unable to find objects ";
            error += "in the DB. Searched for user ID " + QString::number(email_message.user_id());
            error += " and org ID " + QString::number(email_message.org_id()) + ".";
        }
    } else {
        error = "Unable to Connect to SQL Server. Check conf.ini for connection settings and make sure ";
        error += "mysqld has been started.";
        qDebug() << "Unable to Connect to SQL Server. Check conf.ini and try again.";
    }

    if(error.compare("") == 0)
    {
        //No error generate the email
        ctemplate::TemplateDictionary dict("org_membership_accepted");
        if(user->display_name() != "") {
            dict.ShowSection("USER_HAS_NAME");
            dict["USERNAME"] = user->display_name();
        } else {
            dict.ShowSection("NO_USER_NAME");
        }
        dict["ORG_NAME"] = org->name();
        std::string email_body;
        QString template_location = QString(TEMPLATE_DIRECTORY) + "emails/org-membership-accepted.tpl";
        ctemplate::ExpandTemplate(template_location.toStdString(), ctemplate::DO_NOT_STRIP, &dict, &email_body);

        email->setSender(settings.get("site.system_email_address"));
        email->addRecipient(QString::fromStdString(user->email()));
        email->setSubject("SOLAS Match: Organisation Membership Update");
        email->setBody(QString::fromStdString(email_body));
    } else {
        email = this->generateErrorEmail(error);
    }

    delete db;

    return email;
}

QSharedPointer<Email> EmailGenerator::generateEmail(OrgMembershipRefused email_message)
{
    qDebug() << "EmailGenerator - Generating OrgMembershipRefused";

    ConfigParser settings;
    QSharedPointer<Email> email = QSharedPointer<Email>(new Email());
    QSharedPointer<User> user = QSharedPointer<User>();
    QSharedPointer<Organisation> org = QSharedPointer<Organisation>();
    MySQLHandler *db = new MySQLHandler(QUuid::createUuid().toString());
    QString error = "";

    if(db->init()) {
        user = UserDao::getUser(db, email_message.user_id());
        org = OrganisationDao::getOrg(db, email_message.org_id());

        if(user.isNull() || org.isNull())
        {
            error = "Unable to generate OrgMembershipRefused email. Unable to find objects ";
            error += "in the DB. Searched for user ID " + QString::number(email_message.user_id());
            error += " and org ID " + QString::number(email_message.org_id()) + ".";
        }
    } else {
        error = "Unable to Connect to SQL Server. Check conf.ini for connection settings and make sure ";
        error += "mysqld has been started.";
        qDebug() << "Unable to Connect to SQL Server. Check conf.ini and try again.";
    }

    if(error.compare("") == 0)
    {
        ctemplate::TemplateDictionary dict("org_membershipt_refused");
        if(user->display_name() != "") {
            dict.ShowSection("USER_HAS_NAME");
            dict["USERNAME"] = user->display_name();
        } else {
            dict.ShowSection("NO_USER_NAME");
        }
        dict["ORG_NAME"] = org->name();
        std::string email_body;
        QString template_location = QString(TEMPLATE_DIRECTORY) + "emails/org-membership-refused.tpl";
        ctemplate::ExpandTemplate(template_location.toStdString(), ctemplate::DO_NOT_STRIP, &dict, &email_body);

        email->setSender(settings.get("site.system_email_address"));
        email->addRecipient(QString::fromStdString(user->email()));
        email->setSubject("SOLAS Match: Organisation Membership Update");
        email->setBody(QString::fromStdString(email_body));
    } else {
        email = this->generateErrorEmail(error);
    }

    delete db;

    return email;
}

QSharedPointer<Email> EmailGenerator::generateEmail(OrgTaskDeadlinePassed email_message)
{
    qDebug() << "EmailGenerator - Generating OrgTaskDeadlinePassed";

    ConfigParser settings;
    QString error = "";
    QSharedPointer<Email> email = QSharedPointer<Email>(new Email());
    QSharedPointer<User> user = QSharedPointer<User>();
    QSharedPointer<User> translator = QSharedPointer<User>();
    QSharedPointer<Task> task = QSharedPointer<Task>();
    MySQLHandler *db = new MySQLHandler(QUuid::createUuid().toString());

    if(db->init()) {
        translator = UserDao::getUser(db, email_message.translator_id());
        task = TaskDao::getTask(db, email_message.task_id());
        user = UserDao::getUser(db, email_message.user_id());

        if(user.isNull() || task.isNull() || translator.isNull()) {
            error = "OrgTaskDeadlinePassed generation failed. Data missing from the DB.";
            error += "Searched for user ID " + QString::number(email_message.translator_id());
            error += " and " + QString::number(email_message.user_id());
            error += " and task ID " + QString::number(email_message.task_id());
        }
    } else {
        error = "Unable to Connect to SQL Server. Check conf.ini for connection settings and make sure ";
        error += "mysqld has been started.";
        qDebug() << "Unable to Connect to SQL Server. Check conf.ini and try again.";
    }

    if(error.compare("") == 0) {
        ctemplate::TemplateDictionary dict("OrgTaskDeadlinePassed");
        if(user->display_name() != "") {
            dict.ShowSection("USER_HAS_NAME");
            dict["USERNAME"] = user->display_name();
        } else {
            dict.ShowSection("NO_USER_NAME");
        }
        dict["TASK_TITLE"] = task->title();

        std::string email_body;
        QString template_location = QString(TEMPLATE_DIRECTORY) + "emails/org-task-deadline-passed.tpl";
        ctemplate::ExpandTemplate(template_location.toStdString(), ctemplate::DO_NOT_STRIP, &dict, &email_body);

        email->setSender(settings.get("site.system_email_address"));
        email->addRecipient(QString::fromStdString(user->email()));
        email->setSubject("SOLAS Match: Organisation Membership Update");
        email->setBody(QString::fromStdString(email_body));
    } else {
        email = this->generateErrorEmail(error);
    }

    delete db;

    return email;
}

QSharedPointer<Email> EmailGenerator::generateEmail(PasswordResetEmail email_message)
{
    qDebug() << "EmailGenerator - Generating PasswordResetEmail";

    ConfigParser settings;
    QSharedPointer<Email> email = QSharedPointer<Email>(new Email());
    QString uuid = "";
    QString error = "";
    QSharedPointer<User> user = QSharedPointer<User>();
    MySQLHandler *db = new MySQLHandler(QUuid::createUuid().toString());

    if(db->init()) {
        user = UserDao::getUser(db, email_message.user_id());
        uuid = UserDao::getPasswordResetUuid(db, email_message.user_id());

        if(user.isNull() || uuid.compare("") == 0) {
            error = "Password Reset email generation failed. Unable to find ";
            error += "data in the DB. Looking for user id " + email_message.user_id();
        }
    } else {
        error = "Unable to Connect to SQL Server. Check conf.ini for connection settings and make sure ";
        error += "mysqld has been started.";
        qDebug() << "Unable to Connect to SQL Server. Check conf.ini and try again.";
    }

    if(error.compare("") == 0) {
        QString page_url = settings.get("site.url");
        page_url += uuid;
        page_url += "/password/reset";

        ctemplate::TemplateDictionary dict("password_reset");
        if(user->display_name() != "") {
            dict.ShowSection("USER_HAS_NAME");
            dict["USERNAME"] = user->display_name();
        } else {
            dict.ShowSection("NO_USER_NAME");
        }
        dict["URL"] = page_url.toStdString();
        std::string email_body;
        QString template_location = QString(TEMPLATE_DIRECTORY) + "emails/password-reset.tpl";
        ctemplate::ExpandTemplate(template_location.toStdString(), ctemplate::DO_NOT_STRIP, &dict, &email_body);

        email->setSender(settings.get("site.system_email_address"));
        email->addRecipient(QString::fromStdString(user->email()));
        email->setSubject("SOLAS Match: Organisation Membership Update");
        email->setBody(QString::fromStdString(email_body));
    } else {
        email = this->generateErrorEmail(error);
    }

    delete db;

    return email;
}

QSharedPointer<Email> EmailGenerator::generateEmail(TaskArchived email_message)
{
    qDebug() << "EmailGenerator - Generating TaskArchived";

    ConfigParser settings;
    QString error = "";
    QSharedPointer<Email> email = QSharedPointer<Email>(new Email());
    QSharedPointer<User> user = QSharedPointer<User>();
    QSharedPointer<Organisation> org = QSharedPointer<Organisation>();
    QSharedPointer<ArchivedTask> task = QSharedPointer<ArchivedTask>();
    QSharedPointer<Project> project = QSharedPointer<Project>();
    MySQLHandler *db = new MySQLHandler(QUuid::createUuid().toString());

    if(db->init()) {
        user = UserDao::getUser(db, email_message.user_id());
        task = TaskDao::getArchivedTask(db, -1, email_message.task_id());

        if(!user.isNull() && !task.isNull()) {
            project = ProjectDao::getProject(db, task->projectid());
            org = OrganisationDao::getOrg(db, project->organisationid());
            if(org.isNull()) {
                error = "Failed to Generate task archived email. Unable to find relevent information ";
                error += "in the Database. Unable to locate org with id " + QString::number(org->id());
                error += ".";
            }
        } else {
            error = "Failed to Generate task archived email. Unable to find relevent information ";
            error += "in the Database. Searched for user ID " + QString::number(email_message.user_id());
            error += ", task ID " + QString::number(email_message.task_id()) + ".";
        }
    } else {
        error = "Failed to generate task archived email: Unable to Connect to SQL Server. ";
        error += "Check conf.ini for connection settings and make sure mysqld has been started.";
        qDebug() << "Unable to Connect to SQL Server. Check conf.ini and try again.";
    }

    if(error.compare("") == 0) {
        ctemplate::TemplateDictionary dict("task_archived");
        if(user->display_name() != "") {
            dict.ShowSection("USER_HAS_NAME");
            dict["USERNAME"] = user->display_name();
        } else {
            dict.ShowSection("NO_USER_NAME");
        }
        dict["TASK_TITLE"] = task->title();
        dict["ORG_NAME"] = org->name();

        std::string email_body;
        QString template_location = QString(TEMPLATE_DIRECTORY) + "emails/task-archived.tpl";
        ctemplate::ExpandTemplate(template_location.toStdString(), ctemplate::DO_NOT_STRIP, &dict, &email_body);

        email->setSender(settings.get("site.system_email_address"));
        email->addRecipient(QString::fromStdString(user->display_name()));
        email->setSubject("SOLAS Match: Task Updated");
        email->setBody(QString::fromStdString(email_body));
    } else {
        email = this->generateErrorEmail(error);
    }

    delete db;

    return email;
}

QSharedPointer<Email> EmailGenerator::generateEmail(TaskClaimed email_message)
{
    qDebug() << "EmailGenerator - Generating TaskClaimed";

    ConfigParser settings;
    QString error = "";
    QSharedPointer<Email> email = QSharedPointer<Email>(new Email());
    QSharedPointer<User> user = QSharedPointer<User>();
    QSharedPointer<User> translator = QSharedPointer<User>();
    QSharedPointer<Task> task = QSharedPointer<Task>();
    MySQLHandler *db = new MySQLHandler(QUuid::createUuid().toString());

    if(db->init()) {
        user = UserDao::getUser(db, email_message.user_id());
        translator = UserDao::getUser(db, email_message.translator_id());
        task = TaskDao::getTask(db, email_message.task_id());

        if(user.isNull() || translator.isNull() || task.isNull()) {
            error = "Failed to generate task claimed email: Unable to find relevant ";
            error += "information in the database. Searched for user ID ";
            error += QString::number(email_message.user_id()) + ", translator ID ";
            error += QString::number(email_message.translator_id()) + " and task ID ";
            error += QString::number(email_message.task_id()) + ".";
        }

    } else {
        error = "Failed to generate task claimed email: Unable to Connect to SQL Server. ";
        error += "Check conf.ini for connection settings and make sure mysqld has been started.";
        qDebug() << "Unable to Connect to SQL Server. Check conf.ini and try again.";
    }

    if(error.compare("") == 0) {
        ctemplate::TemplateDictionary dict("task_claimed");
        if(user->display_name() != "") {
            dict.ShowSection("USER_HAS_NAME");
            dict["USERNAME"] = user->display_name();
        } else {
            dict.ShowSection("NO_USER_NAME");
        }
        dict["TASK_TITLE"] = task->title();
        dict["TRANSLATOR_NAME"] = translator->display_name();

        QString user_profile_url = settings.get("site.url");
        user_profile_url += "profile/" + QString::number(translator->user_id());
        dict["USER_PROFILE_URL"] = user_profile_url.toStdString();

        std::string email_body;
        QString template_location = QString(TEMPLATE_DIRECTORY) + "emails/task-claimed.tpl";
        ctemplate::ExpandTemplate(template_location.toStdString(), ctemplate::DO_NOT_STRIP, &dict, &email_body);

        email->setSender(settings.get("site.system_email_address"));;
        email->addRecipient(QString::fromStdString(user->email()));
        email->setSubject("Task Claim Notification");
        email->setBody(QString::fromStdString(email_body));
    } else {
        email = this->generateErrorEmail(error);
    }

    delete db;

    return email;
}

QSharedPointer<Email> EmailGenerator::generateEmail(TaskTranslationUploaded email_message)
{
    qDebug() << "EmailGenerator - Generating TaskTranslationUploaded";

    ConfigParser settings;
    QString error = "";
    QSharedPointer<Email> email = QSharedPointer<Email>(new Email());
    QSharedPointer<User> user = QSharedPointer<User>();
    QSharedPointer<User> translator = QSharedPointer<User>();
    QSharedPointer<Task> task = QSharedPointer<Task>();
    QSharedPointer<Project> project = QSharedPointer<Project>();
    QSharedPointer<Organisation> org = QSharedPointer<Organisation>();
    MySQLHandler *db = new MySQLHandler(QUuid::createUuid().toString());

    if(db->init()) {
        user = UserDao::getUser(db, email_message.user_id());
        translator = UserDao::getUser(db, email_message.translator_id());
        task = TaskDao::getTask(db, email_message.task_id());

        if(user.isNull() || translator.isNull() || task.isNull()) {
            error = "Failed to generate task translation uploaded email. Unable ";
            error += "to find relevant inforamtion in the Database. Searched for ";
            error += "User ID " + QString::number(email_message.user_id()) + ", ";
            error += "Translator ID " + QString::number(email_message.translator_id());
            error += " and Task ID " + QString::number(email_message.task_id()) + ".";
        } else {
            project = ProjectDao::getProject(db, email_message.task_id());
            org = OrganisationDao::getOrg(db, project->organisationid());

            if(org.isNull()) {
                error = "Failed to generate task translation uploaded email. Unable ";
                error += "to find relevant inforamtion in the Database. Could not find ";
                error += "Organisation with ID " + QString::number(project->organisationid()) + ".";
            }
        }

    } else {
        error = "Failed to generate task translation uploaded email: Unable to Connect to SQL Server.";
        error += " Check conf.ini for connection settings and make sure mysqld has been started.";
        qDebug() << "Unable to Connect to SQL Server. Check conf.ini and try again.";
    }

    if(error.compare("") == 0) {
        ctemplate::TemplateDictionary dict("task_translation_uploaded");
        if(user->display_name() != "") {
            dict.ShowSection("USER_HAS_NAME");
            dict["USERNAME"] = user->display_name();
        } else {
            dict.ShowSection("NO_USER_NAME");
        }
        dict["TRANSLATOR_NAME"] = translator->display_name();
        dict["TASK_TITLE"] = task->title();
        dict["ORG_NAME"] = org->name();

        QString dash_url = settings.get("site.url");
        dash_url += "client/dashboard";
        dict["DASHBOARD_URL"] = dash_url.toStdString();

        std::string email_body;
        QString template_location = QString(TEMPLATE_DIRECTORY) + "emails/task-translation-uploaded.tpl";
        ctemplate::ExpandTemplate(template_location.toStdString(), ctemplate::DO_NOT_STRIP, &dict, &email_body);

        email->setSender(settings.get("site.system_email_address"));;
        email->addRecipient(QString::fromStdString(user->email()));
        email->setSubject("Task Translation Uploaded Notification");
        email->setBody(QString::fromStdString(email_body));
    } else {
        email = this->generateErrorEmail(error);
    }

    delete db;

    return email;
}

QSharedPointer<Email> EmailGenerator::generateEmail(UserTaskClaim email_message)
{
    qDebug() << "EmailGenerator - Generating UserTaskClaim";

    ConfigParser settings;
    QString error = "";
    QSharedPointer<Email> email = QSharedPointer<Email>(new Email());
    QSharedPointer<User> user = QSharedPointer<User>();
    QSharedPointer<Task> task = QSharedPointer<Task>();
    MySQLHandler *db = new MySQLHandler(QUuid::createUuid().toString());

    if(db->init()) {
        user = UserDao::getUser(db, email_message.user_id());
        task = TaskDao::getTask(db, email_message.task_id());

        if(user.isNull() || task.isNull()) {
            error = "Failed to generate UserTaskClaim email: Unable to find relevant ";
            error += "data in the Database. Searched for User ID ";
            error += QString::number(email_message.user_id()) + " and Task ID ";
            error += QString::number(email_message.task_id()) + ".";
        }
    } else {
        error = "Failed to generate user task claim email: Unable to Connect to SQL Server.";
        error += " Check conf.ini for connection settings and make sure mysqld has been started.";
        qDebug() << "Unable to Connect to SQL Server. Check conf.ini and try again.";
    }

    if(error.compare("") == 0) {
        ctemplate::TemplateDictionary dict("user_task_claim");
        if(user->display_name() != "") {
            dict.ShowSection("USER_HAS_NAME");
            dict["USERNAME"] = user->display_name();
        } else {
            dict.ShowSection("NO_USER_NAME");
        }

        QString task_url = settings.get("site.url");
        task_url += "task/id/" + QString::number(task->id());
        dict["TASK_PAGE"] = task_url.toStdString();

        std::string email_body;
        QString template_location = QString(TEMPLATE_DIRECTORY) + "emails/user-task-claim.tpl";
        ctemplate::ExpandTemplate(template_location.toStdString(), ctemplate::DO_NOT_STRIP, &dict, &email_body);

        email->setSender(settings.get("site.system_email_address"));;
        email->addRecipient(QString::fromStdString(user->email()));
        email->setSubject("Task Claim Notification");
        email->setBody(QString::fromStdString(email_body));
    } else {
        email = this->generateErrorEmail(error);
    }

    delete db;

    return email;
}

QSharedPointer<Email> EmailGenerator::generateEmail(UserClaimedTaskDeadlinePassed email_message)
{
    ConfigParser settings;
    QString error = "";
    QSharedPointer<Email> email = QSharedPointer<Email>(new Email);
    QSharedPointer<User> user = QSharedPointer<User>();
    QSharedPointer<Task> task = QSharedPointer<Task>();
    MySQLHandler* db = new MySQLHandler(QUuid::createUuid().toString());

    if(db->init()) {
        user = UserDao::getUser(db, email_message.translator_id());
        task = TaskDao::getTask(db, email_message.task_id());

        if(!user || !task) {
            error = "Failed to generate UserClaimedTaskDeadlinePassed email: Unable to find relevant ";
            error += "data in the Database. Searched for User ID ";
            error += QString::number(email_message.translator_id()) + " and Task ID ";
            error += QString::number(email_message.task_id()) + ".";
        }
    } else {
        error = "Failed to generate user UserClaimedTaskDeadlinePassed: Unable to Connect to SQL Server.";
        error += " Check conf.ini for connection settings and make sure mysqld has been started.";
        qDebug() << "Unable to Connect to SQL Server. Check conf.ini and try again.";
    }

    if(error.compare("") == 0) {
        ctemplate::TemplateDictionary dict("user_claimed_task_deadline_exceeded");
        if(user->display_name() != "") {
            dict.ShowSection("USER_HAS_NAME");
            dict["USERNAME"] = user->display_name();
        } else {
            dict.ShowSection("NO_USER_NAME");
        }
        dict["TASK_TITLE"] = task->title();

        std::string email_body;
        QString template_location = QString(TEMPLATE_DIRECTORY) + "emails/user-claimed-task-deadline-passed.tpl";
        ctemplate::ExpandTemplate(template_location.toStdString(), ctemplate::DO_NOT_STRIP, &dict, &email_body);

        email->setSender(settings.get("site.system_email_address"));;
        email->addRecipient(QString::fromStdString(user->email()));
        email->setSubject("Task Claim Notification");
        email->setBody(QString::fromStdString(email_body));
    } else {
        email = this->generateErrorEmail(error);
    }

    delete db;

    return email;
}

QSharedPointer<Email> EmailGenerator::generateEmail(FeedbackEmail email_message)
{
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
        feedback = email_message.feedback().c_str();

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

    return email;
}

QSharedPointer<Email> EmailGenerator::generateErrorEmail(QString error_message)
{
    ConfigParser settings;
    QSharedPointer<Email> email = QSharedPointer<Email>(new Email());

    email->setSender(settings.get("site.system_email_address"));
    QStringList admins = settings.get("mail.admin_emails").split(",");
    foreach(QString admin, admins) {
        email->addRecipient(admin.trimmed());
    }
    email->setSubject("An error has occurred");

    QString body = "<p>Hello,</p><p>An error has occurred in the SOLAS-Match worker Daemon. ";
    body += error_message + "</p>";
    email->setBody(body);

    return email;
}
