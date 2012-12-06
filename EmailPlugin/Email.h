#ifndef EMAIL_H
#define EMAIL_H

#include <QString>
#include <QStringList>

class Email
{
public:
    Email(QString to = "", QString from = "", QString subject = "", QString body = "");
    QStringList getRecipients();
    QString getSender();
    QString getSubject();
    QString getBody();
    void addRecipient(QString to);
    void setSender(QString from);
    void setSubject(QString sub);
    void setBody(QString body);
    void printEmail();

private:
    QStringList recipient;
    QString sender;
    QString subject;
    QString body;

};

#endif // EMAIL_H
