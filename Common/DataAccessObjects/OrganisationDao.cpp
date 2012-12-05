#include "OrganisationDao.h"

#include "../ModelGenerator.h"

Organisation *OrganisationDao::getOrg(MySQLHandler *db, int org_id)
{
    Organisation *org;
    QString args = QString::number(org_id);
    args += ", null, null, null";
    QSqlQuery *result = db->call("getOrg", args);
    if(result->first())
    {
        org = ModelGenerator::GenerateOrg(result);
    }

    return org;
}
