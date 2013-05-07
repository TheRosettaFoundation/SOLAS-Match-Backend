#include "UserDao.h"

#include "../ModelGenerator.h"

QList<QSharedPointer<User> > UserDao::getUsers(QSharedPointer<MySQLHandler> db, int id, QString name, QString email, QString pass,
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
        args += MySQLHandler::wrapString(name) + ", ";
    } else {
        args += "null, ";
    }

    if(email != "") {
        args += MySQLHandler::wrapString(email) + ", ";
    } else {
        args += "null, ";
    }

    if(pass != "") {
        args += MySQLHandler::wrapString(pass) + ", ";
    } else {
        args += "null, ";
    }

    if(bio != "") {
        args += MySQLHandler::wrapString(bio) + ", ";
    } else {
        args += "null, ";
    }

    if(non != "") {
        args += MySQLHandler::wrapString(non) + ", ";
    } else {
        args += "null, ";
    }

    if(date != "") {
        args += MySQLHandler::wrapString(date) + ", ";
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

QSharedPointer<User> UserDao::getUser(QSharedPointer<MySQLHandler> db, int id, QString name,
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

QSharedPointer<BannedUser> UserDao::getBanData(QSharedPointer<MySQLHandler> db, int userId)
{
    QSharedPointer<BannedUser> data = QSharedPointer<BannedUser>();
    QString args = QString::number(userId);
    args += ", null, null, null, null";
    QSharedPointer<QSqlQuery> mQuery = db->call("getBannedUser", args);
    if (mQuery->first()) {
        data = ModelGenerator::GenerateBannedUser(mQuery);
    }
    return data;
}

QString UserDao::getPasswordResetUuid(QSharedPointer<MySQLHandler> db, int id)
{
    QString ret;
    QString args = "null, " + QString::number(id);
    QSharedPointer<QSqlQuery> mQuery = db->call("getPasswordResetRequests", args);
    if(mQuery->first()) {
        ret = MySQLHandler::getValueFromQuery("uid", mQuery).toString();
    }

    return ret;
}

QString UserDao::getRegistrationId(QSharedPointer<MySQLHandler> db, int userId)
{
    QString ret = "";
    QString args = QString::number(userId);
    QSharedPointer<QSqlQuery> mQuery = db->call("getRegistrationId", args);
    if (mQuery->first()) {
        ret = MySQLHandler::getValueFromQuery("unique_id", mQuery).toString();
    }

    return ret;
}

QList<QSharedPointer<Task> > UserDao::getUserTopTasks(QSharedPointer<MySQLHandler> db, int userId, int limit, QString filter)
{
    QList<QSharedPointer<Task> > taskList = QList<QSharedPointer<Task> >();
    QString args = QString::number(userId) + ", ";
    args = args + QString::number(limit) + ", ";
    args += MySQLHandler::wrapString(filter);
    QSharedPointer<QSqlQuery> mQuery = db->call("getUserTopTasks", args);
    if (mQuery->first()) {
        do {
            QSharedPointer<Task> task = ModelGenerator::GenerateTask(mQuery);
            taskList.append(task);
        } while (mQuery->next());
    }
    return taskList;
}

QList<int> UserDao::getUserIdsPendingTaskStreamNotification(QSharedPointer<MySQLHandler> db)
{
    QList<int> userIds = QList<int>();
    QSharedPointer<QSqlQuery> mQuery = db->call("getUserIdsPendingTaskStreamNotification", "");
    if (mQuery->first()) {
        do {
            userIds.append(MySQLHandler::getValueFromQuery("user_id", mQuery).toInt());
        } while (mQuery->next());
    }
    return userIds;
}

bool UserDao::taskStreamNotificationSent(QSharedPointer<MySQLHandler> db, int userId, QString sentDate)
{
    bool ret = false;
    QString args = QString::number(userId) + ", " + MySQLHandler::wrapString(sentDate);
    QSharedPointer<QSqlQuery> mQuery = db->call("taskStreamNotificationSent", args);
    if (mQuery->first()) {
        ret = (MySQLHandler::getValueFromQuery("result", mQuery).toInt() == 1);
    }
    return ret;
}
