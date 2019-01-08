#include "ModelGenerator.h"

#include "Common/MySQLHandler.h"
#include "Common/protobufs/models/Locale.pb.h"
#include <QDebug>

void ModelGenerator::Generate(QSharedPointer<QSqlQuery> q, QSharedPointer<Badge> badge, QMap<QString, int> fieldMap)
{
    badge->set_id(MySQLHandler::getValueFromQuery(fieldMap.value("id"), q).toInt());
    badge->set_title(MySQLHandler::getStringFromQuery(fieldMap.value("title"), q));
    badge->set_description(MySQLHandler::getStringFromQuery(fieldMap.value("description"), q));
    badge->set_owner_id(MySQLHandler::getValueFromQuery(fieldMap.value("owner_id"), q).toInt());
}

void ModelGenerator::Generate(QSharedPointer<QSqlQuery> q, QSharedPointer<User> user, QMap<QString, int> fieldMap)
{
    user->set_id(MySQLHandler::getValueFromQuery(fieldMap.value("id"), q).toInt());
    user->set_biography(MySQLHandler::getStringFromQuery(fieldMap.value("biography"), q));
    user->set_created_time(MySQLHandler::getStringFromQuery(fieldMap.value("created_time"), q));
    user->set_display_name(MySQLHandler::getStringFromQuery(fieldMap.value("display_name"), q));
    user->set_email(MySQLHandler::getStringFromQuery(fieldMap.value("email"), q));
    user->set_nonce(MySQLHandler::getStringFromQuery(fieldMap.value("nonce"), q));
    user->set_password(MySQLHandler::getStringFromQuery(fieldMap.value("password"), q));
    Locale *nativeLocale = user->mutable_nativelocale();
    nativeLocale->set_languagecode(MySQLHandler::getStringFromQuery(fieldMap.value("languageCode"), q));
    nativeLocale->set_languagename(MySQLHandler::getStringFromQuery(fieldMap.value("languageName"), q));
    nativeLocale->set_countrycode(MySQLHandler::getStringFromQuery(fieldMap.value("countryCode"), q));
    nativeLocale->set_countryname(MySQLHandler::getStringFromQuery(fieldMap.value("countryName"), q));
}

void ModelGenerator::Generate(QSharedPointer<QSqlQuery> q, QSharedPointer<Tag> tag, QMap<QString, int> fieldMap)
{
    tag->set_id(MySQLHandler::getValueFromQuery(fieldMap.value("id"), q).toInt());
    tag->set_label(MySQLHandler::getStringFromQuery(fieldMap.value("label"), q));
}

void ModelGenerator::Generate(QSharedPointer<QSqlQuery> q, QSharedPointer<Organisation> org, QMap<QString, int> fieldMap)
{
    org->set_id(MySQLHandler::getValueFromQuery(fieldMap.value("id"), q).toInt());
    org->set_name(MySQLHandler::getStringFromQuery(fieldMap.value("name"), q));
    org->set_biography(MySQLHandler::getStringFromQuery(fieldMap.value("biography"), q));
    org->set_homepage(MySQLHandler::getStringFromQuery(fieldMap.value("homepage"), q));
    org->set_email(MySQLHandler::getStringFromQuery(fieldMap.value("email"), q));
    org->set_address(MySQLHandler::getStringFromQuery(fieldMap.value("address"), q));
    org->set_city(MySQLHandler::getStringFromQuery(fieldMap.value("city"), q));
    org->set_country(MySQLHandler::getStringFromQuery(fieldMap.value("country"), q));
    org->set_regionalfocus(MySQLHandler::getStringFromQuery(fieldMap.value("regionalFocus"), q));
}

