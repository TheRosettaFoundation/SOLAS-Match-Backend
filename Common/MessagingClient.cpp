#include "MessagingClient.h"
#include "ConfigParser.h"

#include <QDebug>

MessagingClient::MessagingClient()
{
    qDebug() << "MessagingClient:;Creating Configuration Parser";
    ConfigParser mParser;
    this->hostname = mParser.get("messaging.host");
    this->port = mParser.get("messaging.port").toInt();
    this->user = mParser.get("messaging.mess_user");
    this->pass = mParser.get("messaging.mess_pass");
    this->vhost = mParser.get("messaging.virtualhost");
    this->finished = false;
}

bool MessagingClient::init()
{
    bool ret = this->openConnection();
    this->user = "";
    this->pass = "";
    return ret;
}

bool MessagingClient::openConnection()
{
    qDebug() << "MessagingClient::Connecting to RabbitMQ";
    bool ret = false;
    try {
        QString connectionString = this->pass+ ":" +
                this->user + "@" + this->hostname + ":" + QString::number(this->port) + "/";
        qDebug() << "Attempting connection string: " << connectionString;
        this->conn = new AMQP(connectionString.toStdString());
    } catch(AMQPException error) {
        qDebug() << "Error " << error.getReplyCode() << ": "
                 << QString::fromStdString(error.getMessage());
    }

    return ret;
}

void MessagingClient::declareQueue(QString exchange, QString topic, QString queue)
{
    mQueue = this->conn->createQueue(queue.toStdString());

    mQueue->Declare();
    mQueue->Bind(exchange.toStdString(), topic.toStdString());
}

void MessagingClient::consumeFromQueue()
{
    mQueue->Get();

    AMQPMessage *message = mQueue->getMessage();
    if(message->getMessageCount() > -1) {
        emit AMQPMessageReceived(message);
    }
}
