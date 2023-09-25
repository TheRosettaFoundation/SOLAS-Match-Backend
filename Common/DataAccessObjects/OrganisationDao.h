#ifndef ORGANISATIONDAO_H
#define ORGANISATIONDAO_H

#include <QtSql/QSqlQuery>
#include <QList>
#include <QString>
#include <QSharedPointer>

#include "Common/protobufs/models/Organisation.pb.h"
#include "Common/protobufs/models/User.pb.h"
#include "Common/MySQLHandler.h"

using namespace  SolasMatch::Common::Protobufs::Models;

class OrganisationDao
{
public:
    static QSharedPointer<Organisation> getOrg(QSharedPointer<MySQLHandler> db, int org_id);
};

#endif // ORGANISATIONDAO_H
