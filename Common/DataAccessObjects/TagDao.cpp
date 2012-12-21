#include "TagDao.h"

#include "Common/ModelGenerator.h"

QList<QSharedPointer<Tag> > TagDao::getUserTags(MySQLHandler *db, int user_id)
{
    QList<QSharedPointer<Tag> > tags = QList<QSharedPointer<Tag> >();
    QSharedPointer<QSqlQuery> q = db->call("getUserTags", QString::number(user_id) + ", null");
    if(q->first()) {
        do {
            QSharedPointer<Tag> tag = ModelGenerator::GenerateTag(q);
            tags.append(tag);
        } while(q->next());
    }

    return tags;
}

QList<QSharedPointer<Tag> > TagDao::getTaskTags(MySQLHandler *db, int task_id)
{
    QList<QSharedPointer<Tag> > tags = QList<QSharedPointer<Tag> >();
    QSharedPointer<QSqlQuery> q = db->call("getTaskTags", QString::number(task_id));
    if(q->first()) {
        do {
            QSharedPointer<Tag> tag = ModelGenerator::GenerateTag(q);
            tags.append(tag);
        } while(q->next());
    }

    return tags;
}
