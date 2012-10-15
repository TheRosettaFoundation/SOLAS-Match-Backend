#include "User.h"

#include <QDebug>

User::User()
{
}

User::User(QSqlQuery *q)
{
    this->setUserId(MySQLHandler::getValueFromQuery("user_id", q).toInt());
    this->setBiography(MySQLHandler::getValueFromQuery("biography", q).toString());
    this->setCreatedTime(MySQLHandler::getValueFromQuery("created_time", q).toString());
    this->setDisplayName(MySQLHandler::getValueFromQuery("display_name", q).toString());
    this->setEmail(MySQLHandler::getValueFromQuery("email", q).toString());
    this->setNativeLangId(MySQLHandler::getValueFromQuery("native_lang_id", q).toInt());
    this->setNonce(MySQLHandler::getValueFromQuery("nonce", q).toString());
    this->setPassword(MySQLHandler::getValueFromQuery("password", q).toString());
    this->setRegionId(MySQLHandler::getValueFromQuery("native_region_id", q).toInt());
}

QList<User> *User::getUsers(MySQLHandler *db, int id, QString name, QString email, QString pass,
                            QString bio, QString non, QString date, int lang_id, int reg_id)
{
    QList<User> *users = NULL;
    QString args = "";

    if(id != -1) {
        args += QString::number(id) + ", ";
    } else {
        args += "null, ";
    }

    if(name != "") {
        args += name + ", ";
    } else {
        args += "null, ";
    }

    if(email != "") {
        args += email + ", ";
    } else {
        args += "null, ";
    }

    if(pass != "") {
        args += pass + ", ";
    } else {
        args += "null, ";
    }

    if(bio != "") {
        args += bio + ", ";
    } else {
        args += "null, ";
    }

    if(non != "") {
        args += non + ", ";
    } else {
        args += "null, ";
    }

    if(date != "") {
        args += date + ", ";
    } else {
        args += "null, ";
    }

    if(lang_id != -1) {
        args += QString::number(lang_id) + ", ";
    } else {
        args += "null, ";
    }

    if(reg_id != -1) {
        args += QString::number(reg_id);
    } else {
        args += "null";
    }

    QSqlQuery *mQuery = db->call("getUser", args);
    if(mQuery->first()) {
        users = new QList<User>();
        do {
            User user(mQuery);
            users->append(user);
        } while(mQuery->next());
    }

    return users;
}

void User::setUserId(int user_id)
{
    this->id = user_id;
}

void User::setDisplayName(QString name)
{
    this->display_name = name;
}

void User::setEmail(QString email)
{
    this->email = email;
}

void User::setPassword(QString pass)
{
    this->password = pass;
}

void User::setBiography(QString bio)
{
    this->biography = bio;
}

void User::setNonce(QString non)
{
    this->nonce = non;
}

void User::setCreatedTime(QString date)
{
    this->created_time = date;
}

void User::setNativeLangId(int lang_id)
{
    this->native_lang_id = lang_id;
}

void User::setRegionId(int reg_id)
{
    this->native_region_id = reg_id;
}

int User::getUserId()
{
    return id;
}

QString User::getDisplayName()
{
    return this->display_name;
}

QString User::getEmail()
{
    return this->email;
}

QString User::getPassword()
{
    return this->password;
}

QString User::getBiography()
{
    return this->biography;
}

QString User::getNonce()
{
    return this->nonce;
}

QString User::getCreatedTime()
{
    return this->created_time;
}

int User::getNativeLangId()
{
    return this->native_lang_id;
}

int User::getRegionId()
{
    return this->native_region_id;
}
