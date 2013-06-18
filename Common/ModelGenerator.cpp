#include "ModelGenerator.h"

#include "Common/MySQLHandler.h"
#include "Common/protobufs/models/Locale.pb.h"

void ModelGenerator::Generate(QSharedPointer<QSqlQuery> q, QSharedPointer<User> user)
{
    user->set_id(MySQLHandler::getValueFromQuery("id", q).toInt());
    user->set_biography(MySQLHandler::getValueFromQuery("biography", q).toString().toStdString());
    user->set_created_time(MySQLHandler::getValueFromQuery("created-time", q).toString().toStdString());
    user->set_display_name(MySQLHandler::getValueFromQuery("display-name", q).toString().toStdString());
    user->set_email(MySQLHandler::getValueFromQuery("email", q).toString().toStdString());
    user->set_nonce(MySQLHandler::getValueFromQuery("nonce", q).toString().toStdString());
    user->set_password(MySQLHandler::getValueFromQuery("password", q).toString().toStdString());
    Locale *nativeLocale = user->mutable_nativelocale();
    nativeLocale->set_languagecode(MySQLHandler::getValueFromQuery("languageCode", q).toString().toStdString());
    nativeLocale->set_languagename(MySQLHandler::getValueFromQuery("languageName", q).toString().toStdString());
    nativeLocale->set_countrycode(MySQLHandler::getValueFromQuery("countryCode", q).toString().toStdString());
    nativeLocale->set_countryname(MySQLHandler::getValueFromQuery("countryName", q).toString().toStdString());
}

void ModelGenerator::Generate(QSharedPointer<QSqlQuery> q, QSharedPointer<Tag> tag)
{
    tag->set_id(MySQLHandler::getValueFromQuery("id", q).toInt());
    tag->set_label(MySQLHandler::getValueFromQuery("label", q).toString().toStdString());
}

void ModelGenerator::Generate(QSharedPointer<QSqlQuery> q, QSharedPointer<Organisation> org)
{
    org->set_id(MySQLHandler::getValueFromQuery("id", q).toInt());
    org->set_name(MySQLHandler::getValueFromQuery("name", q).toString().toStdString());
    org->set_biography(MySQLHandler::getValueFromQuery("biography", q).toString().toStdString());
    org->set_homepage(MySQLHandler::getValueFromQuery("home-page", q).toString().toStdString());
    org->set_email(MySQLHandler::getValueFromQuery("e-mail", q).toString().toStdString());
    org->set_address(MySQLHandler::getValueFromQuery("address", q).toString().toStdString());
    org->set_city(MySQLHandler::getValueFromQuery("city", q).toString().toStdString());
    org->set_country(MySQLHandler::getValueFromQuery("country", q).toString().toStdString());
    org->set_regionalfocus(MySQLHandler::getValueFromQuery("regional-focus", q).toString().toStdString());
}

void ModelGenerator::Generate(QSharedPointer<QSqlQuery> q, QSharedPointer<ArchivedTask> task)
{
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
}

void ModelGenerator::Generate(QSharedPointer<QSqlQuery> q, QSharedPointer<Task> task)
{
    task->set_id(MySQLHandler::getValueFromQuery("id", q).toInt());
    task->set_projectid(MySQLHandler::getValueFromQuery("project_id", q).toInt());
    task->set_title(MySQLHandler::getValueFromQuery("title", q).toString().toStdString());
    task->set_comment(MySQLHandler::getValueFromQuery("comment", q).toString().toStdString());
    task->set_deadline(MySQLHandler::getValueFromQuery("deadline", q).toString().toStdString());
    task->set_wordcount(MySQLHandler::getValueFromQuery("word-count", q).toInt());
    task->set_createdtime(MySQLHandler::getValueFromQuery("created-time", q).toString().toStdString());
    task->set_tasktype(MySQLHandler::getValueFromQuery("task-type_id", q).toInt());
    task->set_taskstatus(MySQLHandler::getValueFromQuery("task-status_id", q).toInt());
    task->set_published(MySQLHandler::getValueFromQuery("published", q).toBool());
    Locale *sourceLocale = task->mutable_sourcelocale();
    sourceLocale->set_countrycode(MySQLHandler::getValueFromQuery("sourceCountryCode", q).toString().toStdString());
    sourceLocale->set_countryname(MySQLHandler::getValueFromQuery("sourceCountryName", q).toString().toStdString());
    sourceLocale->set_languagecode(MySQLHandler::getValueFromQuery("sourceLanguageCode", q).toString().toStdString());
    sourceLocale->set_languagename(MySQLHandler::getValueFromQuery("sourceLanguageName", q).toString().toStdString());
    Locale *targetLocale = task->mutable_targetlocale();
    targetLocale->set_countrycode(MySQLHandler::getValueFromQuery("targetCountryCode", q).toString().toStdString());
    targetLocale->set_countryname(MySQLHandler::getValueFromQuery("targetCountryName", q).toString().toStdString());
    targetLocale->set_languagecode(MySQLHandler::getValueFromQuery("targetLanguageCode", q).toString().toStdString());
    targetLocale->set_languagename(MySQLHandler::getValueFromQuery("targetLanguageName", q).toString().toStdString());
}

