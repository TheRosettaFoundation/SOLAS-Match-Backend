
#include "Smtp.h"

#include <QDebug>
#include <QTimer>

#include "../Common/ConfigParser.h"

Smtp::Smtp()
{
    smtp = new QxtSmtp();
    isConnected = false;
    busy = false;
    currentMessage = NULL;
    emailQueue = QSharedPointer<EmailQueue>(new EmailQueue());

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

void Smtp::send(QSharedPointer<Email> email)
{
    QxtMailMessage mail_message;
    mail_message.setSender(email->getSender());
    QString recipientString = "";
    foreach(QString recipient, email->getRecipients())
    {
        if (!test) mail_message.addRecipient(recipient);
        recipientString += "%20" + recipient;
    }

    if (test) mail_message.addRecipient("alanabarrett0@gmail.com"); // TEST CODE
    if (test) mail_message.addRecipient("eric.paquin@live.ie"); // TEST CODE
    if (test) mail_message.addRecipient("info@trommons.org"); // TEST CODE
    if (test) mail_message.addRecipient("alanabarrett0@yahoo.com"); // TEST CODE
    if (test) mail_message.addRecipient("alanbarrett@therosettafoundation.org"); // TEST CODE

  if (!test || (QString::compare(only_send, email->getSubject()) == 0)) {
    recipientString.replace("@", "%40");
    mail_message.setExtraHeader("List-Unsubscribe", "<mailto:info@trommons.org?subject=Unsubscribe%20from%20Trommons%3A" + recipientString  + ">");
    mail_message.setSubject(email->getSubject());
    mail_message.setExtraHeader("Content-Type", "text/html; charset=\"UTF-8\"");
    mail_message.setExtraHeader("Content-Transfer-Encoding", "quoted-printable");
    mail_message.setBody(email->getBody());

    if(!isConnected) {
        this->init();
    }
    busy = true;
    smtp->send(mail_message);
  }
}

QSharedPointer<EmailQueue> Smtp::getEmailQueue()
{
    return emailQueue;
}

void Smtp::checkEmailQueue()
{
    if (!busy && !emailQueue->isEmpty()) {
        //qDebug() << "Getting message from queue";
        EmailQueue::ConstIterator i = emailQueue->constBegin();
        if (i != emailQueue->constEnd()) {
            this->currentMessage = i.value();
            QSharedPointer<Email> email = i.key();
            emailQueue->remove(i.key());

          QString email_for_hash = "";
          foreach(QString recipient, email->getRecipients()) {
              email_for_hash += recipient;
          }
          email_for_hash += email->getSender();
          email_for_hash += email->getSubject();
          email_for_hash += email->getBody();
          QByteArray hash = QCryptographicHash::hash(email_for_hash.toUtf8(), QCryptographicHash::Md5);

          if (mail_text_hashes->indexOf(hash) == -1) { // Only send if identical mail not already sent
            mail_text_hashes->append(hash);
            email->printEmail();
            this->send(email);
          }
        }
    }
}

void Smtp::connected()
{
    qDebug() << "SMTP::Connected to host successfully";
    this->isConnected = true;
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
