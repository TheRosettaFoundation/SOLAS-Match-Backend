#include "TaskDao.h"

#include "../ModelGenerator.h"
#include "UserDao.h"

QList<QSharedPointer<Task> > TaskDao::getTasks(QSharedPointer<MySQLHandler> db, int id, int projectId, QString title,
                             int wc, QString sourceLang, QString targetLangId, QString createdTime,
                             QString sourceCountry, QString targetCountry, QString comment,
                             int type, int status, int published, QString deadlineTime)
{
    QList<QSharedPointer<Task> > ret = QList<QSharedPointer<Task> >();
    QString args = "";

    if(id != -1) {
        args += QString::number(id) + ", ";
    } else {
        args += "null, ";
    }

    if(projectId != -1) {
        args += QString::number(projectId) + ", ";
    } else {
        args += "null, ";
    }

    if(title != "") {
        args += MySQLHandler::wrapString(title) + ", ";
    } else {
        args += "null, ";
    }

    if(wc != -1) {
        args += QString::number(wc) + ", ";
    } else {
        args += "null, ";
    }

    if(sourceLang != "") {
        args += MySQLHandler::wrapString(sourceLang) + ", ";
    } else {
        args += "null, ";
    }

    if(targetLangId != "") {
        args += MySQLHandler::wrapString(targetLangId) + ", ";
    } else {
        args += "null, ";
    }

    if (createdTime != "") {
        args += MySQLHandler::wrapString(createdTime) + ", ";
    } else {
        args += "null, ";
    }

    if(sourceCountry != "") {
        args += MySQLHandler::wrapString(sourceCountry) + ", ";
    } else {
        args += "null, ";
    }

    if(targetCountry != "") {
        args += MySQLHandler::wrapString(targetCountry) + ", ";
    } else {
        args += "null, ";
    }

    if (comment != "") {
        args += comment + ", ";
    } else {
        args += "null, ";
    }

    if(type != -1) {
        args += QString::number(type) + ", ";
    } else {
        args += "null, ";
    }

    if (status != -1) {
        args += QString::number(status) + ", ";
    } else {
        args += "null, ";
    }

    if (published != -1) {
        args += QString::number(published) + ", ";
    } else {
        args += "null, ";
    }

    if(deadlineTime != "") {
        args += MySQLHandler::wrapString(deadlineTime);
    } else {
        args += "null";
    }

    QSharedPointer<QSqlQuery> mQuery = db->call("getTask", args);
    if(mQuery->first()) {
        QMap<QString, int> fieldMap = MySQLHandler::getFieldMap(mQuery);
        do {
            QSharedPointer<Task> task = QSharedPointer<Task>(new Task());
            ModelGenerator::Generate(mQuery, task, fieldMap);
            ret.append(task);
        } while(mQuery->next());
    }

    return ret;
}

QSharedPointer<Task> TaskDao::getTask(QSharedPointer<MySQLHandler> db, int id, int projectId, QString title,
                                      int wc, QString sourceLang, QString targetLangId, QString createdTime,
                                      QString sourceCountry, QString targetCountry, QString comment,
                                      int type, int status, int published, QString deadlineTime)
{
    QSharedPointer<Task> task;
    QList<QSharedPointer<Task> > task_list = TaskDao::getTasks(db, id, projectId, title, wc, sourceLang,
                                      targetLangId, createdTime, sourceCountry, targetCountry, comment,
                                      type, status, published, deadlineTime);
    if(task_list.count() > 0) {
        task = task_list.at(0);
    }
    return task;
}

