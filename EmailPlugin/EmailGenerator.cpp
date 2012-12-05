#include "EmailGenerator.h"

#include <QDebug>
#include <QUuid>
#include <ctemplate/template.h>

#include "Common/MySQLHandler.h"
#include "Common/ConfigParser.h"

#include "Common/DataAccessObjects/UserDao.h"
#include "Common/DataAccessObjects/OrganisationDao.h"

#include "Common/protobufs/models/User.pb.h"

#include "Common/Models/Task.h"
#include "Common/Models/ArchivedTask.h"

#define TEMPLATE_DIRECTORY "/etc/SOLAS-Match/templates/"

EmailGenerator::EmailGenerator()
{
    //Empty constructor
}

Email *EmailGenerator::generateEmail(TaskScoreEmail email_message)
{
    qDebug() << "EmailGenerator - Generating TaskScoreEmail";
    Email *email = new Email();
    email->setRecipient("spaceindaver0@gmail.com");
    email->setSender("admin@solas.match");
    email->setSubject("User Task Score Results");
    email->setBody(QString::fromStdString(email_message.body()));
    return email;
}

Email *EmailGenerator::generateEmail(OrgMembershipAccepted email_message)
{
    qDebug() << "EmailGenerator - Generating OrgMembershipAccepted";
    Email *email = new Email();
    MySQLHandler *db = new MySQLHandler(QUuid::createUuid().toString());
    if(db->init()) {
        User *user = UserDao::getUser(db, email_message.user_id());
        Organisation *org = OrganisationDao::getOrg(db, email_message.org_id());

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

        email->setSender("admin@solas.match");
        email->setRecipient(QString::fromStdString(user->email()));
        email->setSubject("SOLAS Match: Organisation Membership Update");
        email->setBody(QString::fromStdString(email_body));
    } else {
        email->setSender("error@solas.match");
        email->setRecipient("spaceindaver0@gmail.com");
        email->setSubject("Org Membership Accepted Error");
        email->setBody("Unable to Connect to SQL Server.");
        qDebug() << "Unable to Connect to SQL Server. Check conf.ini and try again.";
    }

    qDebug() << "Deleting db";
    delete db;

    return email;
}

Email *EmailGenerator::generateEmail(OrgMembershipRefused email_message)
{
    qDebug() << "EmailGenerator - Generating OrgMembershipRefused";
    Email * email = new Email();
    MySQLHandler *db = new MySQLHandler(QUuid::createUuid().toString());
    if(db->init()) {
        User *user = UserDao::getUser(db, email_message.user_id());
        Organisation *org = OrganisationDao::getOrg(db, email_message.org_id());

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

        email->setSender("admin@solas.match");
        email->setRecipient(QString::fromStdString(user->email()));
        email->setSubject("SOLAS Match: Organisation Membership Update");
        email->setBody(QString::fromStdString(email_body));
    } else {
        email->setSender("error@solas.match");
        email->setRecipient("spaceindaver0@gmail.com");
        email->setSubject("Org Membership Accepted Error");
        email->setBody("Unable to Connect to SQL Server.");
        qDebug() << "Unable to Connect to SQL Server. Check conf.ini and try again.";
    }

    qDebug() << "Deleting db";
    delete db;

    return email;
}

Email *EmailGenerator::generateEmail(PasswordResetEmail email_message)
{
    qDebug() << "EmailGenerator - Generating PasswordResetEmail";
    Email *email = new Email();
    MySQLHandler *db = new MySQLHandler(QUuid::createUuid().toString());
    if(db->init()) {
        User *user = UserDao::getUser(db, email_message.user_id());
        QString uuid = UserDao::getPasswordResetUuid(db, email_message.user_id());

        ConfigParser settings;
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

        email->setSender("admin@solas.match");
        email->setRecipient(QString::fromStdString(user->email()));
        email->setSubject("SOLAS Match: Organisation Membership Update");
        email->setBody(QString::fromStdString(email_body));
    } else {
        email->setSender("error@solas.match");
        email->setRecipient("spaceindaver0@gmail.com");
        email->setSubject("Password Reset Error");
        email->setBody("Unable to Connect to SQL Server.");
        qDebug() << "Unable to Connect to SQL Server. Check conf.ini and try again.";
    }

    qDebug() << "Deleting db";
    delete db;

    return email;
}

