#ifndef TAG_H
#define TAG_H

#include <QtSql/QSqlQuery>
#include <QList>
#include <QString>

#include "Common/MySQLHandler.h"

class Tag
{
public:
    Tag();
    Tag(QSqlQuery *q);
    static QList<Tag> *getUserTags(MySQLHandler *db, int user_id);
    static QList<Tag> *getTaskTags(MySQLHandler *db, int task_id);
    void setTagId(int tag_id);
    void setLabel(QString text);
    int getTagId();
    QString getLabel();

private:
    int id;
    QString label;

};

#endif // TAG_H
