#include "AdminDao.h"

#include "Common/ModelGenerator.h"

QList<QSharedPointer<User> > AdminDao::getAdmins(QSharedPointer<MySQLHandler> db, int orgId)
{
    QList<QSharedPointer<User> > admins = QList<QSharedPointer<User> >();
    QString args = "";

    if (orgId > 0) {
        args += QString::number(orgId);
    } else {
        args += "null";
    }

    QSharedPointer<QSqlQuery> q = db->call("getAdmin", args);
    if (q->first()) {
        do {
            admins.append(ModelGenerator::GenerateUser(q));
        } while (q->next());
    }
    return admins;
}
