#include "ModelGenerator.h"

#include "Common/MySQLHandler.h"
#include "Common/protobufs/models/Locale.pb.h"

void ModelGenerator::Generate(QSharedPointer<QSqlQuery> q, QSharedPointer<User> user, QMap<QString, int> fieldMap)
{
    user->set_id(MySQLHandler::getValueFromQuery(fieldMap.value("id"), q).toInt());
    user->set_biography(MySQLHandler::getValueFromQuery(fieldMap.value("biography"), q).toString().toStdString());
    user->set_created_time(MySQLHandler::getValueFromQuery(fieldMap.value("created-time"), q).toString().toStdString());
    user->set_display_name(MySQLHandler::getValueFromQuery(fieldMap.value("display-name"), q).toString().toStdString());
    user->set_email(MySQLHandler::getValueFromQuery(fieldMap.value("email"), q).toString().toStdString());
    user->set_nonce(MySQLHandler::getValueFromQuery(fieldMap.value("nonce"), q).toString().toStdString());
    user->set_password(MySQLHandler::getValueFromQuery(fieldMap.value("password"), q).toString().toStdString());
    Locale *nativeLocale = user->mutable_nativelocale();
    nativeLocale->set_languagecode(MySQLHandler::getValueFromQuery(fieldMap.value("languageCode"), q).toString().toStdString());
    nativeLocale->set_languagename(MySQLHandler::getValueFromQuery(fieldMap.value("languageName"), q).toString().toStdString());
    nativeLocale->set_countrycode(MySQLHandler::getValueFromQuery(fieldMap.value("countryCode"), q).toString().toStdString());
    nativeLocale->set_countryname(MySQLHandler::getValueFromQuery(fieldMap.value("countryName"), q).toString().toStdString());
}

void ModelGenerator::Generate(QSharedPointer<QSqlQuery> q, QSharedPointer<Tag> tag, QMap<QString, int> fieldMap)
{
    tag->set_id(MySQLHandler::getValueFromQuery(fieldMap.value("id"), q).toInt());
    tag->set_label(MySQLHandler::getValueFromQuery(fieldMap.value("label"), q).toString().toStdString());
}

void ModelGenerator::Generate(QSharedPointer<QSqlQuery> q, QSharedPointer<Organisation> org, QMap<QString, int> fieldMap)
{
    org->set_id(MySQLHandler::getValueFromQuery(fieldMap.value("id"), q).toInt());
    org->set_name(MySQLHandler::getValueFromQuery(fieldMap.value("name"), q).toString().toStdString());
    org->set_biography(MySQLHandler::getValueFromQuery(fieldMap.value("biography"), q).toString().toStdString());
    org->set_homepage(MySQLHandler::getValueFromQuery(fieldMap.value("home-page"), q).toString().toStdString());
    org->set_email(MySQLHandler::getValueFromQuery(fieldMap.value("e-mail"), q).toString().toStdString());
    org->set_address(MySQLHandler::getValueFromQuery(fieldMap.value("address"), q).toString().toStdString());
    org->set_city(MySQLHandler::getValueFromQuery(fieldMap.value("city"), q).toString().toStdString());
    org->set_country(MySQLHandler::getValueFromQuery(fieldMap.value("country"), q).toString().toStdString());
    org->set_regionalfocus(MySQLHandler::getValueFromQuery(fieldMap.value("regional-focus"), q).toString().toStdString());
}

