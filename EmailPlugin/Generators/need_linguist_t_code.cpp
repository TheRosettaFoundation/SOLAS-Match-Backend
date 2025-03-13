#include "need_linguist_t_code.h"
#include "Common/MySQLHandler.h"
#include "Common/Definitions.h"

void need_linguist_t_code::run(int task_id, int claimant_id)
{
    qDebug() << "need_linguist_t_code task_id:" << task_id << "claimant_id:" << claimant_id;

    ConfigParser settings;
    QString error = "";
    QSharedPointer<MySQLHandler> db = MySQLHandler::getInstance();

    QSharedPointer<User> claimant = UserDao::getUser(db, claimant_id);
    if (claimant.isNull()) error = "Failed to generate need_linguist_t_code email, unable to find relevant data in the database for claimant_id: " + QString::number(claimant_id);

    QMap<QString, QVariant> linguist_payment_information = UserDao::get_linguist_payment_information(db, user_id);

    if (error == "") {
        QList<int> admin_ids;
        //admin_ids.append(237869); // Rachel
        //admin_ids.append(237873); // Virginie
        //admin_ids.append(24985);  // Ambra
        admin_ids.append(246046);  // twblinguistcode@clearglobal.org
admin_ids.append(3297);    // Temporary Test Alan

        std::string name_info = "";
        if (!(linguist_payment_information.isEmpty())) {
            std::string linguist_name     = linguist_payment_information["linguist_name"].toString().toStdString();
            std::string country           = linguist_payment_information["country"].toString().toStdString();
            std::string google_drive_link = linguist_payment_information["google_drive_link"].toString().toStdString();
            linguist_name = Email::htmlspecialchars(linguist_name);
            name_info = "These values have previously been entered as the correct values to use for payment purposes...<br />Official Name: " + linguist_name + "<br />" + "Billing Country: " + country + "<br />" + "Google Drive Folder Link: " + "<a href=\"" + google_drive_link + "\">" + google_drive_link + "</a>";
        }

        foreach (int admin_id, admin_ids) {
            QSharedPointer<User> admin = UserDao::getUser(db, admin_id);
            if (!admin.isNull()) {

                std::string email_body;

                ctemplate::TemplateDictionary dict("need_linguist_t_code");
                dict.SetValue("ADMIN_NAME",    Email::htmlspecialchars(admin->display_name()));
                dict.SetValue("LINGUIST_NAME", Email::htmlspecialchars(claimant->display_name()));

                QString linguist_link = settings.get("site.url") + QString::number(claimant->id()) + "/profile/";
                dict.SetValue("LINGUIST_LINK", linguist_link.toStdString());

                dict.SetValue("NAME_INFO", name_info);

                QString templateLocation = QString(TEMPLATE_DIRECTORY) + "emails/need_linguist_t_code.tpl";
                ctemplate::ExpandTemplate(templateLocation.toStdString(), ctemplate::DO_NOT_STRIP, &dict, &email_body);

                UserDao::queue_email(db, admin_id, QString::fromStdString(admin->email()), "Need Sun Linguist T-Code for " + QString::fromLatin1(claimant->display_name().c_str()), QString::fromUtf8(email_body.c_str()), LOW);
                UserDao::log_email_sent(db, admin_id, task_id, 0, 0, claimant_id, admin_id, 0, "need_linguist_t_code_to_admin");
            }
        }
    } else {
        IEmailGenerator::generateErrorEmail(error);
    }
}
