#include "need_linguist_t_code.h"
#include "Common/MySQLHandler.h"
#include "Common/Definitions.h"

void need_linguist_t_code::run(int task_id, int claimant_id)
{
    qDebug() << "need_linguist_t_code task_id:" << task_id << "claimant_id:" << claimant_id;

    ConfigParser settings;
    QString error = "";
    QSharedPointer<MySQLHandler> db = MySQLHandler::getInstance();

    if (claimant_id == -1) {
        QMap<QString, QVariant> sun_po_error = UserDao::get_sun_po_errors(db);
        if (sun_po_error.isEmpty()) return;

        int task_id_from_error = sun_po_error["task_id"].toInt();
        std::string message = sun_po_error["message"].toString().toStdString();
        qDebug() << "need_linguist_t_code (sun_po_error) task_id:" << task_id << QString("message:") << QString(message);

        QList<int> admin_ids;
        //admin_ids.append(237869); // Rachel
        //admin_ids.append(237873); // Virginie
        //admin_ids.append(24985);  // Ambra
/* (**)DEL
        admin_ids.append(246046);  // twblinguistcode@clearglobal.org
(**)DEL */
admin_ids.append(3297);    //(**)DEL
        //admin_ids.append(3297);    // Temporary Test Alan

        foreach (int admin_id, admin_ids) {
            QSharedPointer<User> admin = UserDao::getUser(db, admin_id);
            if (!admin.isNull()) {
                std::string email_body2;
                ctemplate::TemplateDictionary dict("sun_po_error");
                dict.SetValue("ADMIN_NAME", Email::htmlspecialchars(admin->display_name()));
                dict.SetValue("MESSAGE", message);
                QString task_view = settings.get("site.url") + "task/" + QString::number(task_id_from_error) + "/view";
                dict.SetValue("TASK_VIEW", task_view.toStdString());

                QString templateLocation = QString(TEMPLATE_DIRECTORY) + "emails/sun_po_error.tpl";
                ctemplate::ExpandTemplate(templateLocation.toStdString(), ctemplate::DO_NOT_STRIP, &dict, &email_body2);

                UserDao::queue_email(db, admin_id, QString::fromStdString(admin->email()), "Sun Purchase Order Error for task_id " + QString::number(task_id_from_error), QString::fromUtf8(email_body2.c_str()), LOW);
                UserDao::log_email_sent(db, admin_id, task_id, 0, 0, 0, admin_id, 0, "sun_po_error_to_admin");
            }
        }
        return;
    }

    QSharedPointer<User> claimant = UserDao::getUser(db, claimant_id);
    if (claimant.isNull()) error = "Failed to generate need_linguist_t_code email, unable to find relevant data in the database for claimant_id: " + QString::number(claimant_id);

    QMap<QString, QVariant> linguist_payment_information = UserDao::get_linguist_payment_information(db, claimant_id);

    if (error == "") {
      if (UserDao::get_email_sent_for_linguist_payment_information(db, claimant_id).isEmpty()) {
        QList<int> admin_ids;
        //admin_ids.append(237869); // Rachel
        //admin_ids.append(237873); // Virginie
        //admin_ids.append(24985);  // Ambra
        admin_ids.append(246046);  // twblinguistcode@clearglobal.org
        //admin_ids.append(3297);    // Temporary Test Alan

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
      } else qDebug() << "need_linguist_t_code email already sent task_id:" << task_id << "claimant_id:" << claimant_id;
    } else {
        IEmailGenerator::generateErrorEmail(error);
    }
}
