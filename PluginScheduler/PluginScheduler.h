#ifndef PLUGINSCHEDULER_H
#define PLUGINSCHEDULER_H

#include <QObject>
#include <AMQPcpp.h>
#include <QtPlugin>
#include <QThreadPool>

#include "PluginHandler/WorkerInterface.h"

class PluginScheduler : public WorkerInterface
{
    Q_OBJECT
    Q_INTERFACES(WorkerInterface)

public:
    PluginScheduler();
    void setThreadPool(QThreadPool *);
    bool isEnabled();

public slots:
    void run();

private:
    QThreadPool *mThreadPool;
    bool enabled;

};



#endif // PLUGINSCHEDULER_H
