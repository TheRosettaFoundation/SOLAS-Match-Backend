#include "Tag.h"

#include <QtSql/QSqlQuery>
#include <QString>

#include "Common/MySQLHandler.h"

Tag::Tag()
{
}

Tag::Tag(QSqlQuery *q)
{
    this->setTagId(MySQLHandler::getValueFromQuery("tag_id", q).toInt());
    this->setLabel(MySQLHandler::getValueFromQuery("label", q).toString());
}

QList<Tag> *Tag::getUserTags(MySQLHandler *db, int user_id)
{
    QList<Tag> *tags = new QList<Tag>();
    QSqlQuery *q = db->call("getUserTags", QString::number(user_id));
    if(q->first()) {
        do {
            Tag tag(q);
            tags->append(tag);
        } while(q->next());
    }

    delete q;

    return tags;
}

QList<Tag> *Tag::getTaskTags(MySQLHandler *db, int task_id)
{
    QList<Tag> *tags = new QList<Tag>();
    QSqlQuery *q = db->call("getTaskTags", QString::number(task_id));
    if(q->first()) {
        do {
            Tag tag(q);
            tags->append(tag);
        } while(q->next());
    }

    delete q;

    return tags;
}

void Tag::setTagId(int tag_id)
{
    this->id = tag_id;
}

void Tag::setLabel(QString text)
{
    this->label = text;
}

int Tag::getTagId()
{
    return this->id;
}

QString Tag::getLabel()
{
    return this->label;
}
