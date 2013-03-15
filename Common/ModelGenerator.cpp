#include "ModelGenerator.h"

#include "Common/MySQLHandler.h"

QSharedPointer<User> ModelGenerator::GenerateUser(QSharedPointer<QSqlQuery> q)
{
    QSharedPointer<User> user = QSharedPointer<User>(new User());

    user->set_user_id(MySQLHandler::getValueFromQuery("id", q).toInt());
    user->set_biography(MySQLHandler::getValueFromQuery("biography", q).toString().toStdString());
    user->set_created_time(MySQLHandler::getValueFromQuery("created-time", q).toString().toStdString());
    user->set_display_name(MySQLHandler::getValueFromQuery("display-name", q).toString().toStdString());
    user->set_email(MySQLHandler::getValueFromQuery("email", q).toString().toStdString());
    user->set_native_lang_id(MySQLHandler::getValueFromQuery("language_id", q).toString().toStdString());
    user->set_nonce(MySQLHandler::getValueFromQuery("nonce", q).toString().toStdString());
    user->set_password(MySQLHandler::getValueFromQuery("password", q).toString().toStdString());
    user->set_native_region_id(MySQLHandler::getValueFromQuery("country_id", q).toString().toStdString());

    return user;
}

QSharedPointer<Tag> ModelGenerator::GenerateTag(QSharedPointer<QSqlQuery> q)
{
    QSharedPointer<Tag> tag = QSharedPointer<Tag>(new Tag());

    tag->set_id(MySQLHandler::getValueFromQuery("id", q).toInt());
    tag->set_label(MySQLHandler::getValueFromQuery("label", q).toString().toStdString());

    return tag;
}

QSharedPointer<Organisation> ModelGenerator::GenerateOrg(QSharedPointer<QSqlQuery> q)
{
    QSharedPointer<Organisation> org = QSharedPointer<Organisation>(new Organisation);

    org->set_id(MySQLHandler::getValueFromQuery("id", q).toInt());
    org->set_name(MySQLHandler::getValueFromQuery("name", q).toString().toStdString());
    org->set_biography(MySQLHandler::getValueFromQuery("biography", q).toString().toStdString());
    org->set_home_page(MySQLHandler::getValueFromQuery("home-page", q).toString().toStdString());

    return org;
}

QSharedPointer<ArchivedTask> ModelGenerator::GenerateArchivedTask(QSharedPointer<QSqlQuery> q)
{
    QSharedPointer<ArchivedTask> task = QSharedPointer<ArchivedTask>(new ArchivedTask());

    task->set_id(MySQLHandler::getValueFromQuery("id", q).toInt());
    task->set_projectid(MySQLHandler::getValueFromQuery("project_id", q).toInt());
    task->set_title(MySQLHandler::getValueFromQuery("title", q).toString().toStdString());
    task->set_comment(MySQLHandler::getValueFromQuery("comment", q).toString().toStdString());
    task->set_deadline(MySQLHandler::getValueFromQuery("deadline", q).toString().toStdString());
    task->set_wordcount(MySQLHandler::getValueFromQuery("word-count", q).toInt());
    task->set_createdtime(MySQLHandler::getValueFromQuery("created-time", q).toString().toStdString());
    task->set_sourcelanguagecode(MySQLHandler::getValueFromQuery("language_id-source", q).toString().toStdString());
    task->set_targetlanguagecode(MySQLHandler::getValueFromQuery("language_id-target", q).toString().toStdString());
    task->set_sourcecountrycode(MySQLHandler::getValueFromQuery("country_id-source", q).toString().toStdString());
    task->set_targetcountrycode(MySQLHandler::getValueFromQuery("country_id-target", q).toString().toStdString());
    task->set_tasktype(MySQLHandler::getValueFromQuery("taskType_id", q).toString().toStdString());
    task->set_taskstatus(MySQLHandler::getValueFromQuery("taskStatus_id", q).toString().toStdString());
    task->set_published(MySQLHandler::getValueFromQuery("published", q).toBool());
    task->set_translatorid(MySQLHandler::getValueFromQuery("user_id-claimed", q).toInt());
    task->set_archiveuserid(MySQLHandler::getValueFromQuery("user_id-archived", q).toInt());
    task->set_archivedate(MySQLHandler::getValueFromQuery("archived-date", q).toString().toStdString());

    return task;
}

