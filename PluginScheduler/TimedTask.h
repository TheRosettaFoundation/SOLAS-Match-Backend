#ifndef TIMEDTASK_H
#define TIMEDTASK_H

#include <QObject>
#include <QTime>
#include <QPointer>
#include <QTimer>

class TimedTask : public QObject
{
    Q_OBJECT
public:
    TimedTask();
    ~TimedTask();
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

public slots:
    void processAndStartTimer();
    void triggerProcess();

signals:
    void processTask(QPointer<TimedTask>);

private:
    QTime startTime;
    QTime interval;
    QString exchange;
    QString topic;
    QString message;
    QTimer *mTimer;

};

#endif // TIMEDTASK_H