void ModelGenerator::Generate(QSharedPointer<QSqlQuery> q, QSharedPointer<ArchivedTask> task, QMap<QString, int> fieldMap)
{
    task->set_id(MySQLHandler::getValueFromQuery(fieldMap.value("id"), q).toInt());
    task->set_projectid(MySQLHandler::getValueFromQuery(fieldMap.value("project_id"), q).toInt());
    task->set_title(MySQLHandler::getValueFromQuery(fieldMap.value("title"), q).toString().toStdString());
    task->set_comment(MySQLHandler::getValueFromQuery(fieldMap.value("comment"), q).toString().toStdString());
    task->set_deadline(MySQLHandler::getValueFromQuery(fieldMap.value("deadline"), q).toString().toStdString());
    task->set_wordcount(MySQLHandler::getValueFromQuery(fieldMap.value("word-count"), q).toInt());
    task->set_createdtime(MySQLHandler::getValueFromQuery(fieldMap.value("created-time"), q).toString().toStdString());
    Locale *sourceLocale = task->mutable_sourcelocale();
    sourceLocale->set_languagename(MySQLHandler::getValueFromQuery(fieldMap.value("sourceLanguageName"), q).toString().toStdString());
    sourceLocale->set_languagecode(MySQLHandler::getValueFromQuery(fieldMap.value("sourceLanguageCode"), q).toString().toStdString());
    sourceLocale->set_countryname(MySQLHandler::getValueFromQuery(fieldMap.value("sourceCountryName"), q).toString().toStdString());
    sourceLocale->set_countrycode(MySQLHandler::getValueFromQuery(fieldMap.value("sourceCountryCode"), q).toString().toStdString());
    Locale *targetLocale = task->mutable_targetlocale();
    targetLocale->set_languagename(MySQLHandler::getValueFromQuery(fieldMap.value("targetLanguageName"), q).toString().toStdString());
    targetLocale->set_languagecode(MySQLHandler::getValueFromQuery(fieldMap.value("targetLanguageCode"), q).toString().toStdString());
    targetLocale->set_countryname(MySQLHandler::getValueFromQuery(fieldMap.value("targetCountryName"), q).toString().toStdString());
    targetLocale->set_countrycode(MySQLHandler::getValueFromQuery(fieldMap.value("targetCountryCode"), q).toString().toStdString());
    task->set_tasktype(MySQLHandler::getValueFromQuery(fieldMap.value("taskType_id"), q).toString().toStdString());
    task->set_taskstatus(MySQLHandler::getValueFromQuery(fieldMap.value("taskStatus_id"), q).toString().toStdString());
    task->set_published(MySQLHandler::getValueFromQuery(fieldMap.value("published"), q).toBool());
    task->set_translatorid(MySQLHandler::getValueFromQuery(fieldMap.value("user_id-claimed"), q).toInt());
    task->set_archiveuserid(MySQLHandler::getValueFromQuery(fieldMap.value("user_id-archived"), q).toInt());
    task->set_archivedate(MySQLHandler::getValueFromQuery(fieldMap.value("archived-date"), q).toString().toStdString());
    task->set_version(MySQLHandler::getValueFromQuery(fieldMap.value("version"), q).toInt());
    task->set_filename(MySQLHandler::getValueFromQuery(fieldMap.value("filename"), q).toString().toStdString());
    task->set_contenttype(MySQLHandler::getValueFromQuery(fieldMap.value("content-type"), q).toString().toStdString());
    task->set_uploadtime(MySQLHandler::getValueFromQuery(fieldMap.value("upload-time"), q).toString().toStdString());
    task->set_useridclaimed(MySQLHandler::getValueFromQuery(fieldMap.value("user_id-claimed"), q).toInt());
    task->set_useridarchived(MySQLHandler::getValueFromQuery(fieldMap.value("user_id-archived"), q).toInt());
    task->set_prerequisites(MySQLHandler::getValueFromQuery(fieldMap.value("prerequisites"), q).toString().toStdString());
    task->set_useridtaskcreator(MySQLHandler::getValueFromQuery(fieldMap.value("user_id-taskCreator"), q).toInt());
    task->set_archivedate(MySQLHandler::getValueFromQuery(fieldMap.value("archived-date"), q).toString().toStdString());
}

