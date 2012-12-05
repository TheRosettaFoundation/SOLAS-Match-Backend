#ifndef TASKDAO_H
#define TASKDAO_H

#include <QtSql/QSqlQuery>
#include <QList>
#include <QString>

#include "Common/MySQLHandler.h"
#include "../protobufs/models/ArchivedTask.pb.h"
#include "../protobufs/models/Task.pb.h"

class TaskDao
{
public:
    static QList<Task *> *getTasks(MySQLHandler *db, int id = -1, int org_id = -1, QString title = "",
                          QString imp = "", QString ref_page = "", int wc = -1, int s_lang_id = -1,
                          int t_lang_id = -1, QString time = "", int s_reg_id = -1, int t_reg_id = -1);
    static Task *getTask(MySQLHandler *db, int id = -1, int org_id = -1, QString title = "",
                          QString imp = "", QString ref_page = "", int wc = -1, int s_lang_id = -1,
                          int t_lang_id = -1, QString time = "", int s_reg_id = -1, int t_reg_id = -1);
    static QList<Task *> *getActiveTasks(MySQLHandler *db, int limit = -1);
    static QList<ArchivedTask *> *getArchivedTasks(MySQLHandler *db, int arc_id = -1, int t_id = -1, int o_id = -1);
    static ArchivedTask *getArchivedTask(MySQLHandler *db, int arc_id = -1, int t_id = -1, int o_id = -1);

};

#endif // TASKDAO_H
