#ifndef ARCHIVEDTASK_H
#define ARCHIVEDTASK_H

#include <QtSql/QSqlQuery>
#include <QList>
#include <QString>

#include "Common/MySQLHandler.h"

class ArchivedTask
{
public:
    ArchivedTask();
    ArchivedTask(QSqlQuery *q);
    static QList<ArchivedTask> *getArchivedTasks(MySQLHandler *db, int arc_id = -1, int t_id = -1, int o_id = -1);
    static ArchivedTask getArchivedTask(MySQLHandler *db, int arc_id = -1, int t_id = -1, int o_id = -1);
    int getArchiveId();
    int getTaskId();
    int getOrgId();
    QString getTitle();
    int getWordCount();
    int getSourceId();
    int getTargetId();
    QString getCreatedTime();
    QString getArchivedTime();
    QString getImpact();
    QString getReferencePage();
    void setArchiveId(int id);
    void setTaskId(int id);
    void setOrgId(int id);
    void setTitle(QString title);
    void setWordcount(int word_count);
    void setSourceId(int id);
    void setTargetId(int id);
    void setCreatedTime(QString time);
    void setArchivedTime(QString time);
    void setImpact(QString impact);
    void setReferencePage(QString reference_page);

private:
    int archive_id;
    int task_id;
    int org_id;
    QString title;
    int word_count;
    int source_id;
    int target_id;
    QString created_time;
    QString archived_time;
    QString impact;
    QString reference_page;

};

#endif // ARCHIVEDTASK_H
