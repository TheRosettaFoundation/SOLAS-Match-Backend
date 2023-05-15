#ifndef PROJECTQUEUEHANDLER_H
#define PROJECTQUEUEHANDLER_H

#include <QObject>
#include <QtPlugin>
#include <QThreadPool>

#include "PluginHandler/WorkerInterface.h"

class ProjectQueueHandler : public WorkerInterface
{
    Q_OBJECT
    Q_INTERFACES(WorkerInterface)

public:
    ProjectQueueHandler();
    void setThreadPool(QThreadPool *);
    bool isEnabled();

public slots:
    void run();
    void consumeFromQueue();

private:
    QThreadPool *mThreadPool;
};

#endif // PROJECTQUEUEHANDLER_H
