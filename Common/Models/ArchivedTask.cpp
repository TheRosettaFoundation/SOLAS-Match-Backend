#include "ArchivedTask.h"

ArchivedTask::ArchivedTask()
{
    this->archive_id = -1;
    this->task_id = -1;
}

ArchivedTask::ArchivedTask(QSqlQuery *q)
{
    this->setArchiveId(MySQLHandler::getValueFromQuery("archived_task_id", q).toInt());
    this->setTaskId(MySQLHandler::getValueFromQuery("task_id", q).toInt());
    this->setOrgId(MySQLHandler::getValueFromQuery("organisation_id", q).toInt());
    this->setTitle(MySQLHandler::getValueFromQuery("title", q).toString());
    this->setWordcount(MySQLHandler::getValueFromQuery("word_count", q).toInt());
    this->setSourceId(MySQLHandler::getValueFromQuery("source_id", q).toInt());
    this->setTargetId(MySQLHandler::getValueFromQuery("target_id", q).toInt());
    this->setCreatedTime(MySQLHandler::getValueFromQuery("created_time", q).toString());
    this->setArchivedTime(MySQLHandler::getValueFromQuery("archived_time", q).toString());
    this->setImpact(MySQLHandler::getValueFromQuery("impact", q).toString());
    this->setReferencePage(MySQLHandler::getValueFromQuery("reference_page", q).toString());
}

QList<ArchivedTask> *ArchivedTask::getArchivedTasks(MySQLHandler *db, int arc_id, int t_id, int o_id)
{
    QList<ArchivedTask> *ret = new QList<ArchivedTask>();
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
            ArchivedTask task(mQuery);
            ret->append(task);
        } while(mQuery->next());
    }

    return ret;
}

ArchivedTask ArchivedTask::getArchivedTask(MySQLHandler *db, int arc_id, int t_id, int o_id)
{
    ArchivedTask task;
    QList<ArchivedTask> *arc_tasks = ArchivedTask::getArchivedTasks(db, arc_id, t_id, o_id);
    if(arc_tasks->count() > 0) {
        task = arc_tasks->at(0);
    }
    return task;
}

int ArchivedTask::getArchiveId()
{
    return archive_id;
}

int ArchivedTask::getTaskId()
{
    return task_id;
}

int ArchivedTask::getOrgId()
{
    return org_id;
}

QString ArchivedTask::getTitle()
{
    return title;
}

int ArchivedTask::getWordCount()
{
    return word_count;
}

int ArchivedTask::getSourceId()
{
    return source_id;
}

int  ArchivedTask::getTargetId()
{
    return target_id;
}

QString ArchivedTask::getCreatedTime()
{
    return created_time;
}

QString ArchivedTask::getArchivedTime()
{
    return archived_time;
}

QString ArchivedTask::getImpact()
{
    return impact;
}

QString ArchivedTask::getReferencePage()
{
    return reference_page;
}

void ArchivedTask::setArchivedTime(QString time)
{
    archived_time = time;
}

void ArchivedTask::setArchiveId(int id)
{
    archive_id = id;
}

void ArchivedTask::setCreatedTime(QString time)
{
    created_time = time;
}

void ArchivedTask::setImpact(QString impact)
{
    this->impact = impact;
}

void ArchivedTask::setOrgId(int id)
{
    org_id = id;
}

void ArchivedTask::setReferencePage(QString reference_page)
{
    this->reference_page = reference_page;
}

void ArchivedTask::setSourceId(int id)
{
    source_id = id;
}

void ArchivedTask::setTargetId(int id)
{
    target_id = id;
}

void ArchivedTask::setTaskId(int id)
{
    task_id = id;
}

void ArchivedTask::setTitle(QString title)
{
    this->title = title;
}

void ArchivedTask::setWordcount(int word_count)
{
    this->word_count = word_count;
}