QSharedPointer<Task> TaskDao::insertAndUpdate(QSharedPointer<MySQLHandler> db, Task task)
{
    QString args = "";
    Locale sourceLocale = task.sourcelocale();
    Locale targetLocale = task.targetlocale();

    if (task.id() > 0) {
        args += QString::number(task.id()) + ", ";
    } else {
        args += "null, ";
    }

    if (task.projectid() > 0) {
        args += QString::number(task.projectid()) + ", ";
    } else {
        args += "null, ";
    }

    if (task.title() != "") {
        args += MySQLHandler::wrapStdString(task.title()) + ", ";
    } else {
        args += "null, ";
    }

    if (task.wordcount() > 0) {
        args += QString::number(task.wordcount()) + ", ";
    } else {
        args += "null, ";
    }

    if (sourceLocale.languagecode() != "") {
        args += MySQLHandler::wrapStdString(sourceLocale.languagecode()) + ", ";
    } else {
        args += "null, ";
    }

    if (targetLocale.languagecode() != "") {
        args += MySQLHandler::wrapStdString(targetLocale.languagecode()) + ", ";
    } else {
        args += "null, ";
    }

    if (task.comment() != "") {
        args += MySQLHandler::wrapStdString(task.comment()) + ", ";
    } else {
        args += "null, ";
    }

    if (sourceLocale.countrycode() != "") {
        args +=  MySQLHandler::wrapStdString(sourceLocale.countrycode()) + ", ";
    } else {
        args += "null, ";
    }

    if (targetLocale.countrycode() != "") {
        args += MySQLHandler::wrapStdString(targetLocale.countrycode()) + ", ";
    } else {
        args += "null, ";
    }

    if (task.deadline() != "") {
        args += MySQLHandler::wrapStdString(task.deadline()) + ", ";
    } else {
        args += "null, ";
    }

    if (task.tasktype() > 0) {
        args += QString::number(task.tasktype()) + ", ";
    } else {
        args += "null, ";
    }

    if (task.taskstatus() > 0) {
        args += QString::number(task.taskstatus()) + ", ";
    } else {
        args += "null, ";
    }

    args += QString::number(task.published());

    QSharedPointer<QSqlQuery> mQuery = db->call("taskInsertAndUpdate", args);
    QSharedPointer<Task> ret = QSharedPointer<Task>();
    if (mQuery->first()) {
        QMap<QString, int> fieldMap = MySQLHandler::getFieldMap(mQuery);
        ret = QSharedPointer<Task>(new Task());
        ModelGenerator::Generate(mQuery, ret, fieldMap);
    }

    return ret;
}

QSharedPointer<Task> TaskDao::insertAndUpdate(QSharedPointer<MySQLHandler> db, QSharedPointer<Task> task)
{
    QString args = "";
    Locale sourceLocale = task->sourcelocale();
    Locale targetLocale = task->targetlocale();

    if (task->id() > 0) {
        args += QString::number(task->id()) + ", ";
    } else {
        args += "null, ";
    }

    if (task->projectid() > 0) {
        args += QString::number(task->projectid()) + ", ";
    } else {
        args += "null, ";
    }

    if (task->title() != "") {
        args += MySQLHandler::wrapStdString(task->title()) + ", ";
    } else {
        args += "null, ";
    }

    if (task->wordcount() > 0) {
        args += QString::number(task->wordcount()) + ", ";
    } else {
        args += "null, ";
    }

    if (sourceLocale.languagecode() != "") {
        args += MySQLHandler::wrapStdString(sourceLocale.languagecode()) + ", ";
    } else {
        args += "null, ";
    }

    if (targetLocale.languagecode() != "") {
        args += MySQLHandler::wrapStdString(targetLocale.languagecode()) + ", ";
    } else {
        args += "null, ";
    }

    if (task->comment() != "") {
        args += MySQLHandler::wrapStdString(task->comment()) + ", ";
    } else {
        args += "null, ";
    }

    if (sourceLocale.countrycode() != "") {
        args +=  MySQLHandler::wrapStdString(sourceLocale.countrycode()) + ", ";
    } else {
        args += "null, ";
    }

    if (targetLocale.countrycode() != "") {
        args += MySQLHandler::wrapStdString(targetLocale.countrycode()) + ", ";
    } else {
        args += "null, ";
    }

    if (task->deadline() != "") {
        args += MySQLHandler::wrapStdString(task->deadline()) + ", ";
    } else {
        args += "null, ";
    }

    if (task->tasktype() > 0) {
        args += QString::number(task->tasktype()) + ", ";
    } else {
        args += "null, ";
    }

    if (task->taskstatus() > 0) {
        args += QString::number(task->taskstatus()) + ", ";
    } else {
        args += "null, ";
    }

    args += QString::number(task->published());

    QSharedPointer<QSqlQuery> mQuery = db->call("taskInsertAndUpdate", args);
    if (mQuery->first()) {
        QMap<QString, int> fieldMap = MySQLHandler::getFieldMap(mQuery);
        task = QSharedPointer<Task>(new Task());
        ModelGenerator::Generate(mQuery, task, fieldMap);
    }

    return task;
}

