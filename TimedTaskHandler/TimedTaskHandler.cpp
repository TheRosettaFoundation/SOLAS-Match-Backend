#include "TimedTaskHandler.h"

#include <QDebug>
#include <QThreadPool>
#include <QTimer>

#include "Common/MessagingClient.h"
#include "Common/ConfigParser.h"
#include "CalculateTaskScoreJob.h"

Q_EXPORT_PLUGIN2(TimedTaskHandler, TimedTaskHandler)

TimedTaskHandler::TimedTaskHandler()
{
    ConfigParser settings;
    enabled = (QString::compare("y", settings.get("TaskScoreCalculator.enabled")) == 0);
}

void TimedTaskHandler::run()
{
    qDebug() << "TimedTaskHandler::Starting new Thread " << this->thread()->currentThreadId();
    QString exchange = "SOLAS_MATCH";
    QString queue = "task_score_queue";
    MessagingClient *client;

    client = new MessagingClient();
    client->init();
    connect(client, SIGNAL(AMQPMessageReceived(AMQPMessage *)), this, SLOT(messageReceived(AMQPMessage *)));

    try {
        qDebug() << "TimedTaskHandler::Now consuming from " << exchange << " exchange";
        client->declareQueue(exchange, "task.score", queue);

        QTimer *message_queue_read_timer = new QTimer();
        connect(message_queue_read_timer, SIGNAL(timeout()), client, SLOT(consumeFromQueue()));
        message_queue_read_timer->start(50);

        QTimer::singleShot(100, this, SLOT(calculateScoreForAllUsers()));   //Run on startup
    } catch(AMQPException e) {
        qDebug() << "ERROR: " << QString::fromStdString(e.getMessage());
    }
}

void TimedTaskHandler::messageReceived(AMQPMessage *message)
{
    qDebug() << "UserTaskScoreCalc::Starting new thread to handle task";
    QRunnable *job = new CalculateTaskScore(message);
    this->mThreadPool->start(job);
}

void TimedTaskHandler::calculateScoreForAllUsers()
{
    qDebug() << "UserTaskScoreCalc::Running hourly run through";
    QRunnable *job = new CalculateTaskScore();
    this->mThreadPool->start(job);
}

void TimedTaskHandler::setThreadPool(QThreadPool *tp)
{
    this->mThreadPool = tp;
}

bool TimedTaskHandler::isEnabled()
{
    return enabled;
}
