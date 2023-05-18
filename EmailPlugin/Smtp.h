#ifndef SMTP_H
#define SMTP_H

#include <QtDebug>
#include <QString>
#include <QObject>
#include <QSharedPointer>
#include <QQueue>
#include <QCryptographicHash>

#include "qxtsmtp.h"
#include "qxtmailmessage.h"

class Smtp : public QObject
{
    Q_OBJECT

public:
    Smtp();
    ~Smtp();
    void init();

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

    void checkEmailQueue();

private:
    int send(QMap<QString, QVariant>);
    QxtSmtp *smtp;
    QString host;
    int port;
    bool isConnected;
    bool busy;
    int  reconnect_count;
    bool test;
    QString only_send;
    QList<QByteArray> *mail_text_hashes;
    unsigned int count_checkEmailQueue;
};

#endif // SMTP_H
