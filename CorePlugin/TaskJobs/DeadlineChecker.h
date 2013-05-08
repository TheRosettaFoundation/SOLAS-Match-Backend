#ifndef DEADLINECHECKER_H
#define DEADLINECHECKER_H

#include <QObject>
#include <AMQPcpp.h>

#include "PluginHandler/JobInterface.h"
#include "Common/MySQLHandler.h"

class DeadlineChecker : public JobInterface
{
    Q_INTERFACES(JobInterface)

public:
    DeadlineChecker();
    DeadlineChecker(AMQPMessage *);
    ~DeadlineChecker();
    void run();
    void setAMQPMessage(AMQPMessage *message);

private:
    AMQPMessage *message;

};

#endif // DEADLINECHECKER_H
