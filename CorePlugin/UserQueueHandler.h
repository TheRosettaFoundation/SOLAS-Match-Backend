#ifndef USERQUEUEHANDLER_H
#define USERQUEUEHANDLER_H

#include <QObject>

#include "../PluginHandler/WorkerInterface.h"

class UserQueueHandler : public WorkerInterface
{
    Q_OBJECT
    Q_INTERFACES(WorkerInterface)

public:
    UserQueueHandler();
    void setThreadPool(QThreadPool *);
    bool isEnabled();

public slots:
    void run();
    void consumeFromQueue();

private:
    QThreadPool *mThreadPool;
};

#endif // USERQUEUEHANDLER_H
