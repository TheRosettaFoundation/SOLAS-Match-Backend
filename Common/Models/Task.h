#ifndef TASK_H
#define TASK_H

#include <QtSql/QSqlQuery>
#include <QList>
#include <QString>

#include "Common/MySQLHandler.h"

class Task
{
public:
    Task();
    Task(QSqlQuery *q);
    static QList<Task> *getTasks(MySQLHandler *db, int id = -1, int org_id = -1, QString title = "",
                          QString imp = "", QString ref_page = "", int wc = -1, int s_lang_id = -1,
                          int t_lang_id = -1, QString time = "", int s_reg_id = -1, int t_reg_id = -1);
    static Task getTask(MySQLHandler *db, int id = -1, int org_id = -1, QString title = "",
                          QString imp = "", QString ref_page = "", int wc = -1, int s_lang_id = -1,
                          int t_lang_id = -1, QString time = "", int s_reg_id = -1, int t_reg_id = -1);
    static QList<Task> *getActiveTasks(MySQLHandler *db, int limit = -1);
    void setTaskId(int task_id);
    void setOrganisationId(int org_id);
    void setTitle(QString title);
    void setImpact(QString imp);
    void setReferencePage(QString page);
    void setWordCount(int count);
    void setSourceLangId(int lang_id);
    void setTargetLangId(int lang_id);
    void setCreatedTime(QString date);
    void setSourceRegionId(int region_id);
    void setTargetRegionId(int region_id);
    int getTaskId();
    int getOrganisationId();
    QString getTitle();
    QString getImpact();
    QString getReferencePage();
    int getWordCount();
    int getSourceLangId();
    int getTargetLangId();
    QString getCreatedTime();
    int getSourceRegionId();
    int getTargetRegionId();

private:
    int id;
    int org_id;
    QString descriptive_title;
    QString impact;
    QString reference_page;
    int word_count;
    int source_lang_id;
    int target_lang_id;
    QString created_time;
    int source_region_id;
    int target_region_id;

};

#endif // TASK_H
