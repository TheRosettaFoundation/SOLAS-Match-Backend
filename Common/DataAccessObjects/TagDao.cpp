#include "TagDao.h"

#include "Common/ModelGenerator.h"

QList<Tag *> *TagDao::getUserTags(MySQLHandler *db, int user_id)
{
    QList<Tag *> *tags = new QList<Tag *>();
    QSqlQuery *q = db->call("getUserTags", QString::number(user_id) + ", null");
    if(q->first()) {
        do {
            Tag *tag = ModelGenerator::GenerateTag(q);
            tags->append(tag);
        } while(q->next());
    }

    delete q;

    return tags;
}

QList<Tag *> *TagDao::getTaskTags(MySQLHandler *db, int task_id)
{
    QList<Tag *> *tags = new QList<Tag *>();
    QSqlQuery *q = db->call("getTaskTags", QString::number(task_id));
    if(q->first()) {
        do {
            Tag *tag = ModelGenerator::GenerateTag(q);
            tags->append(tag);
        } while(q->next());
    }

    delete q;

    return tags;
}
