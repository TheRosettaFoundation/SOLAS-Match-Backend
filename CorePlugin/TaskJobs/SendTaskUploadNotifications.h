#ifndef SENDTASKUPLOADNOTIFICATIONS_H
#define SENDTASKUPLOADNOTIFICATIONS_H

#include <AMQPcpp.h>
#include <QList>
#include <QSharedPointer>

#include "PluginHandler/JobInterface.h"
#include "Common/MySQLHandler.h"

class SendTaskUploadNotifications : public JobInterface
{
    Q_INTERFACES(JobInterface)

public:
    SendTaskUploadNotifications();
    void run();
    void setAMQPMessage(AMQPMessage *message);

private:
    AMQPMessage *message;

};

#endif // SENDTASKUPLOADNOTIFICATIONS_H
