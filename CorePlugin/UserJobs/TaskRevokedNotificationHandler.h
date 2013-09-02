#ifndef TASKREVOKEDNOTIFICATIONHANDLER_H
#define TASKREVOKEDNOTIFICATIONHANDLER_H

#include <QObject>
#include <AMQPcpp.h>

#include "PluginHandler/JobInterface.h"

class TaskRevokedNotificationHandler : public JobInterface
{
    Q_INTERFACES(JobInterface)

public:
    TaskRevokedNotificationHandler();
    TaskRevokedNotificationHandler(AMQPMessage *);
    ~TaskRevokedNotificationHandler();
    void run();
    void setAMQPMessage(AMQPMessage *message);

private:
    AMQPMessage *message;

};

#endif // TASKREVOKEDNOTIFICATIONHANDLER_H
