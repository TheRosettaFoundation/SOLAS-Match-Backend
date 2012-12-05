#include "TaskDao.h"

#include "../ModelGenerator.h"

QList<ArchivedTask *> *TaskDao::getArchivedTasks(MySQLHandler *db, int arc_id, int t_id, int o_id)
{
    QList<ArchivedTask *> *ret = new QList<ArchivedTask *>();
    QString args = "";

    if(arc_id != -1) {
        args += QString::number(arc_id) + ", ";
    } else {
        args += "null, ";
    }

    if(t_id != -1) {
        args += QString::number(t_id) + ", ";
    } else {
        args += "null, ";
    }

    if(o_id != -1) {
        args += QString::number(o_id) ;
    } else {
        args += "null";
    }

    QSqlQuery *mQuery = db->call("getArchivedTasks", args);
    if(mQuery->first()) {
        do {
            ArchivedTask *task = ModelGenerator::GenerateArchivedTask(mQuery);
            ret->append(task);
        } while(mQuery->next());
    }

    return ret;
}

ArchivedTask *TaskDao::getArchivedTask(MySQLHandler *db, int arc_id, int t_id, int o_id)
{
    ArchivedTask *task = NULL;
    QList<ArchivedTask*> *arc_tasks = TaskDao::getArchivedTasks(db, arc_id, t_id, o_id);
    if(arc_tasks->count() > 0) {
        task = arc_tasks->at(0);
    }
    return task;
}
