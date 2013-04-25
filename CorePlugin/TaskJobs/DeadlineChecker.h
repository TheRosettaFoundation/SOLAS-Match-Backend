#ifndef DEADLINECHECKER_H
#define DEADLINECHECKER_H

#include <QObject>
#include <AMQPcpp.h>

#include "PluginHandler/JobInterface.h"
#include "Common/MySQLHandler.h"

class DeadlineChecker : public QObject, public JobInterface
{
    Q_INTERFACES(JobInterface)

public:
    DeadlineChecker();
    DeadlineChecker(AMQPMessage *);
    ~DeadlineChecker();
    void run();

private:
    AMQPMessage *message;

};

#endif // DEADLINECHECKER_H
