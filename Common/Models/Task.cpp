#include "Task.h"

#include "Common/MySQLHandler.h"
#include <QDebug>

Task::Task()
{
}

Task::Task(QSqlQuery *q)
{
    this->setCreatedTime(MySQLHandler::getValueFromQuery("created_time", q).toString());
    this->setImpact(MySQLHandler::getValueFromQuery("impact", q).toString());
    this->setOrganisationId(MySQLHandler::getValueFromQuery("organisation_id", q).toInt());
    this->setReferencePage(MySQLHandler::getValueFromQuery("reference_page", q).toString());
    this->setSourceLangId(MySQLHandler::getValueFromQuery("source_id", q).toInt());
    this->setSourceRegionId(MySQLHandler::getValueFromQuery("sourceCountry", q).toInt());
    this->setTargetLangId(MySQLHandler::getValueFromQuery("target_id", q).toInt());
    this->setTargetRegionId(MySQLHandler::getValueFromQuery("targetCountry", q).toInt());
    this->setTaskId(MySQLHandler::getValueFromQuery("id", q).toInt());
    this->setTitle(MySQLHandler::getValueFromQuery("title", q).toString());
    this->setWordCount(MySQLHandler::getValueFromQuery("word_count", q).toInt());
}

QList<Task> *Task::getTasks(MySQLHandler *db, int id, int org_id, QString title, QString imp,
                            QString ref_page, int wc, int s_lang_id, int t_lang_id, QString time,
                            int s_reg_id, int t_reg_id)
{
    QList<Task> *ret = new QList<Task>();
    QString args = "";

    if(id != -1) {
        args += QString::number(id) + ", ";
    } else {
        args += "null, ";
    }

    if(org_id != -1) {
        args += QString::number(org_id) + ", ";
    } else {
        args += "null, ";
    }

    if(title != "") {
        args += title + ", ";
    } else {
        args += "null, ";
    }

    if(imp != "") {
        args += imp + ", ";
    } else {
        args += "null, ";
    }

    if(ref_page != "") {
        args += ref_page + ", ";
    } else {
        args += "null, ";
    }

    if(wc != -1) {
        args += QString::number(wc) + ", ";
    } else {
        args += "null, ";
    }

    if(s_lang_id != -1) {
        args += QString::number(s_lang_id) + ", ";
    } else {
        args += "null, ";
    }

    if(t_lang_id != -1) {
        args += QString::number(t_lang_id) + ", ";
    } else {
        args += "null, ";
    }

    if(time != "") {
        args += time + ", ";
    } else {
        args += "null, ";
    }

    if(s_reg_id != -1) {
        args += QString::number(s_reg_id) + ", ";
    } else {
        args += "null, ";
    }

    if(t_reg_id != -1) {
        args += QString::number(t_reg_id);
    } else {
        args += "null";
    }

    QSqlQuery *mQuery = db->call("getTask", args);
    if(mQuery->first()) {
        do {
            Task task(mQuery);
            ret->append(task);
        } while(mQuery->next());
    }

    return ret;
}

Task Task::getTask(MySQLHandler *db, int id, int org_id,
                   QString title, QString imp, QString ref_page,
                   int wc, int s_lang_id, int t_lang_id,
                   QString time, int s_reg_id, int t_reg_id)
{
    Task task;
    QList<Task> *task_list = Task::getTasks(db, id, org_id, title, imp, ref_page, wc,
                          s_lang_id, t_lang_id, time, s_reg_id, t_reg_id);
    if(task_list->count() > 0) {
        task = task_list->at(0);
    }
    return task;
}

void Task::setTaskId(int task_id)
{
    this->id = task_id;
}

void Task::setOrganisationId(int org_id)
{
    this->org_id = org_id;
}

void Task::setCreatedTime(QString date)
{
    this->created_time = date;
}

void Task::setImpact(QString imp)
{
    this->impact = imp;
}

void Task::setReferencePage(QString page)
{
    this->reference_page = page;
}

void Task::setSourceLangId(int lang_id)
{
    this->source_lang_id = lang_id;
}

void Task::setSourceRegionId(int region_id)
{
    this->source_region_id = region_id;
}

void Task::setTargetLangId(int lang_id)
{
    this->target_lang_id = lang_id;
}

void Task::setTargetRegionId(int region_id)
{
    this->target_region_id = region_id;
}

void Task::setTitle(QString title)
{
    this->descriptive_title = title;
}

void Task::setWordCount(int count)
{
    this->word_count = count;
}

QString Task::getCreatedTime()
{
    return this->created_time;
}

QString Task::getImpact()
{
    return this->impact;
}

int Task::getOrganisationId()
{
    return this->org_id;
}

QString Task::getReferencePage()
{
    return this->reference_page;
}

int Task::getSourceLangId()
{
    return this->source_lang_id;
}

int Task::getSourceRegionId()
{
    return this->source_region_id;
}

int Task::getTargetLangId()
{
    return this->target_lang_id;
}

int Task::getTargetRegionId()
{
    return this->target_region_id;
}

int Task::getTaskId()
{
    return this->id;
}

QString Task::getTitle()
{
    return this->descriptive_title;
}

int Task::getWordCount()
{
    return this->word_count;
}
