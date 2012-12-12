#ifndef TIMEDTASK_H
#define TIMEDTASK_H

#include <QTime>

class TimedTask
{
public:
    TimedTask();
    QTime getStartTime();
    QTime getInterval();
    QString getExchange();
    QString getTopic();
    QString getMessage();
    void setStartTime(QTime time);
    void setInterval(QTime time);
    void setExchange(QString name);
    void setTopic(QString name);
    void setMessage(QString mess);
    void printTask();

private:
    QTime startTime;
    QTime interval;
    QString exchange;
    QString topic;
    QString message;

};

#endif // TIMEDTASK_H
