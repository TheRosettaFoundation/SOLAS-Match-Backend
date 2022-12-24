#include "MessagingClient.h"
#include "ConfigParser.h"

#include <QDebug>
#include <QFileInfo>

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
    bool ret = false;
    try {
        //QString connectionString = this->pass+ ":" +
        //        this->user + "@" + this->hostname + ":" + QString::number(this->port) + "/";
        QString connectionString = this->pass+ ":" +
                this->user + "@" + this->hostname + ":" + QString::number(this->port);
        // Trailing slash implies an empty vhost, we want a default vhost ("/"), so remove the /
        // Note although AMQP follows that part of the spec, it does not follow other parts (e.g. it reverses username:password)!
        // see https://github.com/TheRosettaFoundation/amqpcpp.git src/AMQP.cpp
        // spec: https://www.rabbitmq.com/uri-spec.html

        this->conn = new AMQP(connectionString.toStdString());
        ret = true;
    } catch(const AMQPException& error) {
        qDebug() << "Error " << error.getReplyCode() << ": "
                 << QString::fromStdString(error.getMessage());
    } catch (const std::exception& e) {
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

void MessagingClient::publish(QString exchange, QString topic, std::string message)
{
    //qDebug() << "Publishing to exchnage " << exchange << " on " << topic;
    if(this->conn) {
        try {
            mExchange = this->conn->createExchange(exchange.toStdString());
            mExchange->Declare(exchange.toStdString(), "topic", AMQP_DURABLE);
            mExchange->Publish(message, topic.toStdString());
        } catch (const AMQPException& e) {
            qDebug() << "Caught exception " << topic << " : " << QString::fromStdString(e.getMessage());
        }
    } else {
        qDebug() << "Connection not initialized";
    }
}

void MessagingClient::republish(AMQPMessage *message)
{
    uint32_t length = 0;
    char *body = message->getMessage(&length);
    this->publish(QString::fromStdString(message->getExchange()),
                  QString::fromStdString(message->getRoutingKey()),
                  std::string(body, length));
}

void MessagingClient::consumeFromQueue()
{
  if (!QFileInfo::exists("/repo/SOLAS-Match-Backend/STOP_consumeFromQueue")) {
    try {
        mQueue->Get();

        AMQPMessage *message = mQueue->getMessage();
        if(message && message->getMessageCount() > -1) {
            emit AMQPMessageReceived(message);
        }
    } catch (const AMQPException& e) {
        qDebug() << "ERROR: Consuming from Queue";
        emit AMQPError(QString::fromStdString(e.getMessage()));
    }
  }
}
