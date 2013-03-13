#ifndef MESSAGINGCLIENT_H
#define MESSAGINGCLIENT_H

#include <QObject>
#include <AMQPcpp.h>
#include <QString>

class MessagingClient : public QObject
{
    Q_OBJECT
public:
    MessagingClient();
    ~MessagingClient();
    bool init();
    void declareQueue(QString exchange, QString topic, QString queue);
    void publish(QString exchange, QString topic, QString message);

public slots:
    void consumeFromQueue();

signals:
    void AMQPMessageReceived(AMQPMessage *message);
    void AMQPError(QString error);
    void AMQPCancel(AMQPMessage *message);

private:
    bool openConnection();
    bool finished;
    int port;
    QString hostname;
    QString user;
    QString pass;
    QString vhost;
    AMQP *conn;
    AMQPQueue *mQueue;
    AMQPExchange *mExchange;

};

#endif // MESSAGINGCLIENT_H
