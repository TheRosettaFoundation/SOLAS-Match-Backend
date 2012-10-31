#ifndef WORKERINTERFACE_H
#define WORKERINTERFACE_H

#include <QRunnable>
#include <QThreadPool>

class WorkerInterface : public QObject
{
public:
    virtual ~WorkerInterface() {}
    virtual void setThreadPool(QThreadPool *) = 0;

public slots:
    virtual void run() = 0;

};

#define WorkerInterface_iid "solas.match.worker.interface/0.1"

Q_DECLARE_INTERFACE(WorkerInterface, WorkerInterface_iid)

#endif // WORKERINTERFACE_H
