
#include "Smtp.h"

#include <QDebug>
#include <QTimer>

#include "../Common/ConfigParser.h"

Smtp::Smtp()
{
    count_checkEmailQueue = 0;
    smtp = new QxtSmtp();
    isConnected = false;
    busy = false;
    reconnect_count = 0;
    currentMessage = NULL;
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
    mail_message.setSender(email_request["sender"]);
    if (!test) mail_message.addRecipient(email_request["recipient"]);
    if ( test) mail_message.addRecipient("alanabarrett0@gmail.com"); // TEST CODE

    if (!test || (QString::compare(only_send, email_request["subject"]) == 0)) {
        QString recipientString = "%20" + email_request["recipient"];
        recipientString.replace("@", "%40");
        mail_message.setExtraHeader("List-Unsubscribe", "<mailto:info@kato.translatorswb.org?subject=Unsubscribe%20from%20TWB%3A" + recipientString  + ">");
        mail_message.setSubject(email_request["subject"]);
        mail_message.setExtraHeader("Content-Type", "text/html; charset=\"UTF-8\"");
        mail_message.setExtraHeader("Content-Transfer-Encoding", "quoted-printable");
        mail_message.setBody(email_request["body"]);

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
            QMap<QString, QVariant> email_request = TaskDao::get_email_request(db);
            if (!email_request.isNull()) {



email_request["recipient"])
email_request["sender"])
email_request["subject"])
email_request["body"])




    if (!busy) {

        EmailQueue::ConstIterator i = emailQueue->constBegin();
        QSharedPointer<Email> queue_begin = emailQueue->constBegin().key();
qDebug() << "SMTP::checkEmailQueue constBegin(): " << queue_begin << ", constEnd(): " << emailQueue->constEnd().key();
        if (i != emailQueue->constEnd()) {
            this->currentMessage = i.value();
            QSharedPointer<Email> email = i.key();
            int queue_count = emailQueue->count();
qDebug() << "SMTP::checkEmailQueue Removing from Queue: " << i.key() << ", count(): " << queue_count;
            int number_removed = emailQueue->remove(i.key());

            int queue_count_new = emailQueue->count();
            bool contains_email = emailQueue->contains(email);
            QString contains_email_string = "false";
            if (contains_email) contains_email_string = "true";
            QSharedPointer<Email> queue_begin_new;
            if (queue_count_new) queue_begin_new = emailQueue->constBegin().key();
            if (number_removed == 0 || contains_email || (queue_count_new + 1) != queue_count || (queue_count_new && (queue_begin == queue_begin_new))) {
                if (queue_count_new) {
qDebug() << "SMTP::checkEmailQueue emailQueue->remove() Failed? number_removed:" << number_removed << ", contains_email:" << contains_email_string << ", queue_count_new:" << queue_count_new << ", queue_begin_new:" << queue_begin_new;
                } else {
qDebug() << "SMTP::checkEmailQueue emailQueue->remove() Failed? number_removed:" << number_removed << ", contains_email:" << contains_email_string << ", queue_count_new:" << queue_count_new;
                }
                if (number_removed == 0) {
                    emailQueue->clear(); // Try recover
                    queue_count_new = emailQueue->count();
                    if (queue_count_new) {
                        queue_begin_new = emailQueue->constBegin().key();
qDebug() << "SMTP::checkEmailQueue emailQueue->clear() queue_count_new:" << queue_count_new << ", queue_begin_new:" << queue_begin_new;
                    } else {
qDebug() << "SMTP::checkEmailQueue emailQueue->clear() queue_count_new:" << queue_count_new;
                    }
                }
            }

          QString email_for_hash = "";
          email_for_hash += email_request["recipient"];
          email_for_hash += email_request["subject"];
          email_for_hash += email->email_request["subject"];
          email_for_hash += email_request["body"];
          QByteArray hash = QCryptographicHash::hash(email_for_hash.toUtf8(), QCryptographicHash::Md5);

          if (email->getSubject().indexOf("Password Reset") != -1 || mail_text_hashes->indexOf(hash) == -1) { // Only send if identical mail not already sent
            mail_text_hashes->append(hash);

            qDebug() << "===============================";
            qDebug() << "Recipient: " << email_request["recipient"]);
            qDebug() << "Subject: " << email_request["subject"]);
            qDebug() << email_request["body"];
            qDebug() << "================================";

            this->send(email_request);
          }
          else qDebug() << "SMTP::checkEmailQueue Skipped: " << email_request["subject"] << email_request["recipient"];
        }
        else qDebug() << "SMTP::checkEmailQueue i == emailQueue->constEnd()";
    }



                TaskDao::mark_email_request_sent(db, email_request["id"]);
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
