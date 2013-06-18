#include "TagDao.h"

#include "Common/ModelGenerator.h"

QList<QSharedPointer<Tag> > TagDao::getUserTags(QSharedPointer<MySQLHandler> db, int user_id)
{
    QList<QSharedPointer<Tag> > tags = QList<QSharedPointer<Tag> >();
    QSharedPointer<QSqlQuery> q = db->call("getUserTags", QString::number(user_id) + ", null");
    if(q->first()) {
        QMap<QString, int> fieldMap = MySQLHandler::getFieldMap(q);
        do {
            QSharedPointer<Tag> tag = QSharedPointer<Tag>(new Tag());
            ModelGenerator::Generate(q, tag, fieldMap);
            tags.append(tag);
        } while(q->next());
    }

    return tags;
}

QList<QSharedPointer<Tag> > TagDao::getTaskTags(QSharedPointer<MySQLHandler> db, int task_id)
{
    QList<QSharedPointer<Tag> > tags = QList<QSharedPointer<Tag> >();
    QSharedPointer<QSqlQuery> q = db->call("getTaskTags", QString::number(task_id));
    if(q->first()) {
        QMap<QString, int> fieldMap = MySQLHandler::getFieldMap(q);
        do {
            QSharedPointer<Tag> tag = QSharedPointer<Tag>(new Tag());
            ModelGenerator::Generate(q, tag, fieldMap);
            tags.append(tag);
        } while(q->next());
    }

    return tags;
}
