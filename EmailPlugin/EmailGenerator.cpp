#include "EmailGenerator.h"

#include <QDebug>
#include <QUuid>
#include <QCTemplate.h>

#include "Common/MySQLHandler.h"
#include "Common/ConfigParser.h"
#include "Common/Models/User.h"
#include "Common/Models/Task.h"
#include "Common/Models/ArchivedTask.h"
#include "Common/Models/Org.h"

#define TEMPLATE_DIRECTORY "/etc/SOLAS-Match/templates/"

EmailGenerator::EmailGenerator()
{
    //Empty constructor
}

Email *EmailGenerator::generateEmail(TaskScoreEmail email_message)
{
    Email *email = new Email();
    email->setRecipient("spaceindaver0@gmail.com");
    email->setSender("admin@solas.match");
    email->setSubject("User Task Score Results");
    email->setBody(QString::fromStdString(email_message.body()));
    return email;
}

Email *EmailGenerator::generateEmail(OrgMembershipAccepted email_message)
{
    Email *email = new Email();
    MySQLHandler *db = new MySQLHandler(QUuid::createUuid().toString());
    if(db->init()) {
        User user = User::getUser(db, email_message.user_id());
        Org org = Org::getOrg(db, email_message.org_id());

        QCTemplate mTemplate;
        if(user.getDisplayName() != "") {
            mTemplate.enterSection("USER_HAS_NAME");
            mTemplate["USERNAME"] = user.getDisplayName();
            mTemplate.exitSection();
        } else {
            mTemplate.enterSection("NO_USER_NAME");
            mTemplate.exitSection();
        }
        mTemplate["ORG_NAME"] = org.getName();
        QString email_body = mTemplate.expandFile(
                    QString(TEMPLATE_DIRECTORY) + "emails/org-membership-accepted.tpl");
        email->setSender("admin@solas.match");
        email->setRecipient(user.getEmail());
        email->setSubject("SOLAS Match: Organisation Membership Update");
        email->setBody(email_body);
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
    Email * email = new Email();
    MySQLHandler *db = new MySQLHandler(QUuid::createUuid().toString());
    if(db->init()) {
        User user = User::getUser(db, email_message.user_id());
        Org org = Org::getOrg(db, email_message.org_id());

        QCTemplate mTemplate;
        if(user.getDisplayName() != "") {
            mTemplate.enterSection("USER_HAS_NAME");
            mTemplate["USERNAME"] = user.getDisplayName();
            mTemplate.exitSection();
        } else {
            mTemplate.enterSection("NO_USER_NAME");
            mTemplate.exitSection();
        }
        mTemplate["ORG_NAME"] = org.getName();
        QString email_body = mTemplate.expandFile(
                    QString(TEMPLATE_DIRECTORY) + "emails/org-membership-refused.tpl");
        email->setSender("admin@solas.match");
        email->setRecipient(user.getEmail());
        email->setSubject("SOLAS Match: Organisation Membership Update");
        email->setBody(email_body);
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

Email *EmailGenerator::generateEmail(PasswordReset email_message)
{
    Email *email = new Email();
    MySQLHandler *db = new MySQLHandler(QUuid::createUuid().toString());
    if(db->init()) {
        User user = User::getUser(db, email_message.user_id());
        QString uuid = User::getPasswordResetUuid(db, email_message.user_id());

        ConfigParser settings;
        QString page_url = settings.get("site.url");
        page_url += uuid;
        page_url += "/password/reset";

        QCTemplate mTemplate;
        if(user.getDisplayName() != "") {
            mTemplate.enterSection("USER_HAS_NAME");
            mTemplate["USERNAME"] = user.getDisplayName();
            mTemplate.exitSection();
        } else {
            mTemplate.enterSection("NO_USER_NAME");
            mTemplate.exitSection();
        }
        mTemplate["URL"] = page_url;
        QString email_body = mTemplate.expandFile(
                    QString(TEMPLATE_DIRECTORY) + "emails/password-reset.tpl");
        email->setSender("admin@solas.match");
        email->setRecipient(user.getEmail());
        email->setSubject("SOLAS Match: Organisation Membership Update");
        email->setBody(email_body);
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
    Email *email = new Email();
    MySQLHandler *db = new MySQLHandler(QUuid::createUuid().toString());
    if(db->init()) {
        User user = User::getUser(db, email_message.user_id());
        ArchivedTask task = ArchivedTask::getArchivedTask(db, -1, email_message.task_id());
        Org org = Org::getOrg(db, task.getOrgId());

        QCTemplate mTemplate;
        if(user.getDisplayName() != "") {
            mTemplate.enterSection("USER_HAS_NAME");
            mTemplate["USERNAME"] = user.getDisplayName();
            mTemplate.exitSection();
        } else {
            mTemplate.enterSection("NO_USER_NAME");
            mTemplate.exitSection();
        }
        mTemplate["TASK_TITLE"] = task.getTitle();
        mTemplate["ORG_NAME"] = org.getName();

        QString email_body = mTemplate.expandFile(
                    QString(TEMPLATE_DIRECTORY) + "emails/task-archived.tpl");

        email->setSender("admin@solas.match");
        email->setRecipient(user.getEmail());
        email->setSubject("SOLAS Match: Task Updated");
        email->setBody(email_body);
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
    Email *email = new Email();
    MySQLHandler *db = new MySQLHandler(QUuid::createUuid().toString());
    if(db->init()) {
        qDebug() << "Getting user";
        User user = User::getUser(db, email_message.user_id());
        qDebug() << "Getting translator";
        User translator = User::getUser(db, email_message.translator_id());
        qDebug() << "Getting Task";
        Task task = Task::getTask(db, email_message.task_id());

        QCTemplate mTemplate;
        if(user.getDisplayName() != "") {
            mTemplate.enterSection("USER_HAS_NAME");
            mTemplate["USERNAME"] = user.getDisplayName();
            mTemplate.exitSection();
        } else {
            mTemplate.enterSection("NO_USER_NAME");
            mTemplate.exitSection();
        }
        mTemplate["TASK_TITLE"] = task.getTitle();
        mTemplate["TRANSLATOR_NAME"] = translator.getDisplayName();

        ConfigParser settings;
        QString user_profile_url = settings.get("site.url");
        user_profile_url += "profile/" + QString::number(translator.getUserId());
        mTemplate["USER_PROFILE_URL"] = user_profile_url;

        QString email_body = mTemplate.expandFile(QString(TEMPLATE_DIRECTORY) + "emails/task-claimed.tpl");

        email->setSender("admin@solas.match");;
        email->setRecipient(user.getEmail());
        email->setSubject("Task Claim Notification");
        email->setBody(email_body);
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
    Email *email = new Email();
    MySQLHandler *db = new MySQLHandler(QUuid::createUuid().toString());
    if(db->init()) {
        User user = User::getUser(db, email_message.user_id());
        User translator = User::getUser(db, email_message.translatior_id());
        Task task = Task::getTask(db, email_message.task_id());
        Org org = Org::getOrg(db, task.getOrganisationId());

        QCTemplate mTemplate;
        if(user.getDisplayName() != "") {
            mTemplate.enterSection("USER_HAS_NAME");
            mTemplate["USERNAME"] = user.getDisplayName();
            mTemplate.exitSection();
        } else {
            mTemplate.enterSection("NO_USER_NAME");
            mTemplate.exitSection();
        }
        mTemplate["TRANSLATOR_NAME"] = translator.getDisplayName();
        mTemplate["TASK_TITLE"] = task.getTitle();
        mTemplate["ORG_NAME"] = org.getName();

        ConfigParser settings;
        QString dash_url = settings.get("site.url");
        dash_url += "client/dashboard";
        mTemplate["DASHBOARD_URL"] = dash_url;

        QString message_body = mTemplate.expandFile(QString(TEMPLATE_DIRECTORY) + "emails/task-translation-uploaded.tpl");

        email->setSender("admin@solas.match");;
        email->setRecipient(user.getEmail());
        email->setSubject("Task Translation Uploaded Notification");
        email->setBody(message_body);
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
    Email *email = new Email();
    MySQLHandler *db = new MySQLHandler(QUuid::createUuid().toString());
    if(db->init()) {
        User user = User::getUser(db, email_message.user_id());
        Task task = Task::getTask(db, email_message.task_id());

        QCTemplate mTemplate;
        if(user.getDisplayName() != "") {
            mTemplate.enterSection("USER_HAS_NAME");
            mTemplate["USERNAME"] = user.getDisplayName();
            mTemplate.exitSection();
        } else {
            mTemplate.enterSection("NO_USER_NAME");
            mTemplate.exitSection();
        }

        ConfigParser settings;
        QString task_url = settings.get("site.url");
        task_url += "task/id/" + QString::number(task.getTaskId());
        mTemplate["TASK_PAGE"] = task_url;

        QString email_body = mTemplate.expandFile(QString(TEMPLATE_DIRECTORY) + "emails/user-task-claim.tpl");

        email->setSender("admin@solas.match");;
        email->setRecipient(user.getEmail());
        email->setSubject("Task Claim Notification");
        email->setBody(email_body);
    } else {
        email->setSender("error@solas.match");
        email->setRecipient("spaceindaver0@gmail.com");
        email->setSubject("User Task Claim Email Error");
        email->setBody("Unable to Connect to SQL Server.");
        qDebug() << "Unable to Connect to SQL Server. Check conf.ini and try again.";
    }

    return email;
}
