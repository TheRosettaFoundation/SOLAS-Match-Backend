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

    QSharedPointer<QSqlQuery> q = db->call("getAdmins", args);
    if (q->first()) {
        QMap<QString, int> fieldMap = MySQLHandler::getFieldMap(q);
        do {
            QSharedPointer<User> admin = QSharedPointer<User>(new User());
            ModelGenerator::Generate(q, admin, fieldMap);
            admins.append(admin);
        } while (q->next());
    }
    return admins;
}

QList<QSharedPointer<User> > AdminDao::getAdminsForOrg(QSharedPointer<MySQLHandler> db, int orgId)
{
    QList<QSharedPointer<User> > admins = QList<QSharedPointer<User> >();
    QString args = "";

    if (orgId > 0) {
        args += QString::number(orgId);
    } else {
        args += "null";
    }

    QSharedPointer<QSqlQuery> q = db->call("getAdminsForOrg", args);
    if (q->first()) {
        QMap<QString, int> fieldMap = MySQLHandler::getFieldMap(q);
        do {
            QSharedPointer<User> admin = QSharedPointer<User>(new User());
            ModelGenerator::Generate(q, admin, fieldMap);
            admins.append(admin);
        } while (q->next());
    }
    return admins;
}
