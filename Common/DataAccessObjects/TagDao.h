#ifndef TAGDAO_H
#define TAGDAO_H

#include <QtSql/QSqlQuery>
#include <QList>
#include <QString>

#include "Common/MySQLHandler.h"
#include "Common/protobufs/models/Tag.pb.h"

class TagDao
{
public:
    static QList<Tag *> *getUserTags(MySQLHandler *db, int user_id);
    static QList<Tag *> *getTaskTags(MySQLHandler *db, int task_id);

};

#endif // TAGDAO_H
