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

std::string TaskDao::get_matecat_url(QSharedPointer<MySQLHandler> db, QSharedPointer<Task> task, QMap<QString, QVariant> memsource_task)
{
    QString matecat_url("");

    if (!memsource_task.isEmpty()) {
        //matecat_url = QString("https://cloud.memsource.com/web/job/") + memsource_task["memsource_task_uid"].toString() + "/translate";
        matecat_url = QString("https://twbplatform.org/simplesaml/saml2/idp/SSOService.php?spentityid=https://eu.phrase.com/idm/saml/hoKMZESrFauJjF1hpLXwwo&RelayState=https://cloud.memsource.com/web/job/") + memsource_task["memsource_task_uid"].toString() + "/translate";
        return matecat_url.toStdString();
    }

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
                QString job_first_segment      (MySQLHandler::getValueFromQuery(fieldMap.value("job_first_segment"), mQuery).toString());

                if (matecat_langpair != "" && matecat_id_job != "" && matecat_id_job_password != "") {
                    matecat_url = translate_url + QString::number(task->projectid()) + "/" + matecat_langpair.replace("|", "-") + "/" + matecat_id_job + "-" + matecat_id_job_password + job_first_segment;
                }
            }
        }
    }
    return matecat_url.toStdString();
}

std::string TaskDao::get_task_url(QSharedPointer<MySQLHandler> db, int task_id)
{
    QString url("");
    QSharedPointer<QSqlQuery> mQuery = db->call("get_task_url", QString::number(task_id));
    if (mQuery->first()) {
        QMap<QString, int> fieldMap = MySQLHandler::getFieldMap(mQuery);
        url = MySQLHandler::getValueFromQuery(fieldMap.value("url"), mQuery).toString();
    }
    return url.toStdString();
}

