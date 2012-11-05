#ifndef EMAIL_H
#define EMAIL_H

#include <QString>

class Email
{
public:
    Email(QString to = "", QString from = "", QString subject = "", QString body = "");
    QString getRecipient();
    QString getSender();
    QString getSubject();
    QString getBody();
    void setRecipient(QString to);
    void setSender(QString from);
    void setSubject(QString sub);
    void setBody(QString body);

private:
    QString recipient;
    QString sender;
    QString subject;
    QString body;

};

#endif // EMAIL_H