Email *EmailGenerator::generateEmail(TaskArchived email_message)
{
    qDebug() << "EmailGenerator - Generating TaskArchived";
    Email *email = new Email();
    MySQLHandler *db = new MySQLHandler(QUuid::createUuid().toString());
    if(db->init()) {
        User *user = UserDao::getUser(db, email_message.user_id());
        ArchivedTask task = ArchivedTask::getArchivedTask(db, -1, email_message.task_id());
        Organisation *org = OrganisationDao::getOrg(db, task.getOrgId());

        ctemplate::TemplateDictionary dict("task_archived");
        if(user->display_name() != "") {
            dict.ShowSection("USER_HAS_NAME");
            dict["USERNAME"] = user->display_name();
        } else {
            dict.ShowSection("NO_USER_NAME");
        }
        dict["TASK_TITLE"] = task.getTitle().toStdString();
        dict["ORG_NAME"] = org->name();

        std::string email_body;
        QString template_location = QString(TEMPLATE_DIRECTORY) + "emails/task-archived.tpl";
        ctemplate::ExpandTemplate(template_location.toStdString(), ctemplate::DO_NOT_STRIP, &dict, &email_body);

        email->setSender("admin@solas.match");
        email->setRecipient(QString::fromStdString(user->display_name()));
        email->setSubject("SOLAS Match: Task Updated");
        email->setBody(QString::fromStdString(email_body));
    } else {
        email->setSender("error@solas.match");
        email->setRecipient("spaceindaver0@gmail.com");
        email->setSubject("Password Reset Error");
        email->setBody("Unable to Connect to SQL Server.");
        qDebug() << "Unable to Connect to SQL Server. Check conf.ini and try again.";
    }

    qDebug() << "Deleting db";
    delete db;

    return email;
}

Email *EmailGenerator::generateEmail(TaskClaimed email_message)
{
    qDebug() << "EmailGenerator - Generating TaskClaimed";
    Email *email = new Email();
    MySQLHandler *db = new MySQLHandler(QUuid::createUuid().toString());
    if(db->init()) {
        qDebug() << "Getting user";
        User *user = UserDao::getUser(db, email_message.user_id());
        qDebug() << "Getting translator";
        User *translator = UserDao::getUser(db, email_message.translator_id());
        qDebug() << "Getting Task";
        Task task = Task::getTask(db, email_message.task_id());

        ctemplate::TemplateDictionary dict("task_claimed");
        if(user->display_name() != "") {
            dict.ShowSection("USER_HAS_NAME");
            dict["USERNAME"] = user->display_name();
        } else {
            dict.ShowSection("NO_USER_NAME");
        }
        dict["TASK_TITLE"] = task.getTitle().toStdString();
        dict["TRANSLATOR_NAME"] = translator->display_name();

        ConfigParser settings;
        QString user_profile_url = settings.get("site.url");
        user_profile_url += "profile/" + QString::number(translator->user_id());
        dict["USER_PROFILE_URL"] = user_profile_url.toStdString();

        std::string email_body;
        QString template_location = QString(TEMPLATE_DIRECTORY) + "emails/task-claimed.tpl";
        ctemplate::ExpandTemplate(template_location.toStdString(), ctemplate::DO_NOT_STRIP, &dict, &email_body);

        email->setSender("admin@solas.match");;
        email->setRecipient(QString::fromStdString(user->email()));
        email->setSubject("Task Claim Notification");
        email->setBody(QString::fromStdString(email_body));
    } else {
        email->setSender("error@solas.match");
        email->setRecipient("spaceindaver0@gmail.com");
        email->setSubject("Password Reset Error");
        email->setBody("Unable to Connect to SQL Server.");
        qDebug() << "Unable to Connect to SQL Server. Check conf.ini and try again.";
    }

    qDebug() << "Deleting db";
    delete db;

    return email;
}

