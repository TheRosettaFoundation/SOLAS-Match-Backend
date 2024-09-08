#include "invoice.h"
#include "Common/MySQLHandler.h"
#include "Common/Definitions.h"

void invoice::run(int user_id, int badge_id)
{
    qDebug() << "invoice user_id:" << user_id << "badge_id:" << badge_id;

    ConfigParser settings;
    QString error = "";
    QSharedPointer<MySQLHandler> db = MySQLHandler::getInstance();

    QSharedPointer<User> user = UserDao::getUser(db, user_id);
    if (user.isNull()) error = "Failed to generate invoice email, unable to find relevant data in the database for user_id: " + QString::number(user_id);

    if (error == "") {
        std::string email_body;

        ctemplate::TemplateDictionary dict("invoice");
        dict.SetValue("USERNAME", Email::htmlspecialchars(user->display_name()));

        QString invoice_link = settings.get("site.url") + "https://twbplatform.org/invoice/" + QString::number(badge_id) + "/";
        dict.SetValue("INVOICE_LINK", invoice_link.toStdString());


        QString templateLocation = QString(TEMPLATE_DIRECTORY) + "emails/invoice.tpl";
        ctemplate::ExpandTemplate(templateLocation.toStdString(), ctemplate::DO_NOT_STRIP, &dict, &email_body);

        UserDao::queue_email(db, user_id, QString::fromStdString(user->email()), "Invoice from Clear Global", QString::fromUtf8(email_body.c_str()), LOW);
        UserDao::log_email_sent(db, user_id, 0, 0, 0, 0, 0, 0, "invoice_to_volunteer");
    } else {
        IEmailGenerator::generateErrorEmail(error);
    }
}
