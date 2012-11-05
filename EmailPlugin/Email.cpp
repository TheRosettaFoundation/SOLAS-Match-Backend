#include "Email.h"

Email::Email(QString to, QString from, QString subject, QString body)
{
    this->recipient = to;
    this->sender = from;
    this->subject = subject;
    this->body = body;
}

QString Email::getRecipient()
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

void Email::setRecipient(QString to)
{
    this->recipient = to;
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