std::string TaskDao::getMatecatRevisionURL(QSharedPointer<MySQLHandler> db, QSharedPointer<Task> task)
{
    QString matecat_url("");
    QString translate_url("https://tm.translatorswb.org/revise/proj-");

    QSharedPointer<QSqlQuery> mQuery = db->call("getTaskChunk", QString::number(task->id()));
    if (mQuery->first()) {
        QMap<QString, int> fieldMap = MySQLHandler::getFieldMap(mQuery);

        QString matecat_langpair       (MySQLHandler::getValueFromQuery(fieldMap.value("matecat_langpair"), mQuery).toString());
        QString matecat_id_job         (MySQLHandler::getValueFromQuery(fieldMap.value("matecat_id_job"), mQuery).toString());
        QString matecat_id_job_password(MySQLHandler::getValueFromQuery(fieldMap.value("matecat_id_chunk_password"), mQuery).toString());
        QString job_first_segment      (MySQLHandler::getValueFromQuery(fieldMap.value("job_first_segment"), mQuery).toString());

        if (matecat_langpair != "" && matecat_id_job != "" && matecat_id_job_password != "") {
            matecat_url = translate_url + QString::number(task->projectid()) + "/" + matecat_langpair.replace("|", "-") + "/" + matecat_id_job + "-" + matecat_id_job_password + job_first_segment;
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

QSharedPointer<Task> TaskDao::getMatchingTask(QSharedPointer<MySQLHandler> db, int task_id, int type_id)
{
    QSharedPointer<Task> task;

    QSharedPointer<QSqlQuery> mQuery = db->call("getTaskChunk", QString::number(task_id));
    if (mQuery->first()) {
        QMap<QString, int> fieldMap = MySQLHandler::getFieldMap(mQuery);

        int     matecat_id_job         (MySQLHandler::getValueFromQuery(fieldMap.value("matecat_id_job"), mQuery).toInt());
        QString matecat_id_job_password(MySQLHandler::getValueFromQuery(fieldMap.value("matecat_id_chunk_password"), mQuery).toString());

        mQuery = db->call("getMatchingTask", QString::number(matecat_id_job) + "," + MySQLHandler::wrapString(matecat_id_job_password) + "," + QString::number(type_id));
        if(mQuery->first()) {
            QMap<QString, int> fieldMap = MySQLHandler::getFieldMap(mQuery);
                task = QSharedPointer<Task>(new Task());
                ModelGenerator::Generate(mQuery, task, fieldMap);
        }
    }
    return task;
}

QSharedPointer<Task> TaskDao::getParentTask(QSharedPointer<MySQLHandler> db, int task_id, int type_id)
{
    QSharedPointer<Task> task;

    QSharedPointer<QSqlQuery> mQuery = db->call("getTaskChunk", QString::number(task_id));
    if (mQuery->first()) {
        QMap<QString, int> fieldMap = MySQLHandler::getFieldMap(mQuery);

        int project_id    (MySQLHandler::getValueFromQuery(fieldMap.value("project_id"), mQuery).toInt());
        int matecat_id_job(MySQLHandler::getValueFromQuery(fieldMap.value("matecat_id_job"), mQuery).toInt());

        mQuery = db->call("getParentTask", QString::number(project_id) + "," + QString::number(matecat_id_job) + "," + QString::number(type_id));
        if(mQuery->first()) {
            QMap<QString, int> fieldMap = MySQLHandler::getFieldMap(mQuery);
                task = QSharedPointer<Task>(new Task());
                ModelGenerator::Generate(mQuery, task, fieldMap);
        }
    }
    return task;
}

QMap<QString, QVariant> TaskDao::get_memsource_task(QSharedPointer<MySQLHandler> db, int task_id)
{
    QMap<QString, QVariant> row = QMap<QString, QVariant>();

    QSharedPointer<QSqlQuery> mQuery = db->call("get_memsource_task", QString::number(task_id));
    if(mQuery->first()) {
        QMap<QString, int> fieldMap = MySQLHandler::getFieldMap(mQuery);
        row["task_id"]            = MySQLHandler::getValueFromQuery(fieldMap.value("task_id"), mQuery);
        row["memsource_task_id"]  = MySQLHandler::getValueFromQuery(fieldMap.value("memsource_task_id"), mQuery);
        row["memsource_task_uid"] = MySQLHandler::getValueFromQuery(fieldMap.value("memsource_task_uid"), mQuery);
        row["task"]               = MySQLHandler::getValueFromQuery(fieldMap.value("task"), mQuery);
        row["internalId"]         = MySQLHandler::getValueFromQuery(fieldMap.value("internalId"), mQuery);
        row["workflowLevel"]      = MySQLHandler::getValueFromQuery(fieldMap.value("workflowLevel"), mQuery);
        row["beginIndex"]         = MySQLHandler::getValueFromQuery(fieldMap.value("beginIndex"), mQuery);
        row["endIndex"]           = MySQLHandler::getValueFromQuery(fieldMap.value("endIndex"), mQuery);
        row["prerequisite"]       = MySQLHandler::getValueFromQuery(fieldMap.value("prerequisite"), mQuery);
    }
    return row;
}

QList<QMap<QString, QVariant>> TaskDao::get_tasks_for_project(QSharedPointer<MySQLHandler> db, int project_id)
{
    QList<QMap<QString, QVariant>> project_tasks = QList<QMap<QString, QVariant>>();
    QSharedPointer<QSqlQuery> mQuery = db->call("get_tasks_for_project", QString::number(project_id));
    if (mQuery->first()) {
        QMap<QString, int> fieldMap = MySQLHandler::getFieldMap(mQuery);
        do {
            QMap<QString, QVariant> row = QMap<QString, QVariant>();
            row["id"]                 = MySQLHandler::getValueFromQuery(fieldMap.value("id"), mQuery);
            row["project_id"]         = MySQLHandler::getValueFromQuery(fieldMap.value("project_id"), mQuery);
            row["title"]              = MySQLHandler::getValueFromQuery(fieldMap.value("title"), mQuery);
            row["word-count"]         = MySQLHandler::getValueFromQuery(fieldMap.value("word-count"), mQuery);
            row["language_id-source"] = MySQLHandler::getValueFromQuery(fieldMap.value("language_id-source"), mQuery);
            row["language_id-target"] = MySQLHandler::getValueFromQuery(fieldMap.value("language_id-target"), mQuery);
            row["country_id-source"]  = MySQLHandler::getValueFromQuery(fieldMap.value("country_id-source"), mQuery);
            row["country_id-target"]  = MySQLHandler::getValueFromQuery(fieldMap.value("country_id-target"), mQuery);
            row["created-time"]       = MySQLHandler::getValueFromQuery(fieldMap.value("created-time"), mQuery);
            row["deadline"]           = MySQLHandler::getValueFromQuery(fieldMap.value("deadline"), mQuery);
            row["comment"]            = MySQLHandler::getValueFromQuery(fieldMap.value("comment"), mQuery);
            row["task-type_id"]       = MySQLHandler::getValueFromQuery(fieldMap.value("task-type_id"), mQuery);
            row["task-status_id"]     = MySQLHandler::getValueFromQuery(fieldMap.value("task-status_id"), mQuery);
            row["published"]          = MySQLHandler::getValueFromQuery(fieldMap.value("published"), mQuery);
            row["task_id"]            = MySQLHandler::getValueFromQuery(fieldMap.value("task_id"), mQuery);
            row["memsource_task_id"]  = MySQLHandler::getValueFromQuery(fieldMap.value("memsource_task_id"), mQuery);
            row["memsource_task_uid"] = MySQLHandler::getValueFromQuery(fieldMap.value("memsource_task_uid"), mQuery);
            row["task"]               = MySQLHandler::getValueFromQuery(fieldMap.value("task"), mQuery);
            row["internalId"]         = MySQLHandler::getValueFromQuery(fieldMap.value("internalId"), mQuery);
            row["workflowLevel"]      = MySQLHandler::getValueFromQuery(fieldMap.value("workflowLevel"), mQuery);
            row["beginIndex"]         = MySQLHandler::getValueFromQuery(fieldMap.value("beginIndex"), mQuery);
            row["endIndex"]           = MySQLHandler::getValueFromQuery(fieldMap.value("endIndex"), mQuery);
            row["prerequisite"]       = MySQLHandler::getValueFromQuery(fieldMap.value("prerequisite"), mQuery);
            project_tasks.append(row);
        } while (mQuery->next());
    }
    return project_tasks;
}

bool TaskDao::is_task_translated_in_memsource(QSharedPointer<MySQLHandler> db, QSharedPointer<Task> task)
{
    QMap<QString, QVariant> memsource_task = get_memsource_task(db, task->id());
    if (memsource_task.isEmpty()) return true;

    int top_level = get_top_level(memsource_task["internalId"].toString());

    QList<QMap<QString, QVariant>> project_tasks = get_tasks_for_project(db, task->projectid());
    bool translated = true;

    for (int i = 0; i < project_tasks.size(); i++) {
        QMap<QString, QVariant> project_task = project_tasks[i];
        if (top_level == get_top_level(project_task["internalId"].toString())) {
           if (memsource_task["workflowLevel"].toInt() > project_task["workflowLevel"].toInt()) { // Dependent on
                if ((memsource_task["beginIndex"].toInt() <= project_task["endIndex"].toInt()) && (project_task["beginIndex"].toInt() <= memsource_task["endIndex"].toInt())) { // Overlap
                    if (project_task["task-status_id"].toInt() != COMPLETE) translated = false;
                }
            }
        }
    }
    return translated;
}

std::string TaskDao::max_translation_deadline(QSharedPointer<MySQLHandler> db, QSharedPointer<Task> task)
{
    std::string max_translation_deadline = "0000-00-00 00:00:00";
    bool translations_not_all_complete = false;
    if (task->tasktype() == PROOFREADING || task->tasktype() == APPROVAL) {
        QMap<QString, QVariant> memsource_task = get_memsource_task(db, task->id());
        if (!memsource_task.isEmpty()) {
            int top_level = get_top_level(memsource_task["internalId"].toString());
            QList<QMap<QString, QVariant>> project_tasks = get_tasks_for_project(db, task->projectid());
            for (int i = 0; i < project_tasks.size(); i++) {
                QMap<QString, QVariant> project_task = project_tasks[i];
                if (top_level == get_top_level(project_task["internalId"].toString())) {
                    if (memsource_task["workflowLevel"].toInt() > project_task["workflowLevel"].toInt()) { // Dependent on
                        if ((memsource_task["beginIndex"].toInt() <= project_task["endIndex"].toInt()) && (project_task["beginIndex"].toInt() <= memsource_task["endIndex"].toInt())) { // Overlap
                            max_translation_deadline = std::max(project_task["deadline"], max_translation_deadline);
                            if (project_task["task-status_id"].toInt() != COMPLETE) $translations_not_all_complete = true;
                        }
                    }
                }
            }
        }
        if (max_translation_deadline != "0000-00-00 00:00:00") {
            std:string prereq = (const std:string[]){"", "", "", "translation", "", "", "revision"}[task->tasktype()];
            if (!translations_not_all_complete) max_translation_deadline = "Previous " + $prereq + " step: <strong>Completed</strong>";
            else                                max_translation_deadline = "Previous " + $prereq + " step due by: <strong>" + (QDateTime::fromString(QString::fromStdString(max_translation_deadline), "yyyy-MM-ddTHH:mm:ss.zzz").toString("d MMMM yyyy - hh:mm")).toStdString() + " UTC</strong>";
        }
    }
    return max_translation_deadline;
}

int TaskDao::get_top_level(QString internal_id)
{
    int pos = internal_id.indexOf('.');
    if (pos == -1) return internal_id.toInt();
    return internal_id.left(pos).toInt();
}

QList<QSharedPointer<Task> > TaskDao::get_matching_revision_memsource_tasks(QSharedPointer<MySQLHandler> db, QSharedPointer<Task> task)
{
    QList<QSharedPointer<Task> > revision_tasks = QList<QSharedPointer<Task> >();

    QMap<QString, QVariant> memsource_task = get_memsource_task(db, task->id());
    if (memsource_task.isEmpty()) return revision_tasks;

    QList<QMap<QString, QVariant>> task_type_details = get_task_type_details(db);
    for (int i = 0; i < task_type_details.size(); i++) {
        QMap<QString, QVariant> task_type_detail = task_type_details[i];
        if (task->tasktype() == task_type_detail["type_enum"].toInt()) {
            if (task_type_detail["shell_task"].toInt()) return revision_tasks;
        }
    }

    int top_level = get_top_level(memsource_task["internalId"].toString());

    QList<QMap<QString, QVariant>> project_tasks = get_tasks_for_project(db, task->projectid());

    for (int i = 0; i < project_tasks.size(); i++) {
        QMap<QString, QVariant> project_task = project_tasks[i];
        if (top_level == get_top_level(project_task["internalId"].toString())) {
           if (memsource_task["workflowLevel"].toInt() < project_task["workflowLevel"].toInt()) { // Limit to revision tasks
                if ((memsource_task["beginIndex"].toInt() <= project_task["endIndex"].toInt()) && (project_task["beginIndex"].toInt() <= memsource_task["endIndex"].toInt())) { // Overlap
                    revision_tasks.append(getTask(db, project_task["task_id"].toInt()));
                }
            }
        }
    }
    return revision_tasks;
}

QList<QMap<QString, QVariant> > TaskDao::get_task_type_details(QSharedPointer<MySQLHandler> db)
{
    QList<QMap<QString, QVariant>> task_type_details = QList<QMap<QString, QVariant>>();
    QSharedPointer<QSqlQuery> mQuery = db->call("get_task_type_details", "");
    if (mQuery->first()) {
        QMap<QString, int> fieldMap = MySQLHandler::getFieldMap(mQuery);
        do {
            QMap<QString, QVariant> row = QMap<QString, QVariant>();
            row["type_enum"] =                         MySQLHandler::getValueFromQuery(fieldMap.value("type_enum"), mQuery);
            row["type_category"] =                     MySQLHandler::getValueFromQuery(fieldMap.value("type_category"), mQuery);
            row["enabled"] =                           MySQLHandler::getValueFromQuery(fieldMap.value("enabled"), mQuery);
            row["for_self_managed"] =                  MySQLHandler::getValueFromQuery(fieldMap.value("for_self_managed"), mQuery);
            row["visible_community"] =                 MySQLHandler::getValueFromQuery(fieldMap.value("visible_community"), mQuery);
            row["shell_task"] =                        MySQLHandler::getValueFromQuery(fieldMap.value("shell_task"), mQuery);
            row["source_and_target"] =                 MySQLHandler::getValueFromQuery(fieldMap.value("source_and_target"), mQuery);
            row["sourcing"] =                          MySQLHandler::getValueFromQuery(fieldMap.value("sourcing"), mQuery);
            row["type_text"] =                         MySQLHandler::getValueFromQuery(fieldMap.value("type_text"), mQuery);
            row["type_text_short"] =                   MySQLHandler::getValueFromQuery(fieldMap.value("type_text_short"), mQuery);
            row["colour"] =                            MySQLHandler::getValueFromQuery(fieldMap.value("colour"), mQuery);
            row["claimed_template"] =                  MySQLHandler::getValueFromQuery(fieldMap.value("claimed_template"), mQuery);
            row["show_section"] =                      MySQLHandler::getValueFromQuery(fieldMap.value("show_section"), mQuery);
            row["memsource_name"] =                    MySQLHandler::getValueFromQuery(fieldMap.value("memsource_name"), mQuery);
            row["unit_count_text"] =                   MySQLHandler::getValueFromQuery(fieldMap.value("unit_count_text"), mQuery);
            row["unit_count_text_short"] =             MySQLHandler::getValueFromQuery(fieldMap.value("unit_count_text_short"), mQuery);
            row["pricing_and_recognition_unit_text"] = MySQLHandler::getValueFromQuery(fieldMap.value("pricing_and_recognition_unit_text"), mQuery);
            row["source_unit_for_later_stats"] =       MySQLHandler::getValueFromQuery(fieldMap.value("source_unit_for_later_stats"), mQuery);
            row["unit_rate"] =                         MySQLHandler::getValueFromQuery(fieldMap.value("unit_rate"), mQuery);
            row["rate_for_recognition"] =              MySQLHandler::getValueFromQuery(fieldMap.value("rate_for_recognition"), mQuery);
            task_type_details.append(row);
        } while (mQuery->next());
    }
    return task_type_details;
}
