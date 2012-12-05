#ifndef TASKDAO_H
#define TASKDAO_H

#include <QtSql/QSqlQuery>
#include <QList>
#include <QString>

#include "Common/MySQLHandler.h"
#include "../protobufs/models/ArchivedTask.pb.h"

class TaskDao
{
public:
    static QList<ArchivedTask *> *getArchivedTasks(MySQLHandler *db, int arc_id = -1, int t_id = -1, int o_id = -1);
    static ArchivedTask *getArchivedTask(MySQLHandler *db, int arc_id = -1, int t_id = -1, int o_id = -1);

};

#endif // TASKDAO_H
