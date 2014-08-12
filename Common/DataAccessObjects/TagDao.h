#ifndef TAGDAO_H
#define TAGDAO_H

#include <QtSql/QSqlQuery>
#include <QList>
#include <QString>
#include <QSharedPointer>

#include "Common/MySQLHandler.h"
#include "Common/protobufs/models/Tag.pb.h"

using namespace  SolasMatch::Common::Protobufs::Models;

class TagDao
{
public:
    static QList<QSharedPointer<Tag> > getUserTags(QSharedPointer<MySQLHandler> db, int user_id);
    static QList<QSharedPointer<Tag> > getTaskTags(QSharedPointer<MySQLHandler> db, int task_id);

};

#endif // TAGDAO_H
