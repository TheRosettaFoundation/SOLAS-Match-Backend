#ifndef USERQUEUEHANDLER_H
#define USERQUEUEHANDLER_H

#include <QObject>
#include <QtPlugin>
#include <QThreadPool>

#include "PluginHandler/WorkerInterface.h"
#include "Common/MessagingClient.h"

#include "AMQPcpp.h"

class UserQueueHandler : public WorkerInterface
{
    Q_OBJECT
    Q_INTERFACES(WorkerInterface)

public:
    UserQueueHandler();
    void setThreadPool(QThreadPool *);
    void registerRequestTypes();
    bool isEnabled();

public slots:
    void run();
    void messageReceived(AMQPMessage *);
    void handleAMQPError(QString error);

private:
    QThreadPool *mThreadPool;
    MessagingClient *client;

};

#endif // USERQUEUEHANDLER_H
