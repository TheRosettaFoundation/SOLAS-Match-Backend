#ifndef TASKDAO_H
#define TASKDAO_H

#include <QtSql/QSqlQuery>
#include <QList>
#include <QString>
#include <QSharedPointer>

#include "Common/MySQLHandler.h"
#include "../protobufs/models/ArchivedTask.pb.h"
#include "../protobufs/models/User.pb.h"
#include "../protobufs/models/Task.pb.h"

class TaskDao
{
public:
    static QList<QSharedPointer<Task> > getTasks(MySQLHandler *db, int id = -1, int projectId = -1, QString title = "",
                          int wc = -1, QString sourceLang = "", QString targetLangId = "", QString createdTime = "",
                          QString sourceCountry = "", QString targetCountry = "", QString comment = "",
                          int type = -1, int status = -1, int published = -1, QString deadlineTime = "");
    static QSharedPointer<Task> getTask(MySQLHandler *db, int id = -1, int projectId = -1, QString title = "",
                          int wc = -1, QString sourceLang = "", QString targetLangId = "", QString createdTime = "",
                          QString sourceCountry = "", QString targetCountry = "", QString comment = "",
                          int type = -1, int status = -1, int published = -1, QString deadlineTime = "");
    static QSharedPointer<Task> insertAndUpdate(MySQLHandler *db, QSharedPointer<Task> task);
    static QList<QSharedPointer<Task> > getActiveTasks(MySQLHandler *db, int limit = -1);
    static QList<QSharedPointer<Task> > getOverdueTasks(MySQLHandler *db);
    static QSharedPointer<User> getTaskTranslator(MySQLHandler *db, int task_id);
    static QList<QSharedPointer<User> > getSubscribedUsers(MySQLHandler *db, int task_id);
    static QList<QSharedPointer<ArchivedTask> > getArchivedTasks(MySQLHandler *db, int arc_id = -1, int o_id = -1);
    static QSharedPointer<ArchivedTask> getArchivedTask(MySQLHandler *db, int arc_id = -1, int o_id = -1);

};

#endif // TASKDAO_H
