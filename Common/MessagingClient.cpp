#include "MessagingClient.h"
#include "ConfigParser.h"

#include <QDebug>

MessagingClient::MessagingClient()
{
    ConfigParser mParser;
    this->hostname = mParser.get("messaging.host");
    this->port = mParser.get("messaging.port").toInt();
    this->user = mParser.get("messaging.mess_user");
    this->pass = mParser.get("messaging.mess_pass");
    this->vhost = mParser.get("messaging.virtualhost");
    this->finished = false;
    this->conn = NULL;
    this->mQueue = NULL;
    this->mExchange = NULL;
}

MessagingClient::~MessagingClient()
{
    delete conn;
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
    //qDebug() << "MessagingClient::Connecting to RabbitMQ";
    bool ret = false;
    try {
        QString connectionString = this->pass+ ":" +
                this->user + "@" + this->hostname + ":" + QString::number(this->port) + "/";
        this->conn = new AMQP(connectionString.toStdString());
    } catch(AMQPException error) {
        qDebug() << "Error " << error.getReplyCode() << ": "
                 << QString::fromStdString(error.getMessage());
    } catch (exception e) {
        qDebug() << "Unable to connect to rabbitMQ " << e.what();
    }

    return ret;
}

void MessagingClient::declareQueue(QString exchange, QString topic, QString queue)
{
    mQueue = this->conn->createQueue(queue.toStdString());

    mQueue->Declare();
    mQueue->Bind(exchange.toStdString(), topic.toStdString());
}

void MessagingClient::publish(QString exchange, QString topic, QString message)
{
    if(this->conn) {
        try {
            mExchange = this->conn->createExchange(exchange.toStdString());
            mExchange->Declare(exchange.toStdString(), "topic", AMQP_DURABLE);
            mExchange->Publish(message.toStdString(), topic.toStdString());
        } catch (AMQPException e) {
            qDebug() << "Caught exception";
        }
    } else {
        qDebug() << "Connection not initialized";
    }
}

void MessagingClient::consumeFromQueue()
{
    mQueue->Get();

    AMQPMessage *message = mQueue->getMessage();
    if(message->getMessageCount() > -1) {
        emit AMQPMessageReceived(message);
    }
}
