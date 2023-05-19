#include "UserDao.h"

#include <QDebug>
#include "../ModelGenerator.h"
#include "../ConfigParser.h"

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

QString UserDao::get_password_reset_request_uuid(QSharedPointer<MySQLHandler> db, int user_id)
{
    QString ret;
    QSharedPointer<QSqlQuery> mQuery = db->call("get_password_reset_request", QString::number(user_id));
    if(mQuery->first()) {
        QMap<QString, int> fieldMap = MySQLHandler::getFieldMap(mQuery);
        ret = MySQLHandler::getValueFromQuery(fieldMap.value("uuid"), mQuery).toString();
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

QList<QSharedPointer<Task> > UserDao::get_user_earthquake_tasks(QSharedPointer<MySQLHandler> db, int userId)
{
    QList<QSharedPointer<Task> > taskList = QList<QSharedPointer<Task> >();
    QString args = QString::number(userId);

    QSharedPointer<QSqlQuery> mQuery = db->call("get_user_earthquake_tasks", args);
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

QList<int> UserDao::get_users_list_for_earthquake(QSharedPointer<MySQLHandler> db)
{
    QList<int> userIds = QList<int>();
    QSharedPointer<QSqlQuery> mQuery = db->call("get_users_list_for_earthquake", "");
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

void UserDao::log_email_sent(QSharedPointer<MySQLHandler> db, int recipient_id, int task_id, int project_id, int org_id, int translator_id, int admin_id, int badge_id, QString topic)
{
    QString args =
        QString::number(recipient_id) + ", " +
        QString::number(task_id) + ", " +
        QString::number(project_id) + ", " +
        QString::number(org_id) + ", " +
        QString::number(translator_id) + ", " +
        QString::number(admin_id) + ", " +
        QString::number(badge_id) + ", " +
        MySQLHandler::wrapString(topic);
    db->call("log_email_sent", args);
}

void UserDao::queue_email(QSharedPointer<MySQLHandler> db, int recipient_id, QString recipient, QString subject, QString body, int priority /* = 3 */)
{
    ConfigParser settings;
    QString args =
        QString::number(recipient_id) + ", " +
        MySQLHandler::wrapString(settings.get("site.system_email_address")) + ", " +
        MySQLHandler::wrapString(recipient) + ", " +
        MySQLHandler::wrapString(subject) + ", " +
        MySQLHandler::wrapString(body) + ", " +
        QString::number(priority);
    db->call("queue_email", args);
}

QMap<QString, QVariant> UserDao::get_email_request(QSharedPointer<MySQLHandler> db)
{
    QMap<QString, QVariant> row = QMap<QString, QVariant>();

    QSharedPointer<QSqlQuery> mQuery = db->call("get_email_request", "");
    if(mQuery->first()) {
        QMap<QString, int> fieldMap = MySQLHandler::getFieldMap(mQuery);
        row["id"]           = MySQLHandler::getValueFromQuery(fieldMap.value("id"), mQuery);
        row["recipient_id"] = MySQLHandler::getValueFromQuery(fieldMap.value("recipient_id"), mQuery);
        row["sender"]       = MySQLHandler::getValueFromQuery(fieldMap.value("sender"), mQuery);
        row["recipient"]    = MySQLHandler::getValueFromQuery(fieldMap.value("recipient"), mQuery);
        row["subject"]      = MySQLHandler::getValueFromQuery(fieldMap.value("subject"), mQuery);
        row["body"]         = MySQLHandler::getValueFromQuery(fieldMap.value("body"), mQuery);
        row["priority"]     = MySQLHandler::getValueFromQuery(fieldMap.value("priority"), mQuery);
        row["logged_time"]  = MySQLHandler::getValueFromQuery(fieldMap.value("logged_time"), mQuery);
    }
    return row;
}

void UserDao::mark_email_request_sent(QSharedPointer<MySQLHandler> db, unsigned long long id)
{
    db->call("mark_email_request_sent", QString::number(id));
}

void UserDao::insert_queue_request(QSharedPointer<MySQLHandler> db, int queue, int type)
{
    QString args =
        QString::number(queue) + ", " +
        QString::number(type) + ", " +
        "0, " +
        "0, " +
        "0, " +
        "0, " +
        "0, " +
        "0, " +
        MySQLHandler::wrapString("");
    db->call("insert_queue_request", args);
}

QMap<QString, QVariant> UserDao::get_queue_request(QSharedPointer<MySQLHandler> db, int queue)
{
    QMap<QString, QVariant> row = QMap<QString, QVariant>();

    QSharedPointer<QSqlQuery> mQuery = db->call("get_queue_request", QString::number(queue));
    if(mQuery->first()) {
        QMap<QString, int> fieldMap = MySQLHandler::getFieldMap(mQuery);
        row["id"]              = MySQLHandler::getValueFromQuery(fieldMap.value("id"), mQuery);
        row["queue"]           = MySQLHandler::getValueFromQuery(fieldMap.value("queue"), mQuery);
        row["type"]            = MySQLHandler::getValueFromQuery(fieldMap.value("type"), mQuery);
        row["user_id"]         = MySQLHandler::getValueFromQuery(fieldMap.value("user_id"), mQuery);
        row["badge_id"]        = MySQLHandler::getValueFromQuery(fieldMap.value("badge_id"), mQuery);
        row["org_id"]          = MySQLHandler::getValueFromQuery(fieldMap.value("org_id"), mQuery);
        row["project_id"]      = MySQLHandler::getValueFromQuery(fieldMap.value("project_id"), mQuery);
        row["task_id"]         = MySQLHandler::getValueFromQuery(fieldMap.value("task_id"), mQuery);
        row["claimant_id"]     = MySQLHandler::getValueFromQuery(fieldMap.value("claimant_id"), mQuery);
        row["feedback"]        = MySQLHandler::getValueFromQuery(fieldMap.value("feedback"), mQuery);
        row["request_handled"] = MySQLHandler::getValueFromQuery(fieldMap.value("request_handled"), mQuery);
        row["logged_time"]     = MySQLHandler::getValueFromQuery(fieldMap.value("logged_time"), mQuery);
    }
    return row;
}

void UserDao::mark_queue_request_handled(QSharedPointer<MySQLHandler> db, unsigned long long id)
{
    db->call("mark_queue_request_handled", QString::number(id));
}

void UserDao::update_statistics(QSharedPointer<MySQLHandler> db)
{
    db->call("statsUpdateAll", "");
}

void UserDao::insert_qxt_smtp_email(QSharedPointer<MySQLHandler> db, unsigned long long email_request_id, int qxt_smtp_mail_id)
{
    ConfigParser settings;
    QString args =
        QString::number(email_request_id) + ", " +
        QString::number(qxt_smtp_mail_id);
    db->call("insert_qxt_smtp_email", args);
}

void UserDao::update_qxt_smtp_email(QSharedPointer<MySQLHandler> db, unsigned long long email_request_id, int qxt_smtp_mail_id, int success, int error_code)
{
    QString args =
        QString::number(qxt_smtp_mail_id) + ", " +
        QString::number(success) + ", " +
        QString::number(error_code);
    db->call("update_qxt_smtp_email", args);
}
