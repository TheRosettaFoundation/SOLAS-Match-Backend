#ifndef BADGEDAO_H
#define BADGEDAO_H

#include <QSharedPointer>

#include "../protobufs/models/Badge.pb.h"
#include "Common/MySQLHandler.h"

class BadgeDao
{
public:
    static QList<QSharedPointer<Badge> > getBadges(QSharedPointer<MySQLHandler> db, int id = -1, int orgId = -1,
                                          QString name = "", QString description = "");
    static QSharedPointer<Badge> getBadge(QSharedPointer<MySQLHandler> db, int id = -1, int orgId = -1,
                                          QString name = "", QString description = "");

};

#endif // BADGEDAO_H
