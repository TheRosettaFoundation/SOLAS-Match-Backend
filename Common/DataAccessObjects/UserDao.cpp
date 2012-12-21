#include "UserDao.h"

#include "../ModelGenerator.h"

QList<QSharedPointer<User> > UserDao::getUsers(MySQLHandler *db, int id, QString name, QString email, QString pass,
                            QString bio, QString non, QString date, int lang_id, int reg_id)
{
    QList<QSharedPointer<User> > users = QList<QSharedPointer<User> >();
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

    QSharedPointer<QSqlQuery> mQuery = db->call("getUser", args);
    if(mQuery->first()) {
        do {
            QSharedPointer<User> user = ModelGenerator::GenerateUser(mQuery);
            users.append(user);
        } while(mQuery->next());
    }

    return users;
}

QSharedPointer<User> UserDao::getUser(MySQLHandler *db, int id, QString name,
                   QString email, QString pass, QString bio,
                   QString non, QString date, int lang_id, int reg_id)
{
    QSharedPointer<User> user = QSharedPointer<User>();
    QList<QSharedPointer<User> > user_list = UserDao::getUsers(db, id, name, email, pass, bio, non, date, lang_id, reg_id);
    if(user_list.count() > 0) {
        user = user_list.at(0);
    }
    return user;
}

QString UserDao::getPasswordResetUuid(MySQLHandler *db, int id)
{
    QString ret;
    QString args = "null, " + QString::number(id);
    QSharedPointer<QSqlQuery> mQuery = db->call("getPasswordResetRequests", args);
    if(mQuery->first()) {
        ret = MySQLHandler::getValueFromQuery("uid", mQuery).toString();
    }

    return ret;
}
