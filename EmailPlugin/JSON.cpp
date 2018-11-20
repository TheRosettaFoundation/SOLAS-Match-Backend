#include "JSON.h"

#include <QDebug>

namespace SolasMatch::Common::Protobufs::Emails {

bool JSON::isJSON(std::string json_serialized)
{
    // Not the most efficient way, but simpler and safer to implement
    return !QJsonDocument::fromJson(QByteArray(json_serialized.c_str(), json_serialized.length())).isNull();
}

void JSON::ParseFromString(std::string json_serialized)
{
    json_object = QJsonDocument::fromJson(QByteArray(json_serialized.c_str(), json_serialized.length())).object();
}

int JSON::email_type()
{
    return json_object.value("email_type").toInt(0);
}

int JSON::user_id()
{
    return json_object.value("user_id").toInt(0);
}

int JSON::project_id()
{
    return json_object.value("project_id").toInt(0);
}

int JSON::task_id()
{
    return json_object.value("task_id").toInt(0);
}

int JSON::claimant_id()
{
    return json_object.value("claimant_id").toInt(0);
}

int JSON::translator_id()
{
    return json_object.value("translator_id").toInt(0);
}

int JSON::org_id()
{
    return json_object.value("org_id").toInt(0);
}

int JSON::org_member_id()
{
    return json_object.value("org_member_id").toInt(0);
}

int JSON::badge_id()
{
    return json_object.value("badge_id").toInt(0);
}

int JSON::site_admin_id()
{
    return json_object.value("site_admin_id").toInt(0);
}

int JSON::org_admin_id()
{
    return json_object.value("org_admin_id").toInt(0);
}

int JSON::file_version()
{
    return json_object.value("file_version").toInt(0);
}

std::string JSON::class_name()
{
    return json_object.value("class_name").toString("");
}

std::string JSON::feedback()
{
    return json_object.value("feedback").toString("");
}

std::string JSON::body()
{
    return json_object.value("body").toString("");
}

std::string JSON::recipient_email()
{
    return json_object.value("recipient_email").toString("");
}

}