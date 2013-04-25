#ifndef TASKQUEUEHANDLER_H
#define TASKQUEUEHANDLER_H

#include <QObject>
#include <QtPlugin>
#include <QThreadPool>

#include "PluginHandler/WorkerInterface.h"
#include "Common/MessagingClient.h"

#include "AMQPcpp.h"

class TaskQueueHandler : public WorkerInterface
{
    Q_OBJECT
    Q_INTERFACES(WorkerInterface)

public:
    TaskQueueHandler();
    void setThreadPool(QThreadPool *);
    bool isEnabled();

public slots:
    void run();
    void messageReceived(AMQPMessage *);
    void handleAMQPError(QString error);
    void calculateAllTasksScore();

private:
    QThreadPool *mThreadPool;
    MessagingClient *client;

};

#endif // TASKQUEUEHANDLER_H
