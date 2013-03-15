#include "TaskDao.h"

#include "../ModelGenerator.h"
#include "UserDao.h"

QList<QSharedPointer<Task> > TaskDao::getTasks(MySQLHandler *db, int id, int projectId, QString title,
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
        args += title + ", ";
    } else {
        args += "null, ";
    }

    if(wc != -1) {
        args += QString::number(wc) + ", ";
    } else {
        args += "null, ";
    }

    if(sourceLang != "") {
        args += sourceLang + ", ";
    } else {
        args += "null, ";
    }

    if(targetLangId != "") {
        args += targetLangId + ", ";
    } else {
        args += "null, ";
    }

    if (createdTime != "") {
        args += createdTime + ", ";
    } else {
        args += "null, ";
    }

    if(sourceCountry != "") {
        args += sourceCountry + ", ";
    } else {
        args += "null, ";
    }

    if(targetCountry != "") {
        args += targetCountry + ", ";
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
        args += deadlineTime;
    } else {
        args += "null";
    }

    QSharedPointer<QSqlQuery> mQuery = db->call("getTask", args);
    if(mQuery->first()) {
        do {
            QSharedPointer<Task> task = ModelGenerator::GenerateTask(mQuery);
            ret.append(task);
        } while(mQuery->next());
    }

    return ret;
}

QSharedPointer<Task> TaskDao::getTask(MySQLHandler *db, int id, int projectId, QString title,
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

QList<QSharedPointer<Task> > TaskDao::getActiveTasks(MySQLHandler *db, int limit)
{
    QList<QSharedPointer<Task> > ret = QList<QSharedPointer<Task> >();
    QString args = "null";
    if(limit > 0) {
        args = QString::number(limit);
    }

    QSharedPointer<QSqlQuery> mQuery = db->call("getLatestAvailableTasks", args);
    if(mQuery->first()) {
        do {
            QSharedPointer<Task> task = TaskDao::getTask(db, MySQLHandler::getValueFromQuery("id", mQuery).toInt());
            ret.append(task);
        } while(mQuery->next());
    }

    return ret;
}

QSharedPointer<User> TaskDao::getTaskTranslator(MySQLHandler *db, int task_id)
{
    QSharedPointer<User> user;
    QSharedPointer<QSqlQuery> mQuery = db->call("getUserClaimedTask", QString::number(task_id));
    if(mQuery->first()) {
        user = ModelGenerator::GenerateUser(mQuery);
    }
    return user;
}

QList<QSharedPointer<User> > TaskDao::getSubscribedUsers(MySQLHandler *db, int task_id)
{
    QList<QSharedPointer<User> > users = QList<QSharedPointer<User> >();

    QSharedPointer<QSqlQuery> mQuery = db->call("getSubscribedUsers", QString::number(task_id));
    if(mQuery->first()) {
        do {
            users.append(UserDao::getUser(db, MySQLHandler::getValueFromQuery("user_id", mQuery).toInt()));
        } while(mQuery->next());
    }

    return users;
}

QList<QSharedPointer<ArchivedTask> > TaskDao::getArchivedTasks(MySQLHandler *db, int arc_id, int o_id)
{
    QList<QSharedPointer<ArchivedTask> > ret = QList<QSharedPointer<ArchivedTask> >();
    QString args = "";

    if(arc_id != -1) {
        args += QString::number(arc_id) + ", ";
    } else {
        args += "null, ";
    }

    if(o_id != -1) {
        args += QString::number(o_id) ;
    } else {
        args += "null";
    }

    QSharedPointer<QSqlQuery> mQuery = db->call("getArchivedTasks", args);
    if(mQuery->first()) {
        do {
            QSharedPointer<ArchivedTask> task = ModelGenerator::GenerateArchivedTask(mQuery);
            ret.append(task);
        } while(mQuery->next());
    }

    return ret;
}

QSharedPointer<ArchivedTask> TaskDao::getArchivedTask(MySQLHandler *db, int arc_id, int o_id)
{
    QSharedPointer<ArchivedTask> task = QSharedPointer<ArchivedTask>();
    QList<QSharedPointer<ArchivedTask> > arc_tasks = TaskDao::getArchivedTasks(db, arc_id, o_id);
    if(arc_tasks.count() > 0) {
        task = arc_tasks.at(0);
    }
    return task;
}
