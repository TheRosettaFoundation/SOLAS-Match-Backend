#ifndef ORGCREATEDNOTIFICATIONS_H
#define ORGCREATEDNOTIFICATIONS_H

#include <QObject>
#include <AMQPcpp.h>

#include "PluginHandler/JobInterface.h"

class OrgCreatedNotifications : public JobInterface
{
    Q_INTERFACES(JobInterface)

public:
    OrgCreatedNotifications();
    void run();
    void setAMQPMessage(AMQPMessage *message);

private:
    AMQPMessage *message;

};

#endif // ORGCREATEDNOTIFICATIONS_H
