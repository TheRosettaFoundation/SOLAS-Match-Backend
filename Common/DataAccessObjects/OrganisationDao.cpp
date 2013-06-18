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
        QMap<QString, int> fieldMap = MySQLHandler::getFieldMap(result);
        org = QSharedPointer<Organisation>(new Organisation());
        ModelGenerator::Generate(result, org, fieldMap);
    }

    return org;
}

QList<QSharedPointer<User> > OrganisationDao::getOrgAdmins(QSharedPointer<MySQLHandler> db, int orgId)
{
    QList<QSharedPointer<User> > users = QList<QSharedPointer<User> >();
    QString args = QString::number(orgId);
    QSharedPointer<QSqlQuery> result = db->call("getAdmin", args);
    if (result->first()) {
        QMap<QString, int> fieldMap = MySQLHandler::getFieldMap(result);
        do {
            QSharedPointer<User> user = QSharedPointer<User>(new User());
            ModelGenerator::Generate(result, user, fieldMap);
            users.append(user);
        } while (result->next());
    }
    return users;
}
