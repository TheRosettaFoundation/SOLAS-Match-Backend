#include "IEmailGenerator.h"

#include <QDebug>
#include <QStringList>
#include <ctemplate/template.h>

#include "Common/MySQLHandler.h"
#include "Common/ConfigParser.h"

#include "Common/DataAccessObjects/UserDao.h"

void IEmailGenerator::generateErrorEmail(QString error)
{
    QSharedPointer<MySQLHandler> db = MySQLHandler::getInstance();
    ConfigParser settings;

    QString body = "<p>Hello,</p><p>An error has occurred in the SOLAS-Match worker Daemon. ";
    body += error + "</p>";

    QStringList admins = settings.get("mail.admin_emails").split(",");
    foreach (QString admin, admins) {
        UserDao::queue_email(db, 0, admin.trimmed(), "An error has occurred", body);
    }
}
