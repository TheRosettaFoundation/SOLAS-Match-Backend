#include "OrgCreatedNotifications.h"

#include <QSharedPointer>
#include <QDebug>

#include "Common/MySQLHandler.h"

#include "Common/DataAccessObjects/OrganisationDao.h"
#include "Common/DataAccessObjects/AdminDao.h"

#include "Common/protobufs/models/Organisation.pb.h"

using namespace SolasMatch::Common::Protobufs::Models;

static void OrgCreatedNotifications::run(int org_id)
{
    qDebug() << "OrgCreatedNotifications org_id: " << org_id;

    QSharedPointer<MySQLHandler> db = MySQLHandler::getInstance();
    QSharedPointer<Organisation> org = OrganisationDao::getOrg(db, org_id);
    QList<QSharedPointer<User> > orgAdmins = AdminDao::getAdmins(db, org_id);
    QList<QSharedPointer<User> > siteAdmins = AdminDao::getAdmins(db);

    if (!org.isNull()) {
        if (orgAdmins.size() > 0) {
            foreach (QSharedPointer<User> admin, orgAdmins) {
                OrgCreated_OrgEmail::run(org_id, admin->id());
            }
        } else {
            qDebug() << "OrgCreatedNotifications: No org admins found";
        }

        if (siteAdmins.size() > 0) {
            foreach (QSharedPointer<User> admin, siteAdmins) {
                OrgCreate_SiteAdmin::run(org_id, admin->id());
            }
        } else {
            qDebug() << "OrgCreatedNotifications: No site admins found";
        }
    } else {
        qDebug() << "OrgCreatedNotifications: Unable to find relevant data in the DB, "
                 << "Searched for org ID " << QString::number(org_id);
    }
}
