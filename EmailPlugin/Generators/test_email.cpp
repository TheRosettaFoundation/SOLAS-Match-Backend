#include "test_email.h"
#include "Common/MySQLHandler.h"

#include <QDateTime>

#include "Common/Definitions.h"
#include "Common/protobufs/models/Language.pb.h"
#include "Common/DataAccessObjects/LanguageDao.h"
#include "Common/DataAccessObjects/TagDao.h"

void test_email::run(int task_id, int claimant_id)
{
    qDebug() << "test_email task_id:" << task_id << "claimant_id:" << claimant_id;

    bool sendEmail = true;
    QString error = "";
    QList<QSharedPointer<Task> > userTasks;
    QSharedPointer<MySQLHandler> db = MySQLHandler::getInstance();
    QList<QMap<QString, QVariant>> task_type_details = TaskDao::get_task_type_details(db);

    QSharedPointer<User> user = UserDao::getUser(db, claimant_id);

    if (user.isNull()) {
        sendEmail = false;
        error = "Failed to generate UserTaskStream email (test_email email): Unable to find relevant ";
        error += "data in the Database. Searched for User with ID ";
        error += QString::number(claimant_id) + " and their notification data";
    } else {
        userTasks = UserDao::getUserTopTasks(db, claimant_id, true, 25);

        if (userTasks.count() < 1) {
            sendEmail = false;
            qDebug() << "Failed to generate task stream email: No tasks found for user " << QString::number(claimant_id);
        }
    }

    if (sendEmail) {
        QList<QMap<QString, QVariant>> selections = LanguageDao::get_selections(db);

        ConfigParser settings;

        ctemplate::TemplateDictionary dict("userTaskStreamDictDebug");
        dict.SetValue("SITE_NAME", std::string(settings.get("site.name").toLatin1().constData(), settings.get("site.name").toLatin1().length()));
        if (user->display_name() != "") {
            dict.ShowSection("USER_HAS_NAME");
            dict.SetValue("USERNAME", Email::htmlspecialchars(user->display_name()));
        } else {
            dict.ShowSection("NO_USER_NAME");
        }

        int project_id = 0;
        int tasks_within_cutoff = 0;
        foreach (QSharedPointer<Task> task, userTasks) {
                ctemplate::TemplateDictionary *taskSect = dict.AddSectionDictionary("TASK_SECT");
                QString taskView = settings.get("site.url") + "task/" + QString::number(task->id()) + "/view/?utm_source=email&utm_medium=stream&utm_campaign=task";
                taskSect->SetValue("TASK_VIEW", taskView.toStdString());
                taskSect->SetValue("TASK_TITLE", Email::htmlspecialchars(task->title()));

                std::string task_type = "Invalid Type";
                for (int i = 0; i < task_type_details.size(); i++) {
                    QMap<QString, QVariant> task_type_detail = task_type_details[i];
                    if (task->tasktype() == task_type_detail["type_enum"].toInt()) task_type = task_type_detail["type_text"].toString().toStdString();
                }
                taskSect->SetValue("TASK_TYPE", task_type);

                std::string source_languagename = task->sourcelocale().languagename();
                std::string source_countryname  = task->sourcelocale().countryname();
                std::string target_languagename = task->targetlocale().languagename();
                std::string target_countryname  = task->targetlocale().countryname();
                for (int i = 0; i < selections.size(); i++) {
                    QMap<QString, QVariant> selection = selections[i];
                    if (task->sourcelocale().languagecode() == selection["language_code"].toString().toStdString() && task->sourcelocale().countrycode() == selection["country_code"].toString().toStdString()) {
                        source_languagename = selection["selection"].toString().toStdString();
                        source_countryname  = "ANY";
                    }
                    if (task->targetlocale().languagecode() == selection["language_code"].toString().toStdString() && task->targetlocale().countrycode() == selection["country_code"].toString().toStdString()) {
                        target_languagename = selection["selection"].toString().toStdString();
                        target_countryname  = "ANY";
                    }
                }

                if (source_countryname == "ANY") taskSect->SetValue("SOURCE_LANGUAGE", source_languagename);
                else                             taskSect->SetValue("SOURCE_LANGUAGE", source_languagename + " (" + source_countryname + ")");
                if (target_countryname == "ANY") taskSect->SetValue("TARGET_LANGUAGE", target_languagename);
                else                             taskSect->SetValue("TARGET_LANGUAGE", target_languagename + " (" + target_countryname + ")");

                taskSect->SetValue("WORD_COUNT", QString::number(task->wordcount()).toStdString());
                QString createdTime = QDateTime::fromString(QString::fromStdString(task->createdtime()),
                           "yyyy-MM-ddTHH:mm:ss.zzz").toString("d MMMM yyyy - hh:mm");
                taskSect->SetValue("CREATED_TIME", createdTime.toStdString());
                QString deadline = QDateTime::fromString(QString::fromStdString(task->deadline()),
                        "yyyy-MM-ddTHH:mm:ss.zzz").toString("d MMMM yyyy - hh:mm");
                taskSect->SetValue("DEADLINE_TIME", deadline.toStdString());

                taskSect->SetValue("PREVIOUS_DEADLINE_TIME", TaskDao::max_translation_deadline(db, task));

                QSharedPointer<Project> project = ProjectDao::getProject(db, task->projectid());
                if (!project.isNull()) {
                    if (task->projectid() != project_id) { // Display first time only
                        taskSect->ShowSection("DESCRIPTION_SECT");
                        taskSect->SetValue("PROJECT_DESCRIPTION", Email::clean_project_description(project->description()));
                        taskSect->SetValue("PROJECT_IMPACT", Email::uiCleanseHTMLNewlineAndTabs(project->impact()));
                    }

                    if (task->projectid() != project_id) { // Display first time only
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
                    }

                    if (task->projectid() != project_id) { // Display first time only
                        taskSect->ShowSection("PARTOF_SECT");
                        QString projectView = settings.get("site.url") + "project/" + QString::number(task->projectid()) + "/view/?utm_source=email&utm_medium=stream&utm_campaign=project";
                        taskSect->SetValue("PROJECT_VIEW", projectView.toStdString());
                        taskSect->SetValue("PROJECT_TITLE", Email::htmlspecialchars(project->title()));
                        QSharedPointer<Organisation> org = OrganisationDao::getOrg(db, project->organisationid());
                        if (!org.isNull()) {
                            QString orgView = settings.get("site.url") + "org/" + QString::number(project->organisationid()) + "/profile/?utm_source=email&utm_medium=stream&utm_campaign=org";
                            taskSect->SetValue("ORG_VIEW", orgView.toStdString());
                            taskSect->SetValue("ORG_NAME", org->name());
                        }

                        if (project->imageuploaded() && project->imageapproved()) {
                            taskSect->ShowSection("IMAGE_SECT");
                            QString projectImage = settings.get("site.url") + "project/" + QString::number(task->projectid()) + "/image";
                            taskSect->SetValue("PROJECT_IMAGE", projectImage.toStdString());
                        }
                    }
                }

                project_id = task->projectid();
qDebug() << "project_id:" << project_id << "tasks_within_cutoff:" << tasks_within_cutoff; //(**)
                tasks_within_cutoff++;
        }

        if (tasks_within_cutoff > 0) {
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
qDebug() << "body:" << QString::fromUtf8(email_body.c_str());//(**)

            UserDao::queue_email(db, claimant_id, QString::fromStdString(user->email()), "TWB dev: Task Stream", QString::fromUtf8(email_body.c_str()), LOW);
        } else {
            qDebug() << "UserTaskStreamEmailGenerator: No tasks within cutoff for user " << QString::number(claimant_id);
        }
    } else {
        if (error != "") {
            IEmailGenerator::generateErrorEmail(error);
        }
    }
}
