#ifndef TIMEDTASKHANDLER_H
#define TIMEDTASKHANDLER_H

#include <QObject>
#include <AMQPcpp.h>
#include <QtPlugin>
#include <QThreadPool>
#include "Common/MessagingClient.h"

#include "PluginHandler/WorkerInterface.h"

class TimedTaskHandler : public WorkerInterface
{
    Q_OBJECT
    Q_INTERFACES(WorkerInterface)

public:
    TimedTaskHandler();
    void setThreadPool(QThreadPool *);
    bool isEnabled();

public slots:
    void messageReceived(AMQPMessage *message);
    void calculateScoreForAllUsers();
    void handleAMQPError(QString error);
    void run();

private:
    void setupConnection();
    QThreadPool *mThreadPool;
    bool enabled;
    MessagingClient *client;

};

#endif // TIMEDTASKHANDLER_H
