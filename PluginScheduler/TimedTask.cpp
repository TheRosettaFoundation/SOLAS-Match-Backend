#include "TimedTask.h"

#include <QDebug>

TimedTask::TimedTask()
{
    //Default Constructor
}

QTime TimedTask::getStartTime()
{
    return startTime;
}

QTime TimedTask::getInterval()
{
    return interval;
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

void TimedTask::setInterval(QTime time)
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

void TimedTask::printTask()
{
    qDebug() << "========== Printing Task ===========";
    qDebug() << "Sending " << message << " to " << exchange << " on topic " << topic
             << " every " << interval.toString() << " starting at " << startTime.toString();
    qDebug() << "====================================";
}