QList<QSharedPointer<Task> > TaskDao::getActiveTasks(QSharedPointer<MySQLHandler> db, int limit, int offset)
{
    QList<QSharedPointer<Task> > ret = QList<QSharedPointer<Task> >();
    QString args = "";
    if(limit > 0) {
        args += QString::number(limit) + ", ";
    } else {
        args += "null, ";
    }

    if (offset > 0) {
        args += QString::number(offset);
    } else {
        args += "null";
    }

    QSharedPointer<QSqlQuery> mQuery = db->call("getLatestAvailableTasks", args);
    if(mQuery->first()) {
        QMap<QString, int> fieldMap = MySQLHandler::getFieldMap(mQuery);
        do {
            QSharedPointer<Task> task = QSharedPointer<Task>(new Task());
            ModelGenerator::Generate(mQuery, task, fieldMap);
            ret.append(task);
        } while(mQuery->next());
    }

    return ret;
}

QList<QSharedPointer<Task> > TaskDao::getOverdueTasks(QSharedPointer<MySQLHandler> db)
{
    QList<QSharedPointer<Task> > ret = QList<QSharedPointer<Task> >();

    QSharedPointer<QSqlQuery> mQuery = db->call("getOverdueTasks", "");
    if (mQuery->first()) {
        QMap<QString, int> fieldMap = MySQLHandler::getFieldMap(mQuery);
        do {
            QSharedPointer<Task> task = QSharedPointer<Task>(new Task());
            ModelGenerator::Generate(mQuery, task, fieldMap);
            ret.append(task);
        } while (mQuery->next());
    }

    return ret;
}

QList<QSharedPointer<Task> > TaskDao::getEarlyWarningTasks(QSharedPointer<MySQLHandler> db)
{
    QList<QSharedPointer<Task> > ret = QList<QSharedPointer<Task> >();

    QSharedPointer<QSqlQuery> mQuery = db->call("getEarlyWarningTasks", "");
    if (mQuery->first()) {
        QMap<QString, int> fieldMap = MySQLHandler::getFieldMap(mQuery);
        do {
            QSharedPointer<Task> task = QSharedPointer<Task>(new Task());
            ModelGenerator::Generate(mQuery, task, fieldMap);
            ret.append(task);
        } while (mQuery->next());
    }

    return ret;
}

QList<QSharedPointer<Task> > TaskDao::getLateWarningTasks(QSharedPointer<MySQLHandler> db)
{
    QList<QSharedPointer<Task> > ret = QList<QSharedPointer<Task> >();

    QSharedPointer<QSqlQuery> mQuery = db->call("getLateWarningTasks", "");
    if (mQuery->first()) {
        QMap<QString, int> fieldMap = MySQLHandler::getFieldMap(mQuery);
        do {
            QSharedPointer<Task> task = QSharedPointer<Task>(new Task());
            ModelGenerator::Generate(mQuery, task, fieldMap);
            ret.append(task);
        } while (mQuery->next());
    }

    return ret;
}

void TaskDao::taskNotificationSentInsertAndUpdate(QSharedPointer<MySQLHandler> db, int task_id, int notification)
{
    QString args = "";
    args += QString::number(task_id) + ", ";
    args += QString::number(notification);

    db->call("taskNotificationSentInsertAndUpdate", args);
}

