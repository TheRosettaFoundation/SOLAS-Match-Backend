
#include "Smtp.h"

#include <QDebug>
#include <QTimer>

#include "../Common/ConfigParser.h"
#include "IEmailGenerator.h"

Smtp::Smtp()
{
    count_checkEmailQueue = 0;
    smtp = new QxtSmtp();
    isConnected = false;
    busy = false;
    reconnect_count = 0;
    mail_text_hashes = new QList<QByteArray>();

    QTimer *emailQueueReadTimer  = new QTimer();
    connect(emailQueueReadTimer, SIGNAL(timeout()), this, SLOT(checkEmailQueue()));
    emailQueueReadTimer->start(100);

    connect(smtp, SIGNAL(connected()), this, SLOT(connected()));
    connect(smtp, SIGNAL(connectionFailed()), this, SLOT(connectionFailed()));
    connect(smtp, SIGNAL(authenticated()), this, SLOT(authenticated()));
    connect(smtp, SIGNAL(authenticationFailed()), this, SLOT(authenticationFailed()));
    connect(smtp, SIGNAL(disconnected()), this, SLOT(disconnected()));
    connect(smtp, SIGNAL(finished()), this, SLOT(finished()));
    connect(smtp, SIGNAL(mailFailed(int,int)), this, SLOT(mailFailed(int,int)));
    connect(smtp, SIGNAL(mailSent(int)), this, SLOT(mailSent(int)));
    connect(smtp, SIGNAL(recipientRejected(int,QString)), this, SLOT(recipientRejected(int,QString)));
    connect(smtp, SIGNAL(senderRejected(int,QString)), this, SLOT(connected()));

    ConfigParser settings;
    test = (QString::compare("y", settings.get("mail.test")) == 0);
    if (test) only_send = settings.get("mail.only_send");

    host = settings.get("mail.server");
    port = settings.get("mail.port").toInt();
    smtp->setUsername(settings.get("mail.user").toLatin1());
    smtp->setPassword(settings.get("mail.password").toLatin1());
}

Smtp::~Smtp()
{
    delete smtp;
}

void Smtp::init()
{
    this->smtp->connectToHost(host, port);
}

void Smtp::send(QMap<QString, QVariant> email_request)
{
    QxtMailMessage mail_message;
    mail_message.setSender(email_request["sender"].toString());
    if (!test) mail_message.addRecipient(email_request["recipient"].toString());
    if ( test) mail_message.addRecipient("alanabarrett0@gmail.com"); // TEST CODE

    if (!test || (QString::compare(only_send, email_request["subject"].toString()) == 0)) {
        QString recipientString = "%20" + email_request["recipient"].toString();
        recipientString.replace("@", "%40");
        mail_message.setExtraHeader("List-Unsubscribe", "<mailto:info@kato.translatorswb.org?subject=Unsubscribe%20from%20TWB%3A" + recipientString  + ">");
        mail_message.setSubject(email_request["subject"].toString());
        mail_message.setExtraHeader("Content-Type", "text/html; charset=\"UTF-8\"");
        mail_message.setExtraHeader("Content-Transfer-Encoding", "quoted-printable");
        mail_message.setBody(email_request["body"].toString());

        if (!isConnected) {
            this->init();
        }
        busy = true;
        smtp->send(mail_message);
    }
}

void Smtp::checkEmailQueue()
{
    static QMutex mutex;
    if (mutex.tryLock()) {
        QSharedPointer<MySQLHandler> db = MySQLHandler::getInstance();
        QMap<QString, QVariant> email_request = UserDao::get_email_request(db);
        if (!email_request.isNull()) {
            if (!busy) {
                QString email_for_hash = "";
                email_for_hash += email_request["recipient"].toString();
                email_for_hash += email_request["subject"].toString();
                email_for_hash += email_request["body"].toString();
                QByteArray hash = QCryptographicHash::hash(email_for_hash.toUtf8(), QCryptographicHash::Md5);
                if (email->getSubject().indexOf("Password Reset") != -1 || mail_text_hashes->indexOf(hash) == -1) { // Only send if identical mail not already sent
                    mail_text_hashes->append(hash);
                    qDebug() << "===============================";
                    qDebug() << "Recipient: " << email_request["recipient"].toString());
                    qDebug() << "Subject: " << email_request["subject"].toString());
                    qDebug() << email_request["body"].toString();
                    qDebug() << "================================";

                    this->send(email_request);
                }
                else qDebug() << "SMTP::checkEmailQueue Skipped: " << email_request["subject"].toString() << email_request["recipient"].toString();

                UserDao::mark_email_request_sent(db, email_request["id"].toInt());
            } else {
                if ((count_checkEmailQueue++)%3000 == 0) { // 5 minutes (100ms 3000 times)
                    qDebug() << "SMTP::checkEmailQueue busy";
                }
            }
        }
        mutex.unlock();
    } else qDebug() << "checkEmailQueue: Skipping invocation";
}

void Smtp::connected()
{
    qDebug() << "SMTP::Connected to host successfully";
    this->isConnected = true;
    this->reconnect_count = 0;
}

void Smtp::connectionFailed()
{
    qDebug() << "SMTP::Failed to connect to host";
    this->busy = false;
}

void Smtp::authenticated()
{
    qDebug() << "SMTP::Connection authenticated";
}

void Smtp::authenticationFailed()
{
    qDebug() << "SMTP::authentication failure";
}

void Smtp::disconnected()
{
    qDebug() << "SMTP::Disconnected";
    this->isConnected = false;
    this->busy = false;

    if (smtp->pendingMessages() && this->reconnect_count++ < 2) { // Reconnect so can send failed email
        this->init();
        this->busy = true;
qDebug() << "SMTP::Disconnected INIT";//(**)
    }
}

void Smtp::finished()
{
    emit complete();
    busy = false;
    qDebug() << "SMTP::finished";
}

void Smtp::mailFailed(int mailID, int errorCode)
{
    qDebug() << "SMTP::Mail (" << mailID << ") failed with error code " << errorCode;
}

void Smtp::mailSent(int mailID)
{
    qDebug() << "Mail (" << mailID << ") sent successfully";
}

void Smtp::recipientRejected(int mailID, QString address)
{
    qDebug() << "SMTP::Recipient " << address << " rejected for mail id " << mailID;
}

void Smtp::senderRejected(int mailID, QString address)
{
    qDebug() << "SMTP::Sender " << address << " rejected for mail id " << mailID;
}
