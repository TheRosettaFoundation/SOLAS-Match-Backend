#include "BadgeDao.h"

#include "Common/ModelGenerator.h"

QList<QSharedPointer<Badge> > BadgeDao::getBadges(QSharedPointer<MySQLHandler> db, int id, int orgId, QString name, QString description)
{
    QList<QSharedPointer<Badge> > badges = QList<QSharedPointer<Badge> >();
    QString args = "";

    if (id > 0) {
        args += QString::number(id) + ", ";
    } else {
        args += "null, ";
    }

    if (name.length() > 0) {
        args += name + ", ";
    } else {
        args += "null, ";
    }

    if (description.length() > 0) {
        args += description + ", ";
    } else {
        args += "null, ";
    }

    if (orgId > 0) {
        args += QString::number(orgId);
    } else {
        args += "null";
    }

    QSharedPointer<QSqlQuery> mQuery = db->call("getBadge", args);
    if (mQuery->first()) {
        QMap<QString, int> fieldMap = MySQLHandler::getFieldMap(mQuery);
        do {
            QSharedPointer<Badge> badge = QSharedPointer<Badge>(new Badge());
            ModelGenerator::Generate(mQuery, badge, fieldMap);
            badges.append(badge);
        } while (mQuery->next());
    }

    return badges;
}

QSharedPointer<Badge> BadgeDao::getBadge(QSharedPointer<MySQLHandler> db, int id, int orgId, QString name, QString description)
{
    QSharedPointer<Badge> ret = QSharedPointer<Badge>();
    QList<QSharedPointer<Badge> > badges = BadgeDao::getBadges(db, id, orgId, name, description);
    if (badges.length() > 0) {
        ret = badges.at(0);
    }
    return ret;
}
