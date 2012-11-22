#ifndef USERTASKSCORECALCULATOR_H
#define USERTASKSCORECALCULATOR_H

#include <QObject>
#include <AMQPcpp.h>
#include <QtPlugin>
#include <QThreadPool>

#include "PluginHandler/WorkerInterface.h"

class UserTaskScoreCalculator : public WorkerInterface
{
    Q_OBJECT
    Q_INTERFACES(WorkerInterface)

public:
    UserTaskScoreCalculator();
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

#endif // USERTASKSCORECALCULATOR_H
