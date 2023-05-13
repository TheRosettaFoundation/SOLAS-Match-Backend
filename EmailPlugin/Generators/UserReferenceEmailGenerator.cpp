#include "UserReferenceEmailGenerator.h"

#include <QDateTime>

#include "Common/protobufs/models/ArchivedProject.pb.h"
#include "Common/DataAccessObjects/LanguageDao.h"

using namespace  SolasMatch::Common::Protobufs::Emails;

static void UserReferenceEmailGenerator::run(int user_id)
{
    qDebug() << "UserReferenceEmailGenerator user_id:" << user_id;

    ConfigParser settings;
    QString error;
    QSharedPointer<MySQLHandler> db = MySQLHandler::getInstance();
    QList<QMap<QString, QVariant>> task_type_details = TaskDao::get_task_type_details(db);
    QSharedPointer<User> user = UserDao::getUser(db, user_id);

    if (user.isNull()) {
        error += "Failed to generate User Reference email: Unable to find relevant ";
        error += "data in the Database. Searched for User ID ";
        error += QString::number(user_id);
    }

    if (error == "") {
        QList<QMap<QString, QVariant>> selections = LanguageDao::get_selections(db);

        ctemplate::TemplateDictionary dict("user_task_claim");
        QString realName = UserDao::getUserRealName(db, user->id());
        std::string displayName = user->display_name();
        if (realName != "") {
            displayName = realName.toStdString();
        }
        dict.SetValue("DISPLAY_NAME", Email::htmlspecialchars(displayName));

        QList<QSharedPointer<Task> > tasks = UserDao::getUserTasks(db, user->id());
        QList<QSharedPointer<ArchivedTask> > archivedTasks = UserDao::getUserArchivedTasks(db, user->id());

if (user->id() == 3297) { // test code (3297 is id for Alan Barrett)
        tasks = UserDao::getUserTasks(db, 16590);
        archivedTasks = UserDao::getUserArchivedTasks(db, 16590);
}

        if (tasks.length() > 0 || archivedTasks.length() > 0) {
            dict.ShowSection("TASKS_AVAILABLE");
            if (tasks.length() > 0) {
                foreach (QSharedPointer<Task> task, tasks) {
                    ctemplate::TemplateDictionary *taskSect = dict.AddSectionDictionary("TASKS");
                    taskSect->SetValue("TASK_TITLE", Email::htmlspecialchars(task->title()));

                    QString orgName;
                    QSharedPointer<Project> project = ProjectDao::getProject(db, task->projectid());
                    if (!project.isNull()) {
                        QSharedPointer<Organisation> org = OrganisationDao::getOrg(db, project->organisationid());
                        if (!org.isNull()) {
                            orgName = QString::fromStdString(org->name());
                        } else {
                            qWarning() << "Failed to load org " + project->organisationid();
                            orgName = "Missing data";
                        }
                    } else {
                        qWarning() << "Failed to load project " + task->projectid();
                        orgName = "Missing data";
                    }
                    taskSect->SetValue("ORG_NAME", orgName.toStdString());

                    std::string task_type = "Invalid Type";
                    std::string pricing_and_recognition_unit_text = "Words";
                    int source_and_target = 1;
                    for (int i = 0; i < task_type_details.size(); i++) {
                        QMap<QString, QVariant> task_type_detail = task_type_details[i];
                        if (task->tasktype() == task_type_detail["type_enum"].toInt()) {
                            task_type = task_type_detail["type_text"].toString().toStdString();
                            pricing_and_recognition_unit_text = task_type_detail["pricing_and_recognition_unit_text"].toString().toStdString();
                            source_and_target = task_type_detail["source_and_target"].toInt();
                        }
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

                    if (source_and_target) {
                        if (source_countryname == "ANY") taskSect->SetValue("SOURCE", source_languagename);
                        else                             taskSect->SetValue("SOURCE", source_languagename + " (" + source_countryname + ")");
                    } else {
                        taskSect->SetValue("SOURCE", "");
                    }
                    if (target_countryname == "ANY") taskSect->SetValue("TARGET", target_languagename);
                    else                             taskSect->SetValue("TARGET", target_languagename + " (" + target_countryname + ")");

                    taskSect->SetValue("WORD_COUNT", QString::number(task->wordcount()).toStdString() + " " + pricing_and_recognition_unit_text);
                    QString createdTime = QDateTime::fromString(QString::fromStdString(task->createdtime()), "yyyy-MM-ddTHH:mm:ss.zzz").toString("d MMMM yyyy");
                    taskSect->SetValue("CREATED_TIME", createdTime.toStdString());
                }
            }
            if (archivedTasks.length() > 0) {
                foreach (QSharedPointer<ArchivedTask> task, archivedTasks) {
                    ctemplate::TemplateDictionary *taskSect = dict.AddSectionDictionary("TASKS");
                    taskSect->SetValue("TASK_TITLE", Email::htmlspecialchars(task->title()));

                    QString orgName;
                    QSharedPointer<ArchivedProject> archivedProject = ProjectDao::getArchivedProject(db, task->projectid());
                    if (!archivedProject.isNull()) {
                        QSharedPointer<Organisation> org = OrganisationDao::getOrg(db, archivedProject->organisationid());
                        if (!org.isNull()) {
                            orgName = QString::fromStdString(org->name());
                        } else {
                            qWarning() << "Failed to load org " + archivedProject->organisationid();
                            orgName = "Missing Data";
                        }
                    } else {
                        QSharedPointer<Project> project = ProjectDao::getProject(db, task->projectid());
                        if (!project.isNull()) {
                            QSharedPointer<Organisation> org = OrganisationDao::getOrg(db, project->organisationid());
                            if (!org.isNull()) {
                                orgName = QString::fromStdString(org->name());
                            } else {
                                qWarning() << "Failed to load org " + project->organisationid();
                                orgName = "Missing Data";
                            }
                        } else {
                            qWarning() << "Failed to load project " + task->projectid();
                            orgName = "Missing Data";
                        }
                    }
                    taskSect->SetValue("ORG_NAME", orgName.toStdString());

                    std::string task_type = "Invalid Type";
                    std::string pricing_and_recognition_unit_text = "Words";
                    int source_and_target = 1;
                    for (int i = 0; i < task_type_details.size(); i++) {
                        QMap<QString, QVariant> task_type_detail = task_type_details[i];
                        if (task->tasktype() == task_type_detail["type_enum"].toInt()) {
                            task_type = task_type_detail["type_text"].toString().toStdString();
                            pricing_and_recognition_unit_text = task_type_detail["pricing_and_recognition_unit_text"].toString().toStdString();
                            source_and_target = task_type_detail["source_and_target"].toInt();
                        }
                    }
                    taskSect->SetValue("TASK_TYPE", task_type);
                    if (source_and_target) {
                        taskSect->SetValue("SOURCE", task->sourcelocale().languagename() + " (" + task->sourcelocale().countryname() + ")");
                    } else {
                        taskSect->SetValue("SOURCE", "");
                    }
                    taskSect->SetValue("TARGET", task->targetlocale().languagename() + " (" +
                                       task->targetlocale().countryname() + ")");
                    taskSect->SetValue("WORD_COUNT", QString::number(task->wordcount()).toStdString() + " " + pricing_and_recognition_unit_text);
                    QString uploadTime = QDateTime::fromString(QString::fromStdString(task->uploadtime()), "yyyy-MM-ddTHH:mm:ss.zzz").toString("d MMMM yyyy");
                    taskSect->SetValue("CREATED_TIME", uploadTime.toStdString());
                }
            }
        } else {
            dict.ShowSection("NO_TASKS");
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
        QString template_location = QString(TEMPLATE_DIRECTORY) + "emails/user-reference.tpl";
        ctemplate::ExpandTemplate(template_location.toStdString(), ctemplate::DO_NOT_STRIP, &dict, &email_body);

        UserDao::queue_email(db, user_id, QString::fromStdString(user->email()), settings.get("site.name") + ": User Reference", QString::fromUtf8(email_body.c_str()));
        UserDao::log_email_sent(db, user_id, 0, 0, 0, 0, 0, 0, "reference_to_volunteer");
    } else {
        generateErrorEmail(error);
    }
}
