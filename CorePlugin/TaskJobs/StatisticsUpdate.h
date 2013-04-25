#ifndef STATISTICSUPDATE_H
#define STATISTICSUPDATE_H

#include <QObject>
#include <AMQPcpp.h>

#include "PluginHandler/JobInterface.h"
#include "Common/MySQLHandler.h"

class StatisticsUpdate : public QObject, public JobInterface
{
    Q_INTERFACES(JobInterface)

public:
    StatisticsUpdate();
    StatisticsUpdate(AMQPMessage *);
    ~StatisticsUpdate();
    void run();

private:
    AMQPMessage *message;
};

#endif // STATISTICSUPDATE_H
