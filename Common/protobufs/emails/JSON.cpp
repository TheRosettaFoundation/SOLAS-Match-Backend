#include "JSON.h"

#include <QDebug>

namespace SolasMatch::Common::Protobufs::Emails {

bool JSON::isJSON(std::string json_serialized)
{
    // Not the most efficient way, but simpler and safer to implement
    return !QJsonDocument::fromJson(QByteArray(json_serialized.c_str(), json_serialized.length())).isNull();
}

bool JSON::ParseFromString(std::string json_serialized)
{
    //qDebug() << QString::fromLatin1(json_serialized.c_str(), json_serialized.length());
    QJsonDocument json_document = QJsonDocument::fromJson(QByteArray(json_serialized.c_str(), json_serialized.length()));

    json_object = json_document.object();

    return !json_document.isNull();
}

int JSON::getInt(QString key)
{
    QJsonValue value = json_object.value(key);
    if (value.type() == QJsonValue::String && value.toString("") != "") {
        //qDebug() << "JSON::" << key << "()String: " << value.toString("");
        return value.toString("").toInt();
    } else {
        //qDebug() << "JSON::" << key << "(): " << QString::number(value.toInt(0));
        return value.toInt(0);
    }
}

std::string JSON::getString(QString key)
{
    QJsonValue value = json_object.value(key);
    //qDebug() << "JSON::" << key << "(): " << value.toString("");
    QByteArray bytes = value.toString("").toUtf8();
    return std::string(bytes.constData(), bytes.length());
}

int JSON::email_type()
{
    return getInt("email_type");
}

int JSON::user_id()
{
    return getInt("user_id");
}

int JSON::project_id()
{
    return getInt("project_id");
}

int JSON::task_id()
{
    return getInt("task_id");
}

int JSON::claimant_id()
{
    return getInt("claimant_id");
}

int JSON::translator_id()
{
    return getInt("translator_id");
}

int JSON::org_id()
{
    return getInt("org_id");
}

int JSON::org_member_id()
{
    return getInt("org_member_id");
}

int JSON::badge_id()
{
    return getInt("badge_id");
}

int JSON::site_admin_id()
{
    return getInt("site_admin_id");
}

int JSON::org_admin_id()
{
    return getInt("org_admin_id");
}

int JSON::file_version()
{
    return getInt("file_version");
}

std::string JSON::class_name()
{
    return getString("class_name");
}

std::string JSON::feedback()
{
    return getString("feedback");
}

std::string JSON::body()
{
    return getString("body");
}

std::string JSON::recipient_email()
{
    return getString("recipient_email");
}
}
