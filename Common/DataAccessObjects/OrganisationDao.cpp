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
