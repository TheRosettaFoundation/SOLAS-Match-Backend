#include "OrganisationDao.h"

#include "../ModelGenerator.h"

QSharedPointer<Organisation> OrganisationDao::getOrg(QSharedPointer<MySQLHandler> db, int org_id)
{
    QSharedPointer<Organisation> org;
    QString args = QString::number(org_id);
    args += ", null, null, null, null, null, null, null, null";
    QSharedPointer<QSqlQuery> result = db->call("getOrg", args);
    if(result->first())
    {
        org = ModelGenerator::GenerateOrg(result);
    }

    return org;
}

QList<QSharedPointer<User> > OrganisationDao::getOrgAdmins(QSharedPointer<MySQLHandler> db, int orgId)
{
    QList<QSharedPointer<User> > users = QList<QSharedPointer<User> >();
    QString args = QString::number(orgId);
    QSharedPointer<QSqlQuery> result = db->call("getAdmin", args);
    if (result->first()) {
        do {
            users.append(ModelGenerator::GenerateUser(result));
        } while (result->next());
    }
    return users;
}
