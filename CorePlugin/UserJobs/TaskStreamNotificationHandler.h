#ifndef USERSTREAMNOTIFICATIONHANDLER_H
#define USERSTREAMNOTIFICATIONHANDLER_H

#include <QObject>
#include <AMQPcpp.h>

#include "PluginHandler/JobInterface.h"

class TaskStreamNotificationHandler : public QObject, public JobInterface
{
    Q_INTERFACES(JobInterface)

public:
    TaskStreamNotificationHandler();
    TaskStreamNotificationHandler(AMQPMessage *);
    ~TaskStreamNotificationHandler();
    void run();

private:
    AMQPMessage *message;

};

#endif // USERSTREAMNOTIFICATIONHANDLER_H
