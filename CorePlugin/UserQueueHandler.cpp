#include "UserQueueHandler.h"

#include <QThread>
#include <QTimer>
#include <QDebug>

#include "UserJobs/TaskStreamNotificationHandler.h"
#include "UserJobs/StatisticsUpdate.h"

UserQueueHandler::UserQueueHandler()
{
    // Default Constructor
}

void UserQueueHandler::run()
{
    qDebug() << "Running UserQueueHandler on thread " << this->thread()->currentThreadId();
    QString exchange = "SOLAS_MATCH";
    QString topic = "users.#";
    QString queue = "CoreUsersQueue";

    client = new MessagingClient();
    client->init();
    connect(client, SIGNAL(AMQPMessageReceived(AMQPMessage*)), this, SLOT(messageReceived(AMQPMessage*)));
    connect(client, SIGNAL(AMQPError(QString)), this, SLOT(handleAMQPError(QString)));
    client->declareQueue(exchange, topic, queue);

    QTimer *message_queue_read_timer = new QTimer();
    connect(message_queue_read_timer, SIGNAL(timeout()), client, SLOT(consumeFromQueue()));
    message_queue_read_timer->start(50);
}

void UserQueueHandler::messageReceived(AMQPMessage *message)
{
    qDebug() << "UserQueueHandler: Message received";

    AMQPQueue *messageQueue = message->getQueue();
    if(messageQueue != NULL)
    {
        messageQueue->Ack(message->getDeliveryTag());
    }

    QRunnable *job = NULL;

    if(message->getRoutingKey() == "users.stream.notify") {
        job = new TaskStreamNotificationHandler(message);
    } else if(message->getRoutingKey() == "users.statistics.update") {
        job = new StatisticsUpdate(message);
    }

    if(job) {
        this->mThreadPool->start(job);
    } else {
        qDebug() << "Invalid routing key: " << QString::fromStdString(message->getRoutingKey());
    }
}

void UserQueueHandler::handleAMQPError(QString error)
{
    qDebug() << "UserQueueHandler: AMQPError: " << error;
}

void UserQueueHandler::setThreadPool(QThreadPool *tp)
{
    this->mThreadPool = tp;
}

bool UserQueueHandler::isEnabled()
{
    return true;
}
