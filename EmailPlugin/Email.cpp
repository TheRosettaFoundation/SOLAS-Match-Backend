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

std::string Email::htmlspecialchars(const std::string& in)
{
    std::string out;
    out.reserve(in.length());
    for(std::string::size_type i = 0; i < in.length(); i++) {
        switch(in[i]) {
            case '<':
                out.append("&lt;");
                break;
            case '>':
                out.append("&gt;");
                break;
            default:
                out.append(&in[i], 1);
                break;
        }
    }
    return out;
}

std::string Email::uiCleanseHTMLNewlineAndTabs(const std::string& in)
{
    std::string out;
    out.reserve(in.length() + 50);

    bool crEncountered;
    for (std::string::size_type i = 0; i < in.length(); i++) {
        switch(in[i]) {
            case '<':
                out.append("&lt;");
                crEncountered = false;
                break;
            case '>':
                out.append("&gt;");
                crEncountered = false;
                break;
            case '\r':
                out.append("<br/>");
                crEncountered = true;
                break;
            case '\n':
                if (!crEncountered) out.append("<br/>"); // \r\n, \r will already have output <br/>
                crEncountered = false;
                break;
            case '\t':
                out.append("&nbsp;&nbsp;&nbsp;&nbsp;");
                crEncountered = false;
                break;
            default:
                out.append(&in[i], 1);
                crEncountered = false;
                break;
        }
    }
    return out;
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
