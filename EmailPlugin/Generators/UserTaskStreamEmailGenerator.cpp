#include "UserTaskStreamEmailGenerator.h"

#include <QDateTime>

#include "Common/protobufs/models/Language.pb.h"
#include "Common/DataAccessObjects/LanguageDao.h"
#include "Common/DataAccessObjects/TagDao.h"

UserTaskStreamEmailGenerator::UserTaskStreamEmailGenerator()
{
    //Default Constructor
}

void UserTaskStreamEmailGenerator::run()
{
    qDebug() << "EmailGenerator: Generating UserTaskStreamEmailGenerator";

    UserTaskStreamEmail emailRequest;
    emailRequest.ParseFromString(this->protoBody.toStdString());

    QString error = "";
    QSharedPointer<Email> email;
    QSharedPointer<User> user;
    QList<QSharedPointer<Task> > userTasks;
    MySQLHandler *db = new MySQLHandler(QUuid::createUuid().toString());

    if (db->init()) {
        user = UserDao::getUser(db, emailRequest.user_id());
        userTasks = UserDao::getUserTopTasks(db, emailRequest.user_id(), 25);

        if (user.isNull() || userTasks.count() < 1) {
            error = "Failed to generate UserTaskStream email: Unable to find relevant ";
            error += "data in the Database. Searched for User with ID ";
            error += QString::number(emailRequest.user_id()) + " and their top tasks";
        }
    } else {
        error = "Failed to generate UserTaskStreamEmail: Unable to Connect to SQL Server.";
        error += " Check conf.ini for connection settings and make sure mysqld has been started.";
        qDebug() << "Unable to Connect to SQL Server. Check conf.ini and try again.";
    }

    if (error == "") {
        ConfigParser settings;
        email = QSharedPointer<Email>(new Email);

        ctemplate::TemplateDictionary dict("userTaskStreamDict");
        foreach (QSharedPointer<Task> task, userTasks) {
            ctemplate::TemplateDictionary *taskSect = dict.AddSectionDictionary("TASK_SECT");
            QString taskView = settings.get("site.url") + "task/" + QString::number(task->id()) + "/view";
            taskSect->SetValue("TASK_VIEW", taskView.toStdString());
            taskSect->SetValue("TASK_TITLE", task->title());

            QString taskType;
            switch (task->tasktype()) {
            case CHUNKING:
                taskType = "Chunking";
                break;
            case TRANSLATION:
                taskType = "Translation";
                break;
            case PROOFREADING:
                taskType = "Proofreading";
                break;
            case POSTEDITING:
                taskType = "Post-Editing";
                break;
            default:
                taskType = "Invalid Type";
                break;
            }
            taskSect->SetValue("TASK_TYPE", taskType.toStdString());

            QSharedPointer<Language> sourceLang = LanguageDao::getLanguage(db, -1,
                     QString::fromStdString(task->sourcelanguagecode()));
            taskSect->SetValue("SOURCE_LANGUAGE", sourceLang->name());

            QSharedPointer<Language> targetLang = LanguageDao::getLanguage(db, -1,
                     QString::fromStdString(task->targetlanguagecode()));
            taskSect->SetValue("TARGET_LANGUAGE", targetLang->name());

            QList<QSharedPointer<Tag> > taskTags = TagDao::getTaskTags(db, task->id());
            if (taskTags.count() > 0) {
                taskSect->ShowSection("TAGS_SECT");
                foreach (QSharedPointer<Tag> tag, taskTags) {
                    ctemplate::TemplateDictionary *tagsList = taskSect->AddSectionDictionary("TAGS_LIST");
                    QString tagDetails = settings.get("site.url") + "tag/" + QString::fromStdString(tag->label());
                    tagsList->SetValue("TAG_DETAILS", tagDetails.toStdString());
                    tagsList->SetValue("TAG_LABEL", tag->label());
                }
            }

            taskSect->SetValue("WORD_COUNT", QString::number(task->wordcount()).toStdString());
            QString createdTime = QDateTime::fromString(QString::fromStdString(task->createdtime()),
                       "yyyy-MM-ddTHH:mm:ss").toString("d MMMM yyyy - hh:mm");
            taskSect->SetValue("CREATE_TIME", createdTime.toStdString());
            QString deadline = QDateTime::fromString(QString::fromStdString(task->deadline()),
                    "yyyy-MM-ddTHH:mm:ss").toString("d MMMM yyyy - hh:mm");
            taskSect->SetValue("DEADLINE_TIME", deadline.toStdString());

            QSharedPointer<Project> project = ProjectDao::getProject(db, task->projectid());
            if (!project.isNull()) {
                QString projectView = settings.get("site.url") + "project/" + QString::number(task->projectid()) +
                                        "/view";
                taskSect->SetValue("PROJECT_VIEW", projectView.toStdString());
                taskSect->SetValue("PROJECT_TITLE", project->title());

                QSharedPointer<Organisation> org = OrganisationDao::getOrg(db, project->organisationid());
                if (!org.isNull()) {
                    QString orgView = settings.get("site.url") + "org/" + QString::number(project->organisationid()) +
                                    "/profile";
                    taskSect->SetValue("ORG_VIEW", orgView.toStdString());
                    taskSect->SetValue("ORG_NAME", org->name());
                }
            }
        }

        std::string email_body;
        QString templateLocation = QString(TEMPLATE_DIRECTORY) + "emails/user-task-stream.tpl";
        ctemplate::ExpandTemplate(templateLocation.toStdString(), ctemplate::DO_NOT_STRIP, &dict, &email_body);

        email->setSender(settings.get("site.system_email_address"));;
        email->addRecipient(QString::fromStdString(user->email()));
        email->setSubject("Task Stream");
        email->setBody(QString::fromStdString(email_body));

        QString sentDateTime = QDateTime::currentDateTime().toString("yyyy-MM-dd HH:mm:ss");
        if (UserDao::taskStreamNotificationSent(db, emailRequest.user_id(), sentDateTime)) {
            qDebug() << "UserTaskStreamEmailGenerator: Sending notification request for user " <<
                        QString::number(emailRequest.user_id());
        } else {
            qDebug() << "UserTaskStreamEmailGenerator: Failed to update last sent date for user id "
                        << emailRequest.user_id();
        }
    } else {
        email = this->generateErrorEmail(error);
    }

    delete db;

    this->emailQueue->insert(email, this->currentMessage);
}