void ModelGenerator::Generate(QSharedPointer<QSqlQuery> q, QSharedPointer<Project> project)
{
    project->set_id(MySQLHandler::getValueFromQuery("id", q).toInt());
    project->set_title(MySQLHandler::getValueFromQuery("title", q).toString().toStdString());
    project->set_description(MySQLHandler::getValueFromQuery("description", q).toString().toStdString());
    project->set_deadline(MySQLHandler::getValueFromQuery("deadline", q).toString().toStdString());
    project->set_organisationid(MySQLHandler::getValueFromQuery("organisation_id", q).toInt());
    project->set_impact(MySQLHandler::getValueFromQuery("impact", q).toString().toStdString());
    project->set_reference(MySQLHandler::getValueFromQuery("reference", q).toString().toStdString());
    project->set_wordcount(MySQLHandler::getValueFromQuery("word-count", q).toInt());
    project->set_createdtime(MySQLHandler::getValueFromQuery("created", q).toString().toStdString());
    project->set_status(MySQLHandler::getValueFromQuery("status", q).toString().toStdString());
    Locale *sourceLocale = project->mutable_sourcelocale();
    sourceLocale->set_countrycode(MySQLHandler::getValueFromQuery("sourceCountryCode", q).toString().toStdString());
    sourceLocale->set_countryname(MySQLHandler::getValueFromQuery("sourceCountryName", q).toString().toStdString());
    sourceLocale->set_languagecode(MySQLHandler::getValueFromQuery("sourceLanguageCode", q).toString().toStdString());
    sourceLocale->set_languagename(MySQLHandler::getValueFromQuery("sourceLanguageName", q).toString().toStdString());
}

void ModelGenerator::Generate(QSharedPointer<QSqlQuery> q, QSharedPointer<ArchivedProject> project)
{
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
}

void ModelGenerator::Generate(QSharedPointer<QSqlQuery> q, QSharedPointer<Language> language)
{
    language->set_id(MySQLHandler::getValueFromQuery("id", q).toInt());
    language->set_code(MySQLHandler::getValueFromQuery("code", q).toString().toStdString());
    language->set_name(MySQLHandler::getValueFromQuery("language", q).toString().toStdString());
}

void ModelGenerator::Generate(QSharedPointer<QSqlQuery> q, QSharedPointer<BannedUser> banData)
{
    banData->set_userid(MySQLHandler::getValueFromQuery("user_id", q).toInt());
    banData->set_useridadmin(MySQLHandler::getValueFromQuery("user_id-admin", q).toInt());
    banData->set_bantype(MySQLHandler::getValueFromQuery("bannedtype_id", q).toInt());
    banData->set_comment(MySQLHandler::getValueFromQuery("comment", q).toString().toStdString());
    banData->set_banneddate(MySQLHandler::getValueFromQuery("banned-date", q).toString().toStdString());
}

void ModelGenerator::Generate(QSharedPointer<QSqlQuery> q, QSharedPointer<Locale> localeData)
{
    localeData->set_languagename(MySQLHandler::getValueFromQuery("languageName", q).toString().toStdString());
    localeData->set_languagecode(MySQLHandler::getValueFromQuery("languageCode", q).toString().toStdString());
    localeData->set_countryname(MySQLHandler::getValueFromQuery("countryName", q).toString().toStdString());
    localeData->set_countrycode(MySQLHandler::getValueFromQuery("countryCode", q).toString().toStdString());
}

void ModelGenerator::Generate(QSharedPointer<QSqlQuery> q, QSharedPointer<UserTaskStreamNotification> data)
{
    data->set_user_id(MySQLHandler::getValueFromQuery("user_id", q).toInt());
    data->set_interval(MySQLHandler::getValueFromQuery("interval", q).toInt());
    data->set_strict(MySQLHandler::getValueFromQuery("strict", q).toBool());
    data->set_last_sent(MySQLHandler::getValueFromQuery("last-sent", q).toString().toStdString());
}