void ModelGenerator::Generate(QSharedPointer<QSqlQuery> q, QSharedPointer<ArchivedTask> task, QMap<QString, int> fieldMap)
{
    task->set_id(MySQLHandler::getValueFromQuery(fieldMap.value("id"), q).toInt());
    task->set_projectid(MySQLHandler::getValueFromQuery(fieldMap.value("projectId"), q).toInt());
    task->set_title(MySQLHandler::getStringFromQuery(fieldMap.value("title"), q));
    task->set_comment(MySQLHandler::getStringFromQuery(fieldMap.value("comment"), q));
    task->set_deadline(MySQLHandler::getStringFromQuery(fieldMap.value("deadline"), q));
    task->set_wordcount(MySQLHandler::getValueFromQuery(fieldMap.value("wordCount"), q).toInt());
    task->set_createdtime(MySQLHandler::getStringFromQuery(fieldMap.value("createdTime"), q));
    Locale *sourceLocale = task->mutable_sourcelocale();
    sourceLocale->set_languagename(MySQLHandler::getStringFromQuery(fieldMap.value("sourceLanguageName"), q));
    sourceLocale->set_languagecode(MySQLHandler::getStringFromQuery(fieldMap.value("sourceLanguageCode"), q));
    sourceLocale->set_countryname(MySQLHandler::getStringFromQuery(fieldMap.value("sourceCountryName"), q));
    sourceLocale->set_countrycode(MySQLHandler::getStringFromQuery(fieldMap.value("sourceCountryCode"), q));
    Locale *targetLocale = task->mutable_targetlocale();
    targetLocale->set_languagename(MySQLHandler::getStringFromQuery(fieldMap.value("targetLanguageName"), q));
    targetLocale->set_languagecode(MySQLHandler::getStringFromQuery(fieldMap.value("targetLanguageCode"), q));
    targetLocale->set_countryname(MySQLHandler::getStringFromQuery(fieldMap.value("targetCountryName"), q));
    targetLocale->set_countrycode(MySQLHandler::getStringFromQuery(fieldMap.value("targetCountryCode"), q));
    task->set_tasktype(MySQLHandler::getValueFromQuery(fieldMap.value("taskType"), q).toInt());
    task->set_taskstatus(MySQLHandler::getStringFromQuery(fieldMap.value("taskStatus"), q));
    task->set_published(MySQLHandler::getValueFromQuery(fieldMap.value("published"), q).toBool());
    task->set_version(MySQLHandler::getValueFromQuery(fieldMap.value("version"), q).toInt());
    task->set_filename(MySQLHandler::getStringFromQuery(fieldMap.value("filename"), q));
    task->set_contenttype(MySQLHandler::getStringFromQuery(fieldMap.value("contentType"), q));
    task->set_uploadtime(MySQLHandler::getStringFromQuery(fieldMap.value("uploadTime"), q));
    task->set_useridclaimed(MySQLHandler::getValueFromQuery(fieldMap.value("useridClaimed"), q).toInt());
    task->set_useridarchived(MySQLHandler::getValueFromQuery(fieldMap.value("userIdArchived"), q).toInt());
    task->set_prerequisites(MySQLHandler::getStringFromQuery(fieldMap.value("prerequisites"), q));
    task->set_useridtaskcreator(MySQLHandler::getValueFromQuery(fieldMap.value("userIdTaskCreator"), q).toInt());
    task->set_archiveddate(MySQLHandler::getStringFromQuery(fieldMap.value("archivedDate"), q));
}

void ModelGenerator::Generate(QSharedPointer<QSqlQuery> q, QSharedPointer<Task> task, QMap<QString, int> fieldMap)
{
    task->set_id(MySQLHandler::getValueFromQuery(fieldMap.value("id"), q).toInt());
    task->set_projectid(MySQLHandler::getValueFromQuery(fieldMap.value("projectId"), q).toInt());
    task->set_title(MySQLHandler::getStringFromQuery(fieldMap.value("title"), q));
    task->set_comment(MySQLHandler::getStringFromQuery(fieldMap.value("comment"), q));
    task->set_deadline(MySQLHandler::getStringFromQuery(fieldMap.value("deadline"), q));
    task->set_wordcount(MySQLHandler::getValueFromQuery(fieldMap.value("wordCount"), q).toInt());
    task->set_createdtime(MySQLHandler::getStringFromQuery(fieldMap.value("createdTime"), q));
    task->set_tasktype(MySQLHandler::getValueFromQuery(fieldMap.value("taskType"), q).toInt());
    task->set_taskstatus(MySQLHandler::getValueFromQuery(fieldMap.value("taskStatus"), q).toInt());
    // task->set_published(MySQLHandler::getValueFromQuery(fieldMap.value("published"), q).toBool());
    // The above is always true!
    // Note that other cases of toBool() do not cause a real issue because...
    // (a) The database has an INT(1) not a BIT(1) [strict in UserTaskStreamNotification]
    // (b) The bool is not used [published in ArchivedTask]
    // (c) Would only generate an error email if the bool turned out to be false because of some unexpected failure [imageUploaded, imageApproved]
    // The database system actually returns a string of one character/byte with the BIT in it...
    task->set_published((bool)(MySQLHandler::getValueFromQuery(fieldMap.value("published"), q).toString().toStdString().at(0)));
    Locale *sourceLocale = task->mutable_sourcelocale();
    sourceLocale->set_countrycode(MySQLHandler::getStringFromQuery(fieldMap.value("sourceCountryCode"), q));
    sourceLocale->set_countryname(MySQLHandler::getStringFromQuery(fieldMap.value("sourceCountryName"), q));
    sourceLocale->set_languagecode(MySQLHandler::getStringFromQuery(fieldMap.value("sourceLanguageCode"), q));
    sourceLocale->set_languagename(MySQLHandler::getStringFromQuery(fieldMap.value("sourceLanguageName"), q));
    Locale *targetLocale = task->mutable_targetlocale();
    targetLocale->set_countrycode(MySQLHandler::getStringFromQuery(fieldMap.value("targetCountryCode"), q));
    targetLocale->set_countryname(MySQLHandler::getStringFromQuery(fieldMap.value("targetCountryName"), q));
    targetLocale->set_languagecode(MySQLHandler::getStringFromQuery(fieldMap.value("targetLanguageCode"), q));
    targetLocale->set_languagename(MySQLHandler::getStringFromQuery(fieldMap.value("targetLanguageName"), q));
}