void ModelGenerator::Generate(QSharedPointer<QSqlQuery> q, QSharedPointer<Task> task, QMap<QString, int> fieldMap)
{
    task->set_id(MySQLHandler::getValueFromQuery(fieldMap.value("id"), q).toInt());
    task->set_projectid(MySQLHandler::getValueFromQuery(fieldMap.value("project_id"), q).toInt());
    task->set_title(MySQLHandler::getValueFromQuery(fieldMap.value("title"), q).toString().toStdString());
    task->set_comment(MySQLHandler::getValueFromQuery(fieldMap.value("comment"), q).toString().toStdString());
    task->set_deadline(MySQLHandler::getValueFromQuery(fieldMap.value("deadline"), q).toString().toStdString());
    task->set_wordcount(MySQLHandler::getValueFromQuery(fieldMap.value("word-count"), q).toInt());
    task->set_createdtime(MySQLHandler::getValueFromQuery(fieldMap.value("created-time"), q).toString().toStdString());
    task->set_tasktype(MySQLHandler::getValueFromQuery(fieldMap.value("task-type_id"), q).toInt());
    task->set_taskstatus(MySQLHandler::getValueFromQuery(fieldMap.value("task-status_id"), q).toInt());
    task->set_published(MySQLHandler::getValueFromQuery(fieldMap.value("published"), q).toBool());
    Locale *sourceLocale = task->mutable_sourcelocale();
    sourceLocale->set_countrycode(MySQLHandler::getValueFromQuery(fieldMap.value("sourceCountryCode"), q).toString().toStdString());
    sourceLocale->set_countryname(MySQLHandler::getValueFromQuery(fieldMap.value("sourceCountryName"), q).toString().toStdString());
    sourceLocale->set_languagecode(MySQLHandler::getValueFromQuery(fieldMap.value("sourceLanguageCode"), q).toString().toStdString());
    sourceLocale->set_languagename(MySQLHandler::getValueFromQuery(fieldMap.value("sourceLanguageName"), q).toString().toStdString());
    Locale *targetLocale = task->mutable_targetlocale();
    targetLocale->set_countrycode(MySQLHandler::getValueFromQuery(fieldMap.value("targetCountryCode"), q).toString().toStdString());
    targetLocale->set_countryname(MySQLHandler::getValueFromQuery(fieldMap.value("targetCountryName"), q).toString().toStdString());
    targetLocale->set_languagecode(MySQLHandler::getValueFromQuery(fieldMap.value("targetLanguageCode"), q).toString().toStdString());
    targetLocale->set_languagename(MySQLHandler::getValueFromQuery(fieldMap.value("targetLanguageName"), q).toString().toStdString());
}

void ModelGenerator::Generate(QSharedPointer<QSqlQuery> q, QSharedPointer<Project> project, QMap<QString, int> fieldMap)
{
    project->set_id(MySQLHandler::getValueFromQuery(fieldMap.value("id"), q).toInt());
    project->set_title(MySQLHandler::getValueFromQuery(fieldMap.value("title"), q).toString().toStdString());
    project->set_description(MySQLHandler::getValueFromQuery(fieldMap.value("description"), q).toString().toStdString());
    project->set_deadline(MySQLHandler::getValueFromQuery(fieldMap.value("deadline"), q).toString().toStdString());
    project->set_organisationid(MySQLHandler::getValueFromQuery(fieldMap.value("organisation_id"), q).toInt());
    project->set_impact(MySQLHandler::getValueFromQuery(fieldMap.value("impact"), q).toString().toStdString());
    project->set_reference(MySQLHandler::getValueFromQuery(fieldMap.value("reference"), q).toString().toStdString());
    project->set_wordcount(MySQLHandler::getValueFromQuery(fieldMap.value("word-count"), q).toInt());
    project->set_createdtime(MySQLHandler::getValueFromQuery(fieldMap.value("created"), q).toString().toStdString());
    project->set_status(MySQLHandler::getValueFromQuery(fieldMap.value("status"), q).toString().toStdString());
    Locale *sourceLocale = project->mutable_sourcelocale();
    sourceLocale->set_countrycode(MySQLHandler::getValueFromQuery(fieldMap.value("sourceCountryCode"), q).toString().toStdString());
    sourceLocale->set_countryname(MySQLHandler::getValueFromQuery(fieldMap.value("sourceCountryName"), q).toString().toStdString());
    sourceLocale->set_languagecode(MySQLHandler::getValueFromQuery(fieldMap.value("sourceLanguageCode"), q).toString().toStdString());
    sourceLocale->set_languagename(MySQLHandler::getValueFromQuery(fieldMap.value("sourceLanguageName"), q).toString().toStdString());
}

