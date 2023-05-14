#include "ClaimedTaskUploadedGenerator.h"

using namespace  SolasMatch::Common::Protobufs::Emails;

static void ClaimedTaskUploadedGenerator::run(int task_id, int translator_id)
{
    qDebug() << "ClaimedTaskUploadedGenerator task_id:" << QString::number(task_id) << "translator_id:"  << QString::number(translator_id);

    ConfigParser settings;
    QString error = "";
    QSharedPointer<MySQLHandler> db = MySQLHandler::getInstance();
    QList<QMap<QString, QVariant>> task_type_details = TaskDao::get_task_type_details(db);
    QSharedPointer<User> user = UserDao::getUser(db, translator_id);
    QSharedPointer<Task> task = TaskDao::getTask(db, task_id);
    QSharedPointer<Project> project = QSharedPointer<Project>();
    QSharedPointer<Organisation> org = QSharedPointer<Organisation>();

    if (user.isNull() || task.isNull()) {
        error = "Unable to generate claimed task uploaded email. Unable to find relevant data ";
        error += "in the DB, searched for user id " + QString::number(translator_id);
        error += " and task id " + QString::number(task_id);
    } else {
        project = ProjectDao::getProject(db, task->projectid());

        if (project.isNull()) {
            error += "Unable to generate claimed task uploaded email. Unable to find relevant data ";
            error += "in the DB, searched for project id " + task->projectid();
        } else {
            org = OrganisationDao::getOrg(db, project->organisationid());

            if (org.isNull()) {
                error += "Unable to generate claimed task uploaded email. Unable to find relevant data ";
                error += "in the DB, searched for organisation id " + project->organisationid();
            }
        }
    }

    if (error == "") {
        ctemplate::TemplateDictionary dict("claimed-task-uploaded");

        dict.SetValue("USERNAME", Email::htmlspecialchars(user->display_name()));
        dict.SetValue("SITE_NAME", std::string(settings.get("site.name").toLatin1().constData(), settings.get("site.name").toLatin1().length()));
        dict.SetValue("TASK_TITLE", Email::htmlspecialchars(task->title()));
        dict.SetValue("ORG_NAME", org->name());
        QString uploadUrl = settings.get("site.url");
        QString reviewUrl = settings.get("site.url");
        QString profileUrl = settings.get("site.url");
        uploadUrl += "task/" + QString::number(task->id()) + "/view";
        reviewUrl += "task/" + QString::number(task->id()) + "/review";
        profileUrl += QString::number(user->id()) + "/profile/";

        dict.SetValue("TASK_UPLOAD", uploadUrl.toStdString());
        dict.SetValue("TASK_REVIEW", reviewUrl.toStdString());
        dict.SetValue("USER_PROFILE", profileUrl.toStdString());

        std::string task_type = "Invalid Type";
        for (int i = 0; i < task_type_details.size(); i++) {
            QMap<QString, QVariant> task_type_detail = task_type_details[i];
            if (task->tasktype() == task_type_detail["type_enum"].toInt()) {
                task_type = task_type_detail["type_text"].toString().toStdString();
                if (task->tasktype() != TRANSLATION) dict.ShowSection(task_type_detail["show_section"].toString().toStdString());
            }
        }
        dict.SetValue("TASK_TYPE", task_type);

        Locale taskSourceLocale =  task->sourcelocale();
        Locale taskTargetLocale = task->targetlocale();
        dict.SetValue("SOURCE_LANGUAGE",taskSourceLocale.languagename());
        dict.SetValue("TARGET_LANGUAGE",taskTargetLocale.languagename());

        dict.SetValue("COMMUNITY", ProjectDao::discourse_parameterize(project->title(), task->projectid()));

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
        QString template_location = QString(TEMPLATE_DIRECTORY) + "emails/claimed-task-uploaded.tpl";
        ctemplate::ExpandTemplate(template_location.toStdString(), ctemplate::DO_NOT_STRIP, &dict, &email_body);

        UserDao::queue_email(db, translator_id, QString::fromStdString(user->email()), settings.get("site.name") + ": Task Successfully Completed", QString::fromUtf8(email_body.c_str()));
        UserDao::log_email_sent(db, translator_id, task_id, task->projectid(), project->organisationid(), 0, 0, 0, "task_completed_to_volunteer");
    } else {
        this->generateErrorEmail(error);
    }
}
