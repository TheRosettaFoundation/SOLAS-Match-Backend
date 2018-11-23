#include "JSON.h"

#include <QDebug>

namespace SolasMatch::Common::Protobufs::Emails {

bool JSON::isJSON(std::string json_serialized)
{
if (!QJsonDocument::fromJson(QByteArray(json_serialized.c_str(), json_serialized.length())).isNull()) {
  qDebug() << "isJSON";
} else {
  qDebug() << "NOT isJSON";
}
    // Not the most efficient way, but simpler and safer to implement
    return !QJsonDocument::fromJson(QByteArray(json_serialized.c_str(), json_serialized.length())).isNull();
}

void JSON::ParseFromString(std::string json_serialized)
{
    json_object = QJsonDocument::fromJson(QByteArray(json_serialized.c_str(), json_serialized.length())).object();
}

int JSON::email_type()
{
qDebug() << "JSON::email_type(): " << QString::number(json_object.value("email_type").toInt(0));
    return json_object.value("email_type").toInt(0);
}

int JSON::user_id()
{
qDebug() << "JSON::user_id(): " << QString::number(json_object.value("user_id").toInt(0));
    return json_object.value("user_id").toInt(0);
}

int JSON::project_id()
{
qDebug() << "JSON::project_id(): " << QString::number(json_object.value("project_id").toInt(0));
    return json_object.value("project_id").toInt(0);
}

int JSON::task_id()
{
qDebug() << "JSON::task_id(): " << QString::number(json_object.value("task_id").toInt(0));
    return json_object.value("task_id").toInt(0);
}

int JSON::claimant_id()
{
qDebug() << "JSON::claimant_id(): " << QString::number(json_object.value("claimant_id").toInt(0));
    return json_object.value("claimant_id").toInt(0);
}

int JSON::translator_id()
{
qDebug() << "JSON::translator_id(): " << QString::number(json_object.value("translator_id").toInt(0));
    return json_object.value("translator_id").toInt(0);
}

int JSON::org_id()
{
qDebug() << "JSON::org_id(): " << QString::number(json_object.value("org_id").toInt(0));
    return json_object.value("org_id").toInt(0);
}

int JSON::org_member_id()
{
qDebug() << "JSON::org_member_id(): " << QString::number(json_object.value("org_member_id").toInt(0));
    return json_object.value("org_member_id").toInt(0);
}

int JSON::badge_id()
{
qDebug() << "JSON::badge_id(): " << QString::number(json_object.value("badge_id").toInt(0));
    return json_object.value("badge_id").toInt(0);
}

int JSON::site_admin_id()
{
qDebug() << "JSON::site_admin_id(): " << QString::number(json_object.value("site_admin_id").toInt(0));
    return json_object.value("site_admin_id").toInt(0);
}

int JSON::org_admin_id()
{
qDebug() << "JSON::org_admin_id(): " << QString::number(json_object.value("org_admin_id").toInt(0));
    return json_object.value("org_admin_id").toInt(0);
}

int JSON::file_version()
{
qDebug() << "JSON::file_version(): " << QString::number(json_object.value("file_version").toInt(0));
    return json_object.value("file_version").toInt(0);
}

std::string JSON::class_name()
{
qDebug() << "JSON::class_name(): " << json_object.value("class_name").toString("");
    return json_object.value("class_name").toString("");
}

std::string JSON::feedback()
{
qDebug() << "JSON::feedback(): " << json_object.value("feedback").toString("");
    return json_object.value("feedback").toString("");
}

std::string JSON::body()
{
qDebug() << "JSON::body(): " << json_object.value("body").toString("");
    return json_object.value("body").toString("");
}

std::string JSON::recipient_email()
{
qDebug() << "JSON::recipient_email(): " << json_object.value("recipient_email").toString("");
    return json_object.value("recipient_email").toString("");
}

}
