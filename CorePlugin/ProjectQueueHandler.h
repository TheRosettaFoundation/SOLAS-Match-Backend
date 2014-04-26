#ifndef PROJECTQUEUEHANDLER_H
#define PROJECTQUEUEHANDLER_H

#include <QObject>
#include <QtPlugin>
#include <QThreadPool>

#include "PluginHandler/WorkerInterface.h"
#include "Common/MessagingClient.h"

#include "AMQPcpp.h"

class ProjectQueueHandler : public WorkerInterface
{
    Q_OBJECT
    Q_INTERFACES(WorkerInterface)

public:
    ProjectQueueHandler();
    void setThreadPool(QThreadPool *);
    bool isEnabled() const;

public slots:
    void run();
    void messageReceived(AMQPMessage *message);
    void handleAMQPError(QString error);

private:
    void registerRequestTypes();
    QThreadPool *mThreadPool;
    MessagingClient *client;

};

#endif // PROJECTQUEUEHANDLER_H
