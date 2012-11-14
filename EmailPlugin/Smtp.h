#ifndef SMTP_H
#define SMTP_H

#include <QtDebug>
#include <QString>
#include <QObject>

#include <qxt/QxtNetwork/qxtsmtp.h>
#include <qxt/QxtNetwork/qxtmailmessage.h>

#include "Email.h"

class Smtp : public QObject
{
    Q_OBJECT

public:
    Smtp();
    ~Smtp();
    void init();
    void send(Email *email);

signals:
    void complete();

private slots:
    void connected();
    void connectionFailed();
    void authenticated();
    void authenticationFailed();
    void disconnected();
    void mailFailed(int mailID, int errorCode);
    void mailSent(int mailID);
    void senderRejected(int mailID, QString address);
    void recipientRejected(int mailID, QString address);
    void finished();

private:
    QxtSmtp *smtp;
    QString host;
    int port;
    bool isConnected;

};

#endif // SMTP_H
