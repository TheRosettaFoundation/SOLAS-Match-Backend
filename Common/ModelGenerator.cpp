#include "ModelGenerator.h"

#include "Common/MySQLHandler.h"

User *ModelGenerator::GenerateUser(QSqlQuery *q)
{
    User *user = new User();

    user->set_user_id(MySQLHandler::getValueFromQuery("user_id", q).toInt());
    user->set_biography(MySQLHandler::getValueFromQuery("biography", q).toString().toStdString());
    user->set_created_time(MySQLHandler::getValueFromQuery("created_time", q).toString().toStdString());
    user->set_display_name(MySQLHandler::getValueFromQuery("display_name", q).toString().toStdString());
    user->set_email(MySQLHandler::getValueFromQuery("email", q).toString().toStdString());
    user->set_native_lang_id(MySQLHandler::getValueFromQuery("native_lang_id", q).toInt());
    user->set_nonce(MySQLHandler::getValueFromQuery("nonce", q).toString().toStdString());
    user->set_password(MySQLHandler::getValueFromQuery("password", q).toString().toStdString());
    user->set_native_region_id(MySQLHandler::getValueFromQuery("native_region_id", q).toInt());

    return user;
}

Tag *ModelGenerator::GenerateTag(QSqlQuery *q)
{
    Tag *tag = new Tag();

    tag->set_id(MySQLHandler::getValueFromQuery("tag_id", q).toInt());
    tag->set_label(MySQLHandler::getValueFromQuery("label", q).toString().toStdString());

    return tag;
}

Organisation *ModelGenerator::GenerateOrg(QSqlQuery *q)
{
    Organisation *org = new Organisation();

    org->set_id(MySQLHandler::getValueFromQuery("id", q).toInt());
    org->set_name(MySQLHandler::getValueFromQuery("name", q).toString().toStdString());
    org->set_biography(MySQLHandler::getValueFromQuery("biography", q).toString().toStdString());
    org->set_home_page(MySQLHandler::getValueFromQuery("home_page", q).toString().toStdString());

    return org;
}

ArchivedTask *ModelGenerator::GenerateArchivedTask(QSqlQuery *q)
{
    ArchivedTask *task = new ArchivedTask();

    task->set_archive_id(MySQLHandler::getValueFromQuery("archived_task_id", q).toInt());
    task->set_task_id(MySQLHandler::getValueFromQuery("task_id", q).toInt());
    task->set_org_id(MySQLHandler::getValueFromQuery("organisation_id", q).toInt());
    task->set_title(MySQLHandler::getValueFromQuery("title", q).toString().toStdString());
    task->set_word_count(MySQLHandler::getValueFromQuery("word_count", q).toInt());
    task->set_source_id(MySQLHandler::getValueFromQuery("source_id", q).toInt());
    task->set_target_id(MySQLHandler::getValueFromQuery("target_id", q).toInt());
    task->set_created_time(MySQLHandler::getValueFromQuery("created_time", q).toString().toStdString());
    task->set_archived_time(MySQLHandler::getValueFromQuery("archived_time", q).toString().toStdString());
    task->set_impact(MySQLHandler::getValueFromQuery("impact", q).toString().toStdString());
    task->set_reference_page(MySQLHandler::getValueFromQuery("reference_page", q).toString().toStdString());

    return task;
}
