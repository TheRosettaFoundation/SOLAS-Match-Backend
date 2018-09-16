#ifndef TASKDAO_H
#define TASKDAO_H

#include <QtSql/QSqlQuery>
#include <QList>
#include <QString>
#include <QSharedPointer>

#include "Common/MySQLHandler.h"
#include "Common/Definitions.h"
#include "../protobufs/models/ArchivedTask.pb.h"
#include "../protobufs/models/User.pb.h"
#include "../protobufs/models/Task.pb.h"

using namespace  SolasMatch::Common::Protobufs::Models;

class TaskDao
{
public:
    static QList<QSharedPointer<Task> > getTasks(QSharedPointer<MySQLHandler> db, int id = -1, int projectId = -1, QString title = "",
                          int wc = -1, QString sourceLang = "", QString targetLangId = "", QString createdTime = "",
                          QString sourceCountry = "", QString targetCountry = "", QString comment = "",
                          int type = -1, int status = -1, int published = -1, QString deadlineTime = "");
    static QSharedPointer<Task> getTask(QSharedPointer<MySQLHandler> db, int id = -1, int projectId = -1, QString title = "",
                          int wc = -1, QString sourceLang = "", QString targetLangId = "", QString createdTime = "",
                          QString sourceCountry = "", QString targetCountry = "", QString comment = "",
                          int type = -1, int status = -1, int published = -1, QString deadlineTime = "");
    static QSharedPointer<Task> insertAndUpdate(QSharedPointer<MySQLHandler> db, QSharedPointer<Task> task);
    static QSharedPointer<Task> insertAndUpdate(QSharedPointer<MySQLHandler> db, Task task);
    static QList<QSharedPointer<Task> > getActiveTasks(QSharedPointer<MySQLHandler> db, int limit = -1, int offset = RETURN_ALL);
    static QList<QSharedPointer<Task> > getOverdueTasks(QSharedPointer<MySQLHandler> db);
    static QList<QSharedPointer<Task> > getEarlyWarningTasks(QSharedPointer<MySQLHandler> db);
    static QList<QSharedPointer<Task> > getLateWarningTasks(QSharedPointer<MySQLHandler> db);
    static void taskNotificationSentInsertAndUpdate(QSharedPointer<MySQLHandler> db, int task_id, int notification);
    static QSharedPointer<User> getUserClaimedTask(QSharedPointer<MySQLHandler> db, int task_id);
    static QList<QSharedPointer<User> > getSubscribedUsers(QSharedPointer<MySQLHandler> db, int task_id);
    static QList<QSharedPointer<ArchivedTask> > getArchivedTasks(QSharedPointer<MySQLHandler> db, int arc_id = -1);
    static QSharedPointer<ArchivedTask> getArchivedTask(QSharedPointer<MySQLHandler> db, int arc_id = -1);
    static QList<QSharedPointer<Task> > getTaskPreReqs(QSharedPointer<MySQLHandler> db, int taskId);
    static QMultiMap<int, int> getTaskTagIds(QSharedPointer<MySQLHandler> db, int limit = RETURN_ALL, int offset = RETURN_ALL);
    static std::string get_matecat_url(QSharedPointer<MySQLHandler> db, QSharedPointer<Task> task);
    static bool is_task_translated_in_matecat(QSharedPointer<MySQLHandler> db, int taskId);
    static bool is_chunked_task(QSharedPointer<MySQLHandler> db, int taskId);
    static std::string getMatecatRevisionURL(QSharedPointer<MySQLHandler> db, QSharedPointer<Task> task);
    static QSharedPointer<Task> getMatchingTask(QSharedPointer<MySQLHandler> db, int task_id, int type_id);
    static QSharedPointer<Task> getParentTask(QSharedPointer<MySQLHandler> db, int task_id, int type_id);
};

#endif // TASKDAO_H
