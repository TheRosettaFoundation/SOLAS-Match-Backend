#include "OrgCreatedNotifications.h"

#include <QSharedPointer>
#include <QDebug>

#include "Common/MySQLHandler.h"
#include "Common/MessagingClient.h"

#include "Common/DataAccessObjects/OrganisationDao.h"
#include "Common/DataAccessObjects/AdminDao.h"

#include "Common/protobufs/models/Organisation.pb.h"
#include "Common/protobufs/emails/OrgCreatedOrgAdmin.pb.h"
#include "Common/protobufs/emails/OrgCreatedSiteAdmin.pb.h"
#include "Common/protobufs/requests/OrgCreatedNotificationRequest.pb.h"

using namespace SolasMatch::Common::Protobufs::Emails;
using namespace SolasMatch::Common::Protobufs::Requests;
using namespace SolasMatch::Common::Protobufs::Models;

OrgCreatedNotifications::OrgCreatedNotifications()
{
    // Default Constructor
}

void OrgCreatedNotifications::run()
{
    qDebug() << "Starting new thread to send org created notifications";
    QString exchange = "SOLAS_MATCH";
    QString topic = "email";
    uint32_t length = 0;
    char *body = this->message->getMessage(&length);

    if (length > 0) {
        OrgCreatedNotificationRequest request;
        request.ParseFromString(body);

        QSharedPointer<MySQLHandler> db = MySQLHandler::getInstance();
        QSharedPointer<Organisation> org = OrganisationDao::getOrg(db, request.org_id());
        QList<QSharedPointer<User> > orgAdmins = AdminDao::getAdmins(db, request.org_id());
        QList<QSharedPointer<User> > siteAdmins = AdminDao::getAdmins(db);

        if (!org.isNull()) {
            MessagingClient publisher;
            if (publisher.init()) {
                if (orgAdmins.size() > 0) {
                    foreach (QSharedPointer<User> admin, orgAdmins) {
                        QString body = "";
                        OrgCreatedOrgAdmin email;
                        email.set_org_admin_id(admin->id());
                        email.set_org_id(request.org_id());
                        email.set_email_type(email.email_type());
                        body = QString::fromStdString(email.SerializeAsString());
                        publisher.publish(exchange, topic, body);
                    }
                } else {
                    qWarning() << "OrgCreatedNotifications: No org admins found";
                }

                if (siteAdmins.size() > 0) {
                    foreach (QSharedPointer<User> admin, siteAdmins) {
                        QString body = "";
                        OrgCreatedSiteAdmin email;
                        email.set_org_id(request.org_id());
                        email.set_email_type(email.email_type());
                        email.set_site_admin_id(admin->id());
                        body = QString::fromStdString(email.SerializeAsString());
                        publisher.publish(exchange, topic, body);
                    }
                } else {
                    qWarning() << "OrgCreatedNotifications: No site admins found";
                }
            } else {
                qWarning() << "OrgCreatedNotifications: Unable connect to RabbitMQ";
            }
        } else {
            qDebug() << "OrgCreatedNotifications: Unable to find relevant data in the DB, "
                     << "Searched for org ID " << QString::number(request.org_id());
        }
    }
}

void OrgCreatedNotifications::setAMQPMessage(AMQPMessage *message)
{
    this->message = message;
}
