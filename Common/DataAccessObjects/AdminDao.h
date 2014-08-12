#ifndef ADMINDAO_H
#define ADMINDAO_H

#include <QList>
#include <QSharedPointer>

#include "Common/MySQLHandler.h"
#include "Common/protobufs/models/User.pb.h"

using namespace  SolasMatch::Common::Protobufs::Models;

class AdminDao
{
public:
    static QList<QSharedPointer<User> > getAdmins(QSharedPointer<MySQLHandler> db, int orgId = -1);

};

#endif // ADMINDAO_H