void ModelGenerator::Generate(QSharedPointer<QSqlQuery> q, QSharedPointer<Project> project, QMap<QString, int> fieldMap)
{
    project->set_id(MySQLHandler::getValueFromQuery(fieldMap.value("id"), q).toInt());
    project->set_title(MySQLHandler::getStringFromQuery(fieldMap.value("title"), q));
    project->set_description(MySQLHandler::getStringFromQuery(fieldMap.value("description"), q));
    project->set_deadline(MySQLHandler::getStringFromQuery(fieldMap.value("deadline"), q));
    project->set_organisationid(MySQLHandler::getValueFromQuery(fieldMap.value("organisationId"), q).toInt());
    project->set_impact(MySQLHandler::getStringFromQuery(fieldMap.value("impact"), q));
    project->set_reference(MySQLHandler::getStringFromQuery(fieldMap.value("reference"), q));
    project->set_wordcount(MySQLHandler::getValueFromQuery(fieldMap.value("wordCount"), q).toInt());
    project->set_createdtime(MySQLHandler::getStringFromQuery(fieldMap.value("createdTime"), q));
    project->set_status(MySQLHandler::getStringFromQuery(fieldMap.value("status"), q));
    // The database system actually returns a string of one character/byte with the BIT in it...
    project->set_imageuploaded((bool)(MySQLHandler::getValueFromQuery(fieldMap.value("imageUploaded"), q).toString().toStdString().at(0)));
    project->set_imageapproved((bool)(MySQLHandler::getValueFromQuery(fieldMap.value("imageApproved"), q).toString().toStdString().at(0)));
    Locale *sourceLocale = project->mutable_sourcelocale();
    sourceLocale->set_countrycode(MySQLHandler::getStringFromQuery(fieldMap.value("countryCode"), q));
    sourceLocale->set_countryname(MySQLHandler::getStringFromQuery(fieldMap.value("countryName"), q));
    sourceLocale->set_languagecode(MySQLHandler::getStringFromQuery(fieldMap.value("languageCode"), q));
    sourceLocale->set_languagename(MySQLHandler::getStringFromQuery(fieldMap.value("languageName"), q));

}