QSharedPointer<User> TaskDao::getUserClaimedTask(QSharedPointer<MySQLHandler> db, int task_id)
{
    QSharedPointer<User> user;
    QSharedPointer<QSqlQuery> mQuery = db->call("getUserClaimedTask", QString::number(task_id));
    if(mQuery->first()) {
        QMap<QString, int> fieldMap = MySQLHandler::getFieldMap(mQuery);
        user = QSharedPointer<User>(new User());
        ModelGenerator::Generate(mQuery, user, fieldMap);
    }
    return user;
}

QList<QSharedPointer<User> > TaskDao::getSubscribedUsers(QSharedPointer<MySQLHandler> db, int task_id)
{
    QList<QSharedPointer<User> > users = QList<QSharedPointer<User> >();

    QSharedPointer<QSqlQuery> mQuery = db->call("getSubscribedUsers", QString::number(task_id));
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

QList<QSharedPointer<ArchivedTask> > TaskDao::getArchivedTasks(QSharedPointer<MySQLHandler> db, int arc_id)
{
    QList<QSharedPointer<ArchivedTask> > ret = QList<QSharedPointer<ArchivedTask> >();
    QString args = "";

    if(arc_id != -1) {
        args += QString::number(arc_id) + ", ";
    } else {
        args += "null, ";
    }
    args += "null, null, null, null, null, null, null, null, null, null, null, null, null";

    QSharedPointer<QSqlQuery> mQuery = db->call("getArchivedTask", args);
    if(mQuery->first()) {
        QMap<QString, int> fieldMap = MySQLHandler::getFieldMap(mQuery);
        do {
            QSharedPointer<ArchivedTask> task = QSharedPointer<ArchivedTask>(new ArchivedTask());
            ModelGenerator::Generate(mQuery, task, fieldMap);
            ret.append(task);
        } while(mQuery->next());
    }

    return ret;
}

QSharedPointer<ArchivedTask> TaskDao::getArchivedTask(QSharedPointer<MySQLHandler> db, int arc_id)
{
    QSharedPointer<ArchivedTask> task = QSharedPointer<ArchivedTask>();
    QList<QSharedPointer<ArchivedTask> > arc_tasks = TaskDao::getArchivedTasks(db, arc_id);
    if(arc_tasks.count() > 0) {
        task = arc_tasks.at(0);
    }
    return task;
}

QList<QSharedPointer<Task> > TaskDao::getTaskPreReqs(QSharedPointer<MySQLHandler> db, int taskId)
{
    QList<QSharedPointer<Task> > tasks = QList<QSharedPointer<Task> >();
    QSharedPointer<QSqlQuery> mQuery = db->call("getTaskPreReqs", QString::number(taskId));
    if (mQuery->first()) {
        QMap<QString, int> fieldMap = MySQLHandler::getFieldMap(mQuery);
        do {
            QSharedPointer<Task> task = QSharedPointer<Task>(new Task());
            ModelGenerator::Generate(mQuery, task, fieldMap);
            tasks.append(task);
        } while (mQuery->next());
    }
    return tasks;
}

QMultiMap<int, int> TaskDao::getTaskTagIds(QSharedPointer<MySQLHandler> db, int limit, int offset)
{
    QMultiMap<int, int> taskTagIds;
    QString args = QString::number(limit) + ", " + QString::number(offset);
    QSharedPointer<QSqlQuery> mQuery = db->call("getTaskTagIds", args);
    if(mQuery->first()) {
        QMap<QString, int> fieldMap = MySQLHandler::getFieldMap(mQuery);
        do {
            taskTagIds.insert(MySQLHandler::getValueFromQuery(fieldMap.value("task_id"), mQuery).toInt(),
                              MySQLHandler::getValueFromQuery(fieldMap.value("tag_id"), mQuery).toInt());
        } while (mQuery->next());
    }
    return taskTagIds;
}

std::string TaskDao::get_matecat_url(QSharedPointer<MySQLHandler> db, QSharedPointer<Task> task)
{
    QString matecat_url("");

    if (task->tasktype() == TRANSLATION || task->tasktype() == PROOFREADING) {
        QString translate_url("https://tm.translatorswb.org/translate/proj-");
        if (task->tasktype() == PROOFREADING) translate_url = "https://tm.translatorswb.org/revise/proj-";

        QSharedPointer<QSqlQuery> mQuery = db->call("getMatecatLanguagePairs", QString::number(task->id()));
        if (mQuery->first()) {
            QMap<QString, int> fieldMap = MySQLHandler::getFieldMap(mQuery);

            QString matecat_langpair       (MySQLHandler::getValueFromQuery(fieldMap.value("matecat_langpair"), mQuery).toString());
            QString matecat_id_job         (MySQLHandler::getValueFromQuery(fieldMap.value("matecat_id_job"), mQuery).toString());
            QString matecat_id_job_password(MySQLHandler::getValueFromQuery(fieldMap.value("matecat_id_job_password"), mQuery).toString());

            if (matecat_langpair != "" && matecat_id_job != "" && matecat_id_job_password != "") {
                matecat_url = translate_url + QString::number(task->projectid()) + "/" + matecat_langpair.replace("|", "-") + "/" + matecat_id_job + "-" + matecat_id_job_password;
            }
        } else {
            mQuery = db->call("getTaskChunk", QString::number(task->id()));
            if (mQuery->first()) {
                QMap<QString, int> fieldMap = MySQLHandler::getFieldMap(mQuery);

                QString matecat_langpair       (MySQLHandler::getValueFromQuery(fieldMap.value("matecat_langpair"), mQuery).toString());
                QString matecat_id_job         (MySQLHandler::getValueFromQuery(fieldMap.value("matecat_id_job"), mQuery).toString());
                QString matecat_id_job_password(MySQLHandler::getValueFromQuery(fieldMap.value("matecat_id_chunk_password"), mQuery).toString());

                if (matecat_langpair != "" && matecat_id_job != "" && matecat_id_job_password != "") {
                    matecat_url = translate_url + QString::number(task->projectid()) + "/" + matecat_langpair.replace("|", "-") + "/" + matecat_id_job + "-" + matecat_id_job_password;
                }
            }
        }
    }
    return matecat_url.toStdString();
}

std::string TaskDao::getMatecatRevisionURL(QSharedPointer<MySQLHandler> db, QSharedPointer<Task> task)
{
    QString matecat_url("");
    QString translate_url("https://tm.translatorswb.org/revise/proj-");

    mQuery = db->call("getTaskChunk", QString::number(task->id()));
    if (mQuery->first()) {
        QMap<QString, int> fieldMap = MySQLHandler::getFieldMap(mQuery);

        QString matecat_langpair       (MySQLHandler::getValueFromQuery(fieldMap.value("matecat_langpair"), mQuery).toString());
        QString matecat_id_job         (MySQLHandler::getValueFromQuery(fieldMap.value("matecat_id_job"), mQuery).toString());
        QString matecat_id_job_password(MySQLHandler::getValueFromQuery(fieldMap.value("matecat_id_chunk_password"), mQuery).toString());

        if (matecat_langpair != "" && matecat_id_job != "" && matecat_id_job_password != "") {
            matecat_url = translate_url + QString::number(task->projectid()) + "/" + matecat_langpair.replace("|", "-") + "/" + matecat_id_job + "-" + matecat_id_job_password;
        }
    }

    return matecat_url.toStdString();
}

bool TaskDao::is_task_translated_in_matecat(QSharedPointer<MySQLHandler> db, int taskId)
{
    if (TaskDao::is_chunked_task(db, taskId)) return true;

    QSharedPointer<QSqlQuery> mQuery = db->call("is_task_translated_in_matecat", QString::number(taskId));
    if (mQuery->first()) {
        return true;
    }
    return false;
}

bool TaskDao::is_chunked_task(QSharedPointer<MySQLHandler> db, int taskId)
{
    QSharedPointer<QSqlQuery> mQuery = db->call("getTaskChunk", QString::number(taskId));
    if (mQuery->first()) {
        return true;
    }
    return false;
}
