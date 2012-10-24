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
    void run();
    void setThreadPool(QThreadPool *);

public slots:
    void messageReceived(AMQPMessage *message);
    void calculateScoreForAllUsers();

private:
    QThreadPool *mThreadPool;

};

#endif // USERTASKSCORECALCULATOR_H
