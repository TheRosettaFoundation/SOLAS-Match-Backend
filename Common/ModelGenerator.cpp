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
