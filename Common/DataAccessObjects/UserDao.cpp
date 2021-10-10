#include "UserDao.h"

#include <QDebug>
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
        QMap<QString, int> fieldMap = MySQLHandler::getFieldMap(mQuery);
        do {
            QSharedPointer<User> user = QSharedPointer<User>(new User());
            ModelGenerator::Generate(mQuery, user, fieldMap);
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
        QMap<QString, int> fieldMap = MySQLHandler::getFieldMap(mQuery);
        data = QSharedPointer<BannedUser>(new BannedUser());
        ModelGenerator::Generate(mQuery, data, fieldMap);
    }
    return data;
}

QString UserDao::getPasswordResetUuid(QSharedPointer<MySQLHandler> db, QString email)
{
    QString ret;
    QString args = "null, " + MySQLHandler::wrapString(email);
    QSharedPointer<QSqlQuery> mQuery = db->call("getPasswordResetRequests", args);
    if(mQuery->first()) {
        QMap<QString, int> fieldMap = MySQLHandler::getFieldMap(mQuery);
        ret = MySQLHandler::getValueFromQuery(fieldMap.value("key"), mQuery).toString();
    }

    return ret;
}

QString UserDao::getRegistrationId(QSharedPointer<MySQLHandler> db, int userId)
{
    QString ret = "";
    QString args = QString::number(userId);
    QSharedPointer<QSqlQuery> mQuery = db->call("getRegistrationId", args);
    if (mQuery->first()) {
        QMap<QString, int> fieldMap = MySQLHandler::getFieldMap(mQuery);
        ret = MySQLHandler::getValueFromQuery(fieldMap.value("unique_id"), mQuery).toString();
    }

    return ret;
}

QList<QSharedPointer<Task> > UserDao::getUserTopTasks(QSharedPointer<MySQLHandler> db, int userId, bool strict, int limit,
                                                      int offset, int taskTypeId, QString sourceLanguageCode, QString targetLanguageCode)
{
    QList<QSharedPointer<Task> > taskList = QList<QSharedPointer<Task> >();
    QString args = QString::number(userId) + ", ";
    if (strict) {
        args += "1, ";
    } else {
        args += "0, ";
    }
    args += QString::number(limit) + ", ";
    args += QString::number(offset) + ", ";

    if (taskTypeId > 0) {
        args += QString::number(taskTypeId) + ",";
    } else {
        args += "null, ";
    }

    if (sourceLanguageCode != "") {
        args += MySQLHandler::wrapString(sourceLanguageCode) + ", ";
    } else {
        args += "null, ";
    }

    if (targetLanguageCode != "") {
        args += MySQLHandler::wrapString(targetLanguageCode);
    } else {
        args += "null";
    }

    QSharedPointer<QSqlQuery> mQuery = db->call("getUserTopTasks", args);
    if (mQuery->first()) {
        QMap<QString, int> fieldMap = MySQLHandler::getFieldMap(mQuery);
        do {
            QSharedPointer<Task> task = QSharedPointer<Task>(new Task());
            ModelGenerator::Generate(mQuery, task, fieldMap);
            taskList.append(task);
        } while (mQuery->next());
    }
    return taskList;
}

QList<QSharedPointer<Task> > UserDao::getUserTasks(QSharedPointer<MySQLHandler> db, int userId, int limit, int offset)
{
    QList<QSharedPointer<Task> > taskList = QList<QSharedPointer<Task> >();
    QString args = QString::number(userId) + ", ";
    if (limit > 0) {
        args += QString::number(limit) + ", ";
    } else {
        args += "null, ";
    }
    args += QString::number(offset);
    QSharedPointer<QSqlQuery> mQuery = db->call("getUserTasks", args);
    if (mQuery->first()) {
        QMap<QString, int> fieldMap = MySQLHandler::getFieldMap(mQuery);
        do {
            QSharedPointer<Task> task = QSharedPointer<Task>(new Task());
            ModelGenerator::Generate(mQuery, task, fieldMap);
            taskList.append(task);
        } while (mQuery->next());
    }
    return taskList;
}

