#ifndef CALCULATEPROJECTDEADLINES_H
#define CALCULATEPROJECTDEADLINES_H

#include <QSharedPointer>
#include <AMQPcpp.h>

#include "PluginHandler/JobInterface.h"

class CalculateProjectDeadlines : public JobInterface
{
    Q_INTERFACES(JobInterface)

public:
    CalculateProjectDeadlines();
    ~CalculateProjectDeadlines();
    void run();
    void setAMQPMessage(AMQPMessage *message);

private:
    AMQPMessage *message;

};

#endif // CALCULATEPROJECTDEADLINES_H