void ModelGenerator::Generate(QSharedPointer<QSqlQuery> q, QSharedPointer<ArchivedProject> project, QMap<QString, int> fieldMap)
{
    project->set_id(MySQLHandler::getValueFromQuery(fieldMap.value("id"), q).toInt());
    project->set_title(MySQLHandler::getStringFromQuery(fieldMap.value("title"), q));
    project->set_description(MySQLHandler::getStringFromQuery(fieldMap.value("description"), q));
    project->set_impact(MySQLHandler::getStringFromQuery(fieldMap.value("impact"), q));
    project->set_deadline(MySQLHandler::getStringFromQuery(fieldMap.value("deadline"), q));
    project->set_organisationid(MySQLHandler::getValueFromQuery(fieldMap.value("organisationId"), q).toInt());
    project->set_reference(MySQLHandler::getStringFromQuery(fieldMap.value("reference"), q));
    project->set_wordcount(MySQLHandler::getValueFromQuery(fieldMap.value("wordCount"), q).toInt());
    project->set_createdtime(MySQLHandler::getStringFromQuery(fieldMap.value("created"), q));
    Locale *sourceLocale = project->mutable_sourcelocale();
    sourceLocale->set_countrycode(MySQLHandler::getStringFromQuery(fieldMap.value("sourceCountryCode"), q));
    sourceLocale->set_countryname(MySQLHandler::getStringFromQuery(fieldMap.value("sourceCountryName"), q));
    sourceLocale->set_languagecode(MySQLHandler::getStringFromQuery(fieldMap.value("sourceLanguageCode"), q));
    sourceLocale->set_languagename(MySQLHandler::getStringFromQuery(fieldMap.value("sourceLanguageName"), q));
    project->set_useridarchived(MySQLHandler::getValueFromQuery(fieldMap.value("userIdArchived"), q).toInt());
    project->set_useridarchived(MySQLHandler::getValueFromQuery(fieldMap.value("userIdProjectCreator"), q).toInt());
    project->set_filename(MySQLHandler::getStringFromQuery(fieldMap.value("filename"), q));
    project->set_filetoken(MySQLHandler::getStringFromQuery(fieldMap.value("fileToken"), q));
    project->set_mimetype(MySQLHandler::getStringFromQuery(fieldMap.value("mimeType"), q));
    project->set_archiveddate(MySQLHandler::getStringFromQuery(fieldMap.value("archivedDate"), q));
    project->set_tags(MySQLHandler::getStringFromQuery(fieldMap.value("tags"), q));
    project->set_imageuploaded(MySQLHandler::getValueFromQuery(fieldMap.value("imageUploaded"), q).toBool());
    project->set_imageapproved(MySQLHandler::getValueFromQuery(fieldMap.value("imageApproved"), q).toBool());
}

void ModelGenerator::Generate(QSharedPointer<QSqlQuery> q, QSharedPointer<Language> language, QMap<QString, int> fieldMap)
{
    language->set_id(MySQLHandler::getValueFromQuery(fieldMap.value("id"), q).toInt());
    language->set_code(MySQLHandler::getStringFromQuery(fieldMap.value("code"), q));
    language->set_name(MySQLHandler::getStringFromQuery(fieldMap.value("language"), q));
}

void ModelGenerator::Generate(QSharedPointer<QSqlQuery> q, QSharedPointer<BannedUser> banData, QMap<QString, int> fieldMap)
{
    banData->set_userid(MySQLHandler::getValueFromQuery(fieldMap.value("userId"), q).toInt());
    banData->set_useridadmin(MySQLHandler::getValueFromQuery(fieldMap.value("userIdAdmin"), q).toInt());
    banData->set_bantype(MySQLHandler::getValueFromQuery(fieldMap.value("banType"), q).toInt());
    banData->set_comment(MySQLHandler::getStringFromQuery(fieldMap.value("comment"), q));
    banData->set_banneddate(MySQLHandler::getStringFromQuery(fieldMap.value("bannedDate"), q));
}

void ModelGenerator::Generate(QSharedPointer<QSqlQuery> q, QSharedPointer<Locale> localeData, QMap<QString, int> fieldMap)
{
    localeData->set_languagename(MySQLHandler::getStringFromQuery(fieldMap.value("languageName"), q));
    localeData->set_languagecode(MySQLHandler::getStringFromQuery(fieldMap.value("languageCode"), q));
    localeData->set_countryname(MySQLHandler::getStringFromQuery(fieldMap.value("countryName"), q));
    localeData->set_countrycode(MySQLHandler::getStringFromQuery(fieldMap.value("countryCode"), q));
}

void ModelGenerator::Generate(QSharedPointer<QSqlQuery> q, QSharedPointer<UserTaskStreamNotification> data, QMap<QString, int> fieldMap)
{
    data->set_user_id(MySQLHandler::getValueFromQuery(fieldMap.value("user_id"), q).toInt());
    data->set_interval(MySQLHandler::getValueFromQuery(fieldMap.value("interval"), q).toInt());
    data->set_strict(MySQLHandler::getValueFromQuery(fieldMap.value("strict"), q).toBool());
    data->set_last_sent(MySQLHandler::getStringFromQuery(fieldMap.value("last_sent"), q));
}