QList<QSharedPointer<ArchivedTask> > UserDao::getUserArchivedTasks(QSharedPointer<MySQLHandler> db, int userId, int limit)
{
    QList<QSharedPointer<ArchivedTask> > taskList = QList<QSharedPointer<ArchivedTask> >();
    QString args = QString::number(userId) + ", ";
    if (limit > 0) {
        args += QString::number(limit);
    } else {
        args += "null,";
    }
    args += "null"; //for offset
    QSharedPointer<QSqlQuery> mQuery = db->call("getUserArchivedTasks", args);
    if (mQuery->first()) {
        QMap<QString, int> fieldMap = MySQLHandler::getFieldMap(mQuery);
        do {
            QSharedPointer<ArchivedTask> task = QSharedPointer<ArchivedTask>(new ArchivedTask());
            ModelGenerator::Generate(mQuery, task, fieldMap);
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

QSharedPointer<UserTaskStreamNotification> UserDao::getUserTaskStreamNotification(QSharedPointer<MySQLHandler> db,
                                                                                  int userId)
{
    QSharedPointer<UserTaskStreamNotification> data = QSharedPointer<UserTaskStreamNotification>();
    QSharedPointer<QSqlQuery> mQuery = db->call("getUserTaskStreamNotification", QString::number(userId));
    if (mQuery->first()) {
        QMap<QString, int> fieldMap = MySQLHandler::getFieldMap(mQuery);
        data = QSharedPointer<UserTaskStreamNotification>(new UserTaskStreamNotification());
        ModelGenerator::Generate(mQuery, data, fieldMap);
    }
    return data;
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

QList<QSharedPointer<Locale> > UserDao::getUserSecondaryLanguages(QSharedPointer<MySQLHandler> db, int userId)
{
    QList<QSharedPointer<Locale> > userSecondaryLocales;

    QString args = QString::number(userId);
    QSharedPointer<QSqlQuery> mQuery = db->call("getUserSecondaryLanguages", args);
    if(mQuery->first()) {
        QMap<QString, int> fieldMap = MySQLHandler::getFieldMap(mQuery);
        do {
            QSharedPointer<Locale> locale = QSharedPointer<Locale>(new Locale());
            ModelGenerator::Generate(mQuery, locale, fieldMap);
            userSecondaryLocales.append(locale);
        } while (mQuery->next());
    }
    return userSecondaryLocales;
}



QMultiMap<int, LCCode> UserDao::getUserLCCodes(QSharedPointer<MySQLHandler> db, int limit, int offset)
{
    QMultiMap<int, LCCode> userLCIDs;
    QString args = QString::number(limit) + ", " + QString::number(offset);
    QSharedPointer<QSqlQuery> mQuery = db->call("getUserLCCodes", args);
    if(mQuery->first()) {
        QMap<QString, int> fieldMap = MySQLHandler::getFieldMap(mQuery);
        do {
            LCCode languageCountryId(MySQLHandler::getValueFromQuery(fieldMap.value("languageCode"),
                                                                     mQuery).toString().toStdString(),
                                     MySQLHandler::getValueFromQuery(fieldMap.value("countryCode"),
                                                                     mQuery).toString().toStdString());
            userLCIDs.insert(MySQLHandler::getValueFromQuery(fieldMap.value("user_id"), mQuery).toInt(), languageCountryId);
        } while (mQuery->next());
    }
    return userLCIDs;
}

QMultiMap<int, int> UserDao::getUserTagIds(QSharedPointer<MySQLHandler> db, int limit, int offset)
{
    QMultiMap<int, int> userTagIds;
    QString args = QString::number(limit) + ", " + QString::number(offset);
    QSharedPointer<QSqlQuery> mQuery = db->call("getUserTagIds", args);
    if(mQuery->first()) {
        QMap<QString, int> fieldMap = MySQLHandler::getFieldMap(mQuery);
        do {
            userTagIds.insert(MySQLHandler::getValueFromQuery(fieldMap.value("user_id"), mQuery).toInt(),
                              MySQLHandler::getValueFromQuery(fieldMap.value("tag_id"), mQuery).toInt());
        } while (mQuery->next());
    }
    return userTagIds;
}

QMultiMap<int, LCCode> UserDao::getUserNativeLCCodes(QSharedPointer<MySQLHandler> db, int limit, int offset)
{
    QMultiMap<int, LCCode> userNativeLCIDs;
    QString args = QString::number(limit) + ", " + QString::number(offset);
    QSharedPointer<QSqlQuery> mQuery = db->call("getUserNativeLCCodes", args);
    if(mQuery->first()) {
        QMap<QString, int> fieldMap = MySQLHandler::getFieldMap(mQuery);
        do {
            LCCode languageCountryId(MySQLHandler::getValueFromQuery(fieldMap.value("languageCode"),
                                                                     mQuery).toString().toStdString(),
                                     MySQLHandler::getValueFromQuery(fieldMap.value("countryCode"),
                                                                     mQuery).toString().toStdString());
            userNativeLCIDs.insert(MySQLHandler::getValueFromQuery(fieldMap.value("id"), mQuery).toInt(), languageCountryId);
        } while (mQuery->next());
    }
    return userNativeLCIDs;
}

QString UserDao::getUserRealName(QSharedPointer<MySQLHandler> db, int userId)
{
    QString name = "";
    QString args = QString::number(userId);
    QSharedPointer<QSqlQuery> q = db->call("getUserRealName", args);
    if (q->first()) {
        name = MySQLHandler::getValueFromQuery("real_name", q).toString();
    }
    return name;
}

QList<QSharedPointer<User> > UserDao::getRecordWarningUsers(QSharedPointer<MySQLHandler> db)
{
    QList<QSharedPointer<User> > users = QList<QSharedPointer<User> >();

    QSharedPointer<QSqlQuery> mQuery = db->call("getRecordWarningUsers", "");
    if (mQuery->first()) {
        QMap<QString, int> fieldMap = MySQLHandler::getFieldMap(mQuery);
        do {
            QSharedPointer<User> user = QSharedPointer<User>(new User());
            ModelGenerator::Generate(mQuery, user, fieldMap);
            users.append(user);
        } while (mQuery->next());
    }
    return users;
}

void UserDao::insertWillBeDeletedUser(QSharedPointer<MySQLHandler> db, int user_id)
{
    db->call("insertWillBeDeletedUser", QString::number(user_id));
}
