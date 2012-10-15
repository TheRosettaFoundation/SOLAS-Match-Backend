#include "usertaskscorecalculator.h"

#include <QDebug>
#include <QThreadPool>
#include <QTimer>

#include "Common/MessagingClient.h"
#include "CalculateTaskScoreJob.h"

Q_EXPORT_PLUGIN2(UserTaskScoreCalculator, UserTaskScoreCalculator)

UserTaskScoreCalculator::UserTaskScoreCalculator()
{
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
        qDebug() << "Now consuming from " << exchange << " exchange";
        client->declareQueue(exchange, "task.score", queue);
        QTimer *mTimer = new QTimer();
        connect(mTimer, SIGNAL(timeout()), client, SLOT(consumeFromQueue()));
        mTimer->start(50);
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

void UserTaskScoreCalculator::setThreadPool(QThreadPool *tp)
{
    this->mThreadPool = tp;
}