QSharedPointer<Task> ModelGenerator::GenerateTask(QSharedPointer<QSqlQuery> q)
{
    QSharedPointer<Task> task = QSharedPointer<Task>(new Task());

    task->set_id(MySQLHandler::getValueFromQuery("id", q).toInt());
    task->set_projectid(MySQLHandler::getValueFromQuery("project_id", q).toInt());
    task->set_title(MySQLHandler::getValueFromQuery("title", q).toString().toStdString());
    task->set_comment(MySQLHandler::getValueFromQuery("comment", q).toString().toStdString());
    task->set_deadline(MySQLHandler::getValueFromQuery("deadline", q).toString().toStdString());
    task->set_wordcount(MySQLHandler::getValueFromQuery("word-count", q).toInt());
    task->set_createdtime(MySQLHandler::getValueFromQuery("created-time", q).toString().toStdString());
    task->set_sourcelanguagecode(MySQLHandler::getValueFromQuery("language_id-source", q).toString().toStdString());
    task->set_targetlanguagecode(MySQLHandler::getValueFromQuery("language_id-target", q).toString().toStdString());
    task->set_sourcecountrycode(MySQLHandler::getValueFromQuery("country_id-source", q).toString().toStdString());
    task->set_targetcountrycode(MySQLHandler::getValueFromQuery("country_id-target", q).toString().toStdString());
    task->set_tasktype(MySQLHandler::getValueFromQuery("task-type_id", q).toInt());
    task->set_taskstatus(MySQLHandler::getValueFromQuery("task-status_id", q).toInt());
    task->set_published(MySQLHandler::getValueFromQuery("published", q).toBool());

    return task;
}

QSharedPointer<Project> ModelGenerator::GenerateProject(QSharedPointer<QSqlQuery> q)
{
    QSharedPointer<Project> project = QSharedPointer<Project>(new Project());

    project->set_id(MySQLHandler::getValueFromQuery("id", q).toInt());
    project->set_title(MySQLHandler::getValueFromQuery("title", q).toString().toStdString());
    project->set_description(MySQLHandler::getValueFromQuery("description", q).toString().toStdString());
    project->set_deadline(MySQLHandler::getValueFromQuery("deadline", q).toString().toStdString());
    project->set_organisationid(MySQLHandler::getValueFromQuery("organisation_id", q).toInt());
    project->set_impact(MySQLHandler::getValueFromQuery("impact", q).toString().toStdString());
    project->set_reference(MySQLHandler::getValueFromQuery("reference", q).toString().toStdString());
    project->set_wordcount(MySQLHandler::getValueFromQuery("word-count", q).toInt());
    project->set_createdtime(MySQLHandler::getValueFromQuery("created", q).toString().toStdString());
    project->set_sourcelanguagecode(MySQLHandler::getValueFromQuery("language_id", q).toString().toStdString());
    project->set_sourcecountrycode(MySQLHandler::getValueFromQuery("country_id", q).toString().toStdString());

    return project;
}

QSharedPointer<ArchivedProject> ModelGenerator::GenerateArchivedProject(QSharedPointer<QSqlQuery> q)
{
    QSharedPointer<ArchivedProject> project = QSharedPointer<ArchivedProject>(new ArchivedProject());

    project->set_id(MySQLHandler::getValueFromQuery("id", q).toInt());
    project->set_title(MySQLHandler::getValueFromQuery("title", q).toString().toStdString());
    project->set_description(MySQLHandler::getValueFromQuery("description", q).toString().toStdString());
    project->set_deadline(MySQLHandler::getValueFromQuery("deadline", q).toString().toStdString());
    project->set_organisationid(MySQLHandler::getValueFromQuery("organisation_id", q).toInt());
    project->set_impact(MySQLHandler::getValueFromQuery("impact", q).toString().toStdString());
    project->set_reference(MySQLHandler::getValueFromQuery("reference", q).toString().toStdString());
    project->set_wordcount(MySQLHandler::getValueFromQuery("word-count", q).toInt());
    project->set_createdtime(MySQLHandler::getValueFromQuery("created", q).toString().toStdString());
    project->set_languagecode(MySQLHandler::getValueFromQuery("language_id", q).toString().toStdString());
    project->set_countrycode(MySQLHandler::getValueFromQuery("country_id", q).toString().toStdString());
    project->set_archiveddate(MySQLHandler::getValueFromQuery("archived-date", q).toString().toStdString());
    project->set_translatorid(MySQLHandler::getValueFromQuery("user_id-archived", q).toInt());

    return project;
}