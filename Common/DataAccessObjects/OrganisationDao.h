#ifndef ORGANISATIONDAO_H
#define ORGANISATIONDAO_H

#include <QtSql/QSqlQuery>
#include <QList>
#include <QString>

#include "Common/protobufs/models/Organisation.pb.h"
#include "Common/MySQLHandler.h"

class OrganisationDao
{
public:
    static Organisation *getOrg(MySQLHandler *db, int org_id);

};

#endif // ORGANISATIONDAO_H
