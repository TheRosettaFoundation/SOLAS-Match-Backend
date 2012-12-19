#ifndef TIMEDTASKHANDLER_H
#define TIMEDTASKHANDLER_H

#include <QObject>
#include <AMQPcpp.h>
#include <QtPlugin>
#include <QThreadPool>

#include "PluginHandler/WorkerInterface.h"

class TimedTaskHandler : public WorkerInterface
{
    Q_OBJECT
    Q_INTERFACES(WorkerInterface)

public:
    TimedTaskHandler();
    void setThreadPool(QThreadPool *);
    bool isEnabled();

public slots:
    void messageReceived(AMQPMessage *message);
    void calculateScoreForAllUsers();
    void run();

private:
    QThreadPool *mThreadPool;
    bool enabled;

};

#endif // TIMEDTASKHANDLER_H
