#include "UserReferenceEmailGenerator.h"

#include "Common/protobufs/emails/UserReferenceEmail.pb.h"
#include "Common/protobufs/models/ArchivedProject.pb.h"

UserReferenceEmailGenerator::UserReferenceEmailGenerator()
{
    //Default Constructor
}

void UserReferenceEmailGenerator::run()
{
    qDebug() << "EmailGenerator: generating user reference email";
    UserReferenceEmail emailMessage;
    emailMessage.ParseFromString(this->protoBody.toStdString());

    ConfigParser settings;
    QString error;
    QSharedPointer<MySQLHandler> db = MySQLHandler::getInstance();
    QSharedPointer<User> user = UserDao::getUser(db, emailMessage.user_id());
    QSharedPointer<Email> email = QSharedPointer<Email>(new Email());

    if (user.isNull()) {
        error += "Failed to generate User Reference email: Unable to find relevant ";
        error += "data in the Database. Searched for User ID ";
        error += QString::number(emailMessage.user_id());
    }

    if (error == "") {
        ctemplate::TemplateDictionary dict("user_task_claim");
        QString realName = UserDao::getUserRealName(db, user->id());
        std::string displayName = user->display_name();
        if (realName != "") {
            displayName = realName.toStdString();
        }
        dict.SetValue("DISPLAY_NAME", displayName);

        QList<QSharedPointer<Task> > tasks = UserDao::getUserTasks(db, user->id());
        QList<QSharedPointer<ArchivedTask> > archivedTasks = UserDao::getUserArchivedTasks(db, user->id());
        if (tasks.length() > 0 || archivedTasks.length() > 0) {
            dict.ShowSection("TASKS_AVAILABLE");
            if (tasks.length() > 0) {
                foreach (QSharedPointer<Task> task, tasks) {
                    ctemplate::TemplateDictionary *taskSect = dict.AddSectionDictionary("TASKS");
                    taskSect->SetValue("TASK_TITLE", task->title());

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

                    QString taskType;
                    switch (task->tasktype()) {
                    case CHUNKING:
                        taskType = "Segmentation";
                        break;
                    case TRANSLATION:
                        taskType = "Translation";
                        break;
                    case PROOFREADING:
                        taskType = "Proofreading";
                        break;
                    case POSTEDITING:
                        taskType = "Desegmentation";
                        break;
                    default:
                        taskType = "Invalid Type";
                        break;
                    }
                    taskSect->SetValue("TASK_TYPE", taskType.toStdString());
                    taskSect->SetValue("SOURCE", task->sourcelocale().languagename() + " (" +
                                       task->sourcelocale().countryname() + ")");
                    taskSect->SetValue("TARGET", task->targetlocale().languagename() + " (" +
                                       task->targetlocale().countryname() + ")");
                    taskSect->SetValue("WORD_COUNT", QString::number(task->wordcount()).toStdString());
                }
            }
            if (archivedTasks.length() > 0) {
                foreach (QSharedPointer<ArchivedTask> task, archivedTasks) {
                    ctemplate::TemplateDictionary *taskSect = dict.AddSectionDictionary("TASKS");
                    taskSect->SetValue("TASK_TITLE", task->title());

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

                    QString taskType;
                    QString taskTypeId = QString::fromStdString(task->tasktype());
                    if (taskTypeId == QString::number(CHUNKING)) {
                        taskType = "Chunking";
                    } else if(taskTypeId == QString::number(TRANSLATION)) {
                        taskType = "Translation";
                    } else if(taskTypeId == QString::number(PROOFREADING)) {
                        taskType = "Proofreading";
                    } else if(taskTypeId == QString::number(POSTEDITING)) {
                        taskType = "Post-Editing";
                    } else {
                        taskType = "Invalid Type";
                    }
                    taskSect->SetValue("TASK_TYPE", taskType.toStdString());
                    taskSect->SetValue("SOURCE", task->sourcelocale().languagename() + " (" +
                                       task->sourcelocale().countryname() + ")");
                    taskSect->SetValue("TARGET", task->targetlocale().languagename() + " (" +
                                       task->targetlocale().countryname() + ")");
                    taskSect->SetValue("WORD_COUNT", QString::number(task->wordcount()).toStdString());
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
            dict.SetGlobalValue("DONATE_LINK",donate_link.toStdString());
            footer_dict ->SetFilename(footer_location.toStdString());
        }

        std::string email_body;
        QString template_location = QString(TEMPLATE_DIRECTORY) + "emails/user-reference.tpl";
        ctemplate::ExpandTemplate(template_location.toStdString(), ctemplate::DO_NOT_STRIP, &dict, &email_body);

        email->setSender(settings.get("site.system_email_address"));;
        email->addRecipient(QString::fromStdString(user->email()));
        email->setSubject(settings.get("site.name") + ": User Reference");
        email->setBody(QString::fromUtf8(email_body.c_str()));
    } else {
        email = this->generateErrorEmail(error);
    }

    this->emailQueue->insert(email, currentMessage);
}
