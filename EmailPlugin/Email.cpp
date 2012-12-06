#include "Email.h"

#include <QDebug>

Email::Email(QString to, QString from, QString subject, QString body)
{
    if(to.compare("") != 0) {
        this->recipient.append(to);
    }
    this->sender = from;
    this->subject = subject;
    this->body = body;
}

QStringList Email::getRecipients()
{
    return this->recipient;
}

QString Email::getSender()
{
    return this->sender;
}

QString Email::getSubject()
{
    return this->subject;
}

QString Email::getBody()
{
    return this->body;
}

void Email::addRecipient(QString to)
{
    this->recipient.append(to);
}

void Email::setSender(QString from)
{
    this->sender = from;
}

void Email::setSubject(QString sub)
{
    this->subject = sub;
}

void Email::setBody(QString body)
{
    this->body = body;
}

/*
 *  Used to print email details when testing
 */
void Email::printEmail()
{
    qDebug() << "===============================";
    qDebug() << "Recipients: " << this->recipient;
    qDebug() << "Sender: " << this->sender;
    qDebug() << "Subject: " << this->subject;
    qDebug() << this->body;
    qDebug() << "================================";
}