Email *EmailGenerator::generateEmail(TaskTranslationUploaded email_message)
{
    qDebug() << "EmailGenerator - Generating TaskTranslationUploaded";
    Email *email = new Email();
    MySQLHandler *db = new MySQLHandler(QUuid::createUuid().toString());
    if(db->init()) {
        User *user = UserDao::getUser(db, email_message.user_id());
        User *translator = UserDao::getUser(db, email_message.translator_id());
        Task task = Task::getTask(db, email_message.task_id());
        Organisation *org = OrganisationDao::getOrg(db, task.getOrganisationId());

        ctemplate::TemplateDictionary dict("task_translation_uploaded");
        if(user->display_name() != "") {
            dict.ShowSection("USER_HAS_NAME");
            dict["USERNAME"] = user->display_name();
        } else {
            dict.ShowSection("NO_USER_NAME");
        }
        dict["TRANSLATOR_NAME"] = translator->display_name();
        dict["TASK_TITLE"] = task.getTitle().toStdString();
        dict["ORG_NAME"] = org->name();

        ConfigParser settings;
        QString dash_url = settings.get("site.url");
        dash_url += "client/dashboard";
        dict["DASHBOARD_URL"] = dash_url.toStdString();

        std::string email_body;
        QString template_location = QString(TEMPLATE_DIRECTORY) + "emails/task-translation-uploaded.tpl";
        ctemplate::ExpandTemplate(template_location.toStdString(), ctemplate::DO_NOT_STRIP, &dict, &email_body);

        email->setSender("admin@solas.match");;
        email->setRecipient(QString::fromStdString(user->email()));
        email->setSubject("Task Translation Uploaded Notification");
        email->setBody(QString::fromStdString(email_body));
    } else {
        email->setSender("error@solas.match");
        email->setRecipient("spaceindaver0@gmail.com");
        email->setSubject("Task Translation Uploaded Email Error");
        email->setBody("Unable to Connect to SQL Server.");
        qDebug() << "Unable to Connect to SQL Server. Check conf.ini and try again.";
    }

    return email;
}

Email *EmailGenerator::generateEmail(UserTaskClaim email_message)
{
    qDebug() << "EmailGenerator - Generating UserTaskClaim";
    Email *email = new Email();
    MySQLHandler *db = new MySQLHandler(QUuid::createUuid().toString());
    if(db->init()) {
        User *user = UserDao::getUser(db, email_message.user_id());
        Task task = Task::getTask(db, email_message.task_id());

        ctemplate::TemplateDictionary dict("user_task_claim");
        if(user->display_name() != "") {
            dict.ShowSection("USER_HAS_NAME");
            dict["USERNAME"] = user->display_name();
        } else {
            dict.ShowSection("NO_USER_NAME");
        }

        ConfigParser settings;
        QString task_url = settings.get("site.url");
        task_url += "task/id/" + QString::number(task.getTaskId());
        dict["TASK_PAGE"] = task_url.toStdString();

        std::string email_body;
        QString template_location = QString(TEMPLATE_DIRECTORY) + "emails/user-task-claim.tpl";
        ctemplate::ExpandTemplate(template_location.toStdString(), ctemplate::DO_NOT_STRIP, &dict, &email_body);

        email->setSender("admin@solas.match");;
        email->setRecipient(QString::fromStdString(user->email()));
        email->setSubject("Task Claim Notification");
        email->setBody(QString::fromStdString(email_body));
    } else {
        email->setSender("error@solas.match");
        email->setRecipient("spaceindaver0@gmail.com");
        email->setSubject("User Task Claim Email Error");
        email->setBody("Unable to Connect to SQL Server.");
        qDebug() << "Unable to Connect to SQL Server. Check conf.ini and try again.";
    }

    return email;
}
