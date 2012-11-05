
#include "Smtp.h"

#include <QDebug>

#include "../Common/ConfigParser.h"

Smtp::Smtp(QObject *parent, Email *email)
{
    qDebug() << "SMTP::Initialising Object";

    this->setParent(parent);

    /*QxtMailMessage *mail_message = new QxtMailMessage(email->getSender(),
                                             email->getRecipient());
    mail_message->setBody(email->getBody());
    mail_message->setSubject(email->getSubject());
    mail_message->setExtraHeader("Content-Type", "text/html");
    QxtSmtp *smtp = new QxtSmtp();
    smtp->connectToHost("solas-match.co.cc", 25);
    smtp->send(*mail_message);*/

    this->smtp = new QxtSmtp();
    this->message = new QxtMailMessage(email->getSender(), email->getRecipient());
    this->message->setSubject(email->getSubject());
    this->message->setExtraHeader("Content-Type", "text/html");
    this->message->setBody(email->getBody());

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

    this->smtp->connectToHost("solas-match.co.cc", 25);
    this->smtp->send(*message);
}

Smtp::~Smtp()
{
    delete message;
    delete smtp;
}

void Smtp::init()
{    
    /*qDebug() << "SMTP::Parsing mail options";
    ConfigParser settings;
    QString host = settings.get("mail.server");
    int port = settings.get("mail.port").toInt();*/

    this->smtp->connectToHost("solas-match.co.cc", 25);
}

void Smtp::send()
{
    int status = this->smtp->send(*message);
    qDebug() << "Send returned with status " << status;
}

void Smtp::connected()
{
    qDebug() << "SMTP::Connected to host successfully";
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
}

void Smtp::finished()
{
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
