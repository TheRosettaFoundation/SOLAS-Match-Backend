#include "UserTaskStreamEmailGenerator.h"

#include <QDateTime>

#include "Common/Definitions.h"
#include "Common/protobufs/models/Language.pb.h"
#include "Common/protobufs/models/UserTaskStreamNotification.pb.h"
#include "Common/DataAccessObjects/LanguageDao.h"
#include "Common/DataAccessObjects/TagDao.h"

using namespace  SolasMatch::Common::Protobufs::Emails;

UserTaskStreamEmailGenerator::UserTaskStreamEmailGenerator()
{
    //Default Constructor
}

void UserTaskStreamEmailGenerator::run()
{
    qDebug() << "EmailGenerator: Generating UserTaskStreamEmailGenerator";

    UserTaskStreamEmail emailRequest;
    emailRequest.ParseFromString(this->protoBody);

    bool sendEmail = true;
    QString error = "";
    QSharedPointer<Email> email;
    QList<QSharedPointer<Task> > userTasks;
    QSharedPointer<MySQLHandler> db = MySQLHandler::getInstance();
    QSharedPointer<User> user = UserDao::getUser(db, emailRequest.user_id());
    QSharedPointer<UserTaskStreamNotification> notifData = UserDao::getUserTaskStreamNotification(db,
                                                             emailRequest.user_id());

    if (user.isNull() || notifData.isNull() ) {
        sendEmail = false;
        error = "Failed to generate UserTaskStream email: Unable to find relevant ";
        error += "data in the Database. Searched for User with ID ";
        error += QString::number(emailRequest.user_id()) + " and their notification data";
    } else {
        if (notifData->strict()) {
            userTasks = UserDao::getUserTopTasks(db, emailRequest.user_id(), true, 25);
        } else {
            userTasks = UserDao::getUserTopTasks(db, emailRequest.user_id(), false, 25);
        }

        if (userTasks.count() < 1) {
            sendEmail = false;
            if (notifData->strict()) {
                qDebug() << "Failed to generate task stream email: No strict tasks found for user "
                         << QString::number(emailRequest.user_id());
            } else {
                qDebug() << "Failed to generate task stream email: No tasks found for user "
                         << QString::number(emailRequest.user_id());
            }
        }
    }

    if (sendEmail) {
        ConfigParser settings;
        email = QSharedPointer<Email>(new Email);

        ctemplate::TemplateDictionary dict("userTaskStreamDict");
        dict.SetValue("SITE_NAME", settings.get("site.name").toStdString());
        foreach (QSharedPointer<Task> task, userTasks) {
            ctemplate::TemplateDictionary *taskSect = dict.AddSectionDictionary("TASK_SECT");
            QString taskView = settings.get("site.url") + "task/" + QString::number(task->id()) + "/view";
            taskSect->SetValue("TASK_VIEW", taskView.toStdString());
            taskSect->SetValue("TASK_TITLE", Email::htmlspecialchars(task->title()));

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

            Locale taskSourceLocale = task->sourcelocale();
            taskSect->SetValue("SOURCE_LANGUAGE", taskSourceLocale.languagename());

            Locale taskTargetLocale = task->targetlocale();
            taskSect->SetValue("TARGET_LANGUAGE", taskTargetLocale.languagename());

            QList<QSharedPointer<Tag> > taskTags = TagDao::getTaskTags(db, task->id());
            if (taskTags.count() > 0) {
                taskSect->ShowSection("TAGS_SECT");
                foreach (QSharedPointer<Tag> tag, taskTags) {
                    ctemplate::TemplateDictionary *tagsList = taskSect->AddSectionDictionary("TAGS_LIST");
                    QString tagDetails = settings.get("site.url") + "tag/" + QString::number(tag->id()) + "/";
                    tagsList->SetValue("TAG_DETAILS", tagDetails.toStdString());
                    tagsList->SetValue("TAG_LABEL", Email::htmlspecialchars(tag->label()));
                }
            }

            taskSect->SetValue("WORD_COUNT", QString::number(task->wordcount()).toStdString());
            QString createdTime = QDateTime::fromString(QString::fromStdString(task->createdtime()),
                       "yyyy-MM-ddTHH:mm:ss").toString("d MMMM yyyy - hh:mm");
            taskSect->SetValue("CREATED_TIME", createdTime.toStdString());
            QString deadline = QDateTime::fromString(QString::fromStdString(task->deadline()),
                    "yyyy-MM-ddTHH:mm:ss").toString("d MMMM yyyy - hh:mm");
            taskSect->SetValue("DEADLINE_TIME", deadline.toStdString());

            QSharedPointer<Project> project = ProjectDao::getProject(db, task->projectid());
            if (!project.isNull()) {
                QString projectView = settings.get("site.url") + "project/" + QString::number(task->projectid()) +
                                        "/view";
                taskSect->SetValue("PROJECT_VIEW", projectView.toStdString());
                taskSect->SetValue("PROJECT_TITLE", Email::htmlspecialchars(project->title()));

                QSharedPointer<Organisation> org = OrganisationDao::getOrg(db, project->organisationid());
                if (!org.isNull()) {
                    QString orgView = settings.get("site.url") + "org/" + QString::number(project->organisationid()) +
                                    "/profile";
                    taskSect->SetValue("ORG_VIEW", orgView.toStdString());
                    taskSect->SetValue("ORG_NAME", org->name());
                }
            }
        }

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
        QString templateLocation = QString(TEMPLATE_DIRECTORY) + "emails/user-task-stream.tpl";
        ctemplate::ExpandTemplate(templateLocation.toStdString(), ctemplate::DO_NOT_STRIP, &dict, &email_body);

        email->setSender(settings.get("site.system_email_address"));;
        email->addRecipient(QString::fromStdString(user->email()));
        email->setSubject(settings.get("site.name") + ": Task Stream");
        email->setBody(QString::fromUtf8(email_body.c_str()));
        this->emailQueue->insert(email, this->currentMessage);
    } else {
        if (error != "") {
            email = this->generateErrorEmail(error);
            this->emailQueue->insert(email, this->currentMessage);
        }
    }

    QString sentDateTime = QDateTime::currentDateTime().toString("yyyy-MM-dd HH:mm:ss");
    if (UserDao::taskStreamNotificationSent(db, emailRequest.user_id(), sentDateTime)) {
        qDebug() << "UserTaskStreamEmailGenerator: Sending notification request for user " <<
                    QString::number(emailRequest.user_id());
    } else {
        qDebug() << "UserTaskStreamEmailGenerator: Failed to update last sent date for user id "
                    << emailRequest.user_id();
    }
}
