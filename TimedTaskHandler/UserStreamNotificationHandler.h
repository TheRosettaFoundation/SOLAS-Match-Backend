#ifndef USERSTREAMNOTIFICATIONHANDLER_H
#define USERSTREAMNOTIFICATIONHANDLER_H

#include <QObject>
#include <AMQPcpp.h>

#include "PluginHandler/JobInterface.h"

class UserStreamNotificationHandler : public QObject, public JobInterface
{
    Q_INTERFACES(JobInterface)

public:
    UserStreamNotificationHandler();
    UserStreamNotificationHandler(AMQPMessage *);
    ~UserStreamNotificationHandler();
    void run();

private:
    AMQPMessage *message;

};

#endif // USERSTREAMNOTIFICATIONHANDLER_H
