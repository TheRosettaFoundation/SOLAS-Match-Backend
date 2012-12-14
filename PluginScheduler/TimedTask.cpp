#include "TimedTask.h"

#include <QDebug>

TimedTask::TimedTask()
{

}

TimedTask::~TimedTask()
{
    //delete mTimer;
}

QTime TimedTask::getStartTime()
{
    return startTime;
}

int TimedTask::getIntervalInMSecs()
{
    int msecs = interval.days * 24 * 60 * 60 * 1000;
    msecs += interval.hours * 60 * 60 * 1000;
    msecs += interval.mins * 60 * 1000;
    msecs += interval.secs * 1000;
    return msecs;
}

QString TimedTask::getExchange()
{
    return exchange;
}

QString TimedTask::getTopic()
{
    return topic;
}

QString TimedTask::getMessage()
{
    return message;
}

void TimedTask::setStartTime(QTime time)
{
    startTime = time;
}

void TimedTask::setInterval(TimeInterval time)
{
    interval = time;
}

void TimedTask::setExchange(QString name)
{
    exchange = name;
}

void TimedTask::setTopic(QString name)
{
    topic = name;
}

void TimedTask::setMessage(QString mess)
{
    message = mess;
}

void TimedTask::processAndStartTimer()
{
    qDebug() << "TimedTask::Process and Start";
    emit processTask(QPointer<TimedTask>(this));

    mTimer = new QTimer();
    connect(mTimer, SIGNAL(timeout()), this, SLOT(triggerProcess()));
    mTimer->start(this->getIntervalInMSecs());
}

void TimedTask::triggerProcess()
{
    emit processTask(QPointer<TimedTask>(this));
}

void TimedTask::printTask()
{
    qDebug() << "========== Printing Task ===========";
    qDebug() << "Sending " << message << " to " << exchange << " on topic " << topic
             << " every " << interval.days << " day(s), " << interval.hours << " hour(s), "
             << interval.mins << " minute(s) and " << interval.secs << " second(s)"
             << " starting at " << startTime.toString();
    qDebug() << "====================================";
}
