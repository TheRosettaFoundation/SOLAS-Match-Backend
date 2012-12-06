
#include "Smtp.h"

#include <QDebug>

#include "../Common/ConfigParser.h"

Smtp::Smtp()
{
    smtp = new QxtSmtp();
    isConnected = false;

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

void Smtp::send(Email *email)
{
    QxtMailMessage mail_message;
    mail_message.setSender(email->getSender());
    foreach(QString recipient, email->getRecipients())
    {
        mail_message.addRecipient(recipient);
    }
    mail_message.setSubject(email->getSubject());
    mail_message.setExtraHeader("Content-Type", "text/html");
    mail_message.setBody(email->getBody());

    if(!isConnected) {
        this->init();
    }
    smtp->send(mail_message);
}

void Smtp::connected()
{
    qDebug() << "SMTP::Connected to host successfully";
    this->isConnected = true;
}

void Smtp::connectionFailed()
{
    qDebug() << "SMTP::Failed to connect to host";
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
}

void Smtp::finished()
{
    emit complete();
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
