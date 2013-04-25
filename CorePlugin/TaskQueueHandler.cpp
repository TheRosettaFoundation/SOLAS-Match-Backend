#include "TaskQueueHandler.h"

#include <QThread>
#include <QTimer>
#include <QDebug>

#include "TaskJobs/CalculateTaskScore.h"
#include "TaskJobs/DeadlineChecker.h"

TaskQueueHandler::TaskQueueHandler()
{
    qDebug() << "Constructing TaskQueueHandler";
}

void TaskQueueHandler::run()
{
    qDebug() << "Running TaskQueueHandler on thread " << this->thread()->currentThreadId();
    QString exchange = "SOLAS_MATCH";
    QString queue = "CoreTaskQueue";
    QString topic = "tasks.#";

    client = new MessagingClient();
    client->init();
    connect(client, SIGNAL(AMQPMessageReceived(AMQPMessage*)), this, SLOT(messageReceived(AMQPMessage*)));
    connect(client, SIGNAL(AMQPError(QString)), this, SLOT(handleAMQPError(QString)));

    qDebug() << "Connecting to exchange " << exchange;
    client->declareQueue(exchange, topic, queue);

    QTimer *message_queue_read_timer = new QTimer();
    connect(message_queue_read_timer, SIGNAL(timeout()), client, SLOT(consumeFromQueue()));
    message_queue_read_timer->start(50);

    QTimer::singleShot(100, this, SLOT(calculateAllTasksScore()));   //Run on startup
}

void TaskQueueHandler::messageReceived(AMQPMessage *message)
{
    qDebug() << "TaskQueueHandler: Received Message";

    AMQPQueue *messageQueue = message->getQueue();
    if(messageQueue != NULL)
    {
        messageQueue->Ack(message->getDeliveryTag());
    }

    QRunnable *job = NULL;

    if(message->getRoutingKey() == "tasks.score") {
        job = new CalculateTaskScore(message);
    } else if(message->getRoutingKey() == "tasks.deadline.check") {
        job = new DeadlineChecker(message);
    }

    if(job) {
        this->mThreadPool->start(job);
    } else {
        qDebug() << "Invalid routing key: " << QString::fromStdString(message->getRoutingKey());
    }
}

void TaskQueueHandler::calculateAllTasksScore()
{
    qDebug() << "Calculating user task scores";
    QRunnable *job = new CalculateTaskScore();
    this->mThreadPool->start(job);
}

void TaskQueueHandler::setThreadPool(QThreadPool *tp)
{
    this->mThreadPool = tp;
}

bool TaskQueueHandler::isEnabled()
{
    return true;
}