void ModelGenerator::Generate(QSharedPointer<QSqlQuery> q, QSharedPointer<ArchivedProject> project, QMap<QString, int> fieldMap)
{
    project->set_id(MySQLHandler::getValueFromQuery(fieldMap.value("id"), q).toInt());
    project->set_title(MySQLHandler::getValueFromQuery(fieldMap.value("title"), q).toString().toStdString());
    project->set_description(MySQLHandler::getValueFromQuery(fieldMap.value("description"), q).toString().toStdString());
    project->set_deadline(MySQLHandler::getValueFromQuery(fieldMap.value("deadline"), q).toString().toStdString());
    project->set_organisationid(MySQLHandler::getValueFromQuery(fieldMap.value("organisation_id"), q).toInt());
    project->set_impact(MySQLHandler::getValueFromQuery(fieldMap.value("impact"), q).toString().toStdString());
    project->set_reference(MySQLHandler::getValueFromQuery(fieldMap.value("reference"), q).toString().toStdString());
    project->set_wordcount(MySQLHandler::getValueFromQuery(fieldMap.value("word-count"), q).toInt());
    project->set_createdtime(MySQLHandler::getValueFromQuery(fieldMap.value("created"), q).toString().toStdString());
    project->set_languagecode(MySQLHandler::getValueFromQuery(fieldMap.value("language_id"), q).toString().toStdString());
    project->set_countrycode(MySQLHandler::getValueFromQuery(fieldMap.value("country_id"), q).toString().toStdString());
    project->set_archiveddate(MySQLHandler::getValueFromQuery(fieldMap.value("archived-date"), q).toString().toStdString());
    project->set_translatorid(MySQLHandler::getValueFromQuery(fieldMap.value("user_id-archived"), q).toInt());
}

void ModelGenerator::Generate(QSharedPointer<QSqlQuery> q, QSharedPointer<Language> language, QMap<QString, int> fieldMap)
{
    language->set_id(MySQLHandler::getValueFromQuery(fieldMap.value("id"), q).toInt());
    language->set_code(MySQLHandler::getValueFromQuery(fieldMap.value("code"), q).toString().toStdString());
    language->set_name(MySQLHandler::getValueFromQuery(fieldMap.value("language"), q).toString().toStdString());
}

void ModelGenerator::Generate(QSharedPointer<QSqlQuery> q, QSharedPointer<BannedUser> banData, QMap<QString, int> fieldMap)
{
    banData->set_userid(MySQLHandler::getValueFromQuery(fieldMap.value("user_id"), q).toInt());
    banData->set_useridadmin(MySQLHandler::getValueFromQuery(fieldMap.value("user_id-admin"), q).toInt());
    banData->set_bantype(MySQLHandler::getValueFromQuery(fieldMap.value("bannedtype_id"), q).toInt());
    banData->set_comment(MySQLHandler::getValueFromQuery(fieldMap.value("comment"), q).toString().toStdString());
    banData->set_banneddate(MySQLHandler::getValueFromQuery(fieldMap.value("banned-date"), q).toString().toStdString());
}

void ModelGenerator::Generate(QSharedPointer<QSqlQuery> q, QSharedPointer<Locale> localeData, QMap<QString, int> fieldMap)
{
    localeData->set_languagename(MySQLHandler::getValueFromQuery(fieldMap.value("languageName"), q).toString().toStdString());
    localeData->set_languagecode(MySQLHandler::getValueFromQuery(fieldMap.value("languageCode"), q).toString().toStdString());
    localeData->set_countryname(MySQLHandler::getValueFromQuery(fieldMap.value("countryName"), q).toString().toStdString());
    localeData->set_countrycode(MySQLHandler::getValueFromQuery(fieldMap.value("countryCode"), q).toString().toStdString());
}

void ModelGenerator::Generate(QSharedPointer<QSqlQuery> q, QSharedPointer<UserTaskStreamNotification> data, QMap<QString, int> fieldMap)
{
    data->set_user_id(MySQLHandler::getValueFromQuery(fieldMap.value("user_id"), q).toInt());
    data->set_interval(MySQLHandler::getValueFromQuery(fieldMap.value("interval"), q).toInt());
    data->set_strict(MySQLHandler::getValueFromQuery(fieldMap.value("strict"), q).toBool());
    data->set_last_sent(MySQLHandler::getValueFromQuery(fieldMap.value("last-sent"), q).toString().toStdString());
}
