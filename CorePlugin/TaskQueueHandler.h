#ifndef TASKQUEUEHANDLER_H
#define TASKQUEUEHANDLER_H

#include <QObject>

#include "../PluginHandler/WorkerInterface.h"

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
    void consumeFromQueue();

private:
    QThreadPool *mThreadPool;
};

#endif // TASKQUEUEHANDLER_H
