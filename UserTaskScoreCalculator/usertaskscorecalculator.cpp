#include "usertaskscorecalculator.h"

#include <QDebug>
#include <QThreadPool>
#include <QTimer>

#include "Common/MessagingClient.h"
#include "Common/ConfigParser.h"
#include "CalculateTaskScoreJob.h"

Q_EXPORT_PLUGIN2(UserTaskScoreCalculator, UserTaskScoreCalculator)

UserTaskScoreCalculator::UserTaskScoreCalculator()
{
    ConfigParser settings;
    enabled = (QString::compare("y", settings.get("TaskScoreCalculator.enabled")) == 0);
}

void UserTaskScoreCalculator::run()
{
    qDebug() << "UserTaskScoreCalculator::Starting new Thread " << this->thread()->currentThreadId();
    QString exchange = "SOLAS_MATCH";
    QString queue = "task_score_queue";
    MessagingClient *client;

    client = new MessagingClient();
    client->init();
    connect(client, SIGNAL(AMQPMessageReceived(AMQPMessage *)), this, SLOT(messageReceived(AMQPMessage *)));

    try {
        qDebug() << "UserTaskScoreCalculator::Now consuming from " << exchange << " exchange";
        client->declareQueue(exchange, "task.score", queue);

        QTimer *message_queue_read_timer = new QTimer();
        connect(message_queue_read_timer, SIGNAL(timeout()), client, SLOT(consumeFromQueue()));
        message_queue_read_timer->start(50);

        QTimer::singleShot(100, this, SLOT(calculateScoreForAllUsers()));   //Run on startup
    } catch(AMQPException e) {
        qDebug() << "ERROR: " << QString::fromStdString(e.getMessage());
    }
}

void UserTaskScoreCalculator::messageReceived(AMQPMessage *message)
{
    qDebug() << "UserTaskScoreCalc::Starting new thread to handle task";
    QRunnable *job = new CalculateTaskScore(message);
    this->mThreadPool->start(job);
}

void UserTaskScoreCalculator::calculateScoreForAllUsers()
{
    qDebug() << "UserTaskScoreCalc::Running hourly run through";
    QRunnable *job = new CalculateTaskScore();
    this->mThreadPool->start(job);
}

void UserTaskScoreCalculator::setThreadPool(QThreadPool *tp)
{
    this->mThreadPool = tp;
}

bool UserTaskScoreCalculator::isEnabled()
{
    return enabled;
}
