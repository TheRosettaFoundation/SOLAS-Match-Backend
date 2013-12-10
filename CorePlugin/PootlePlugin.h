#ifndef POOTLEPLUGIN_H
#define POOTLEPLUGIN_H

#include <QObject>
#include <QtPlugin>
#include <QThreadPool>
#include <QSharedPointer>
#include <QFileSystemWatcher>

#include "PluginHandler/WorkerInterface.h"

class PootlePlugin : public WorkerInterface
{
    Q_OBJECT
    Q_INTERFACES(WorkerInterface)

public:
    PootlePlugin();
    void setThreadPool(QThreadPool *);
    bool isEnabled();

public slots:
    void run();
    void directoryChanged(QString location);

private:
    QSharedPointer<QFileSystemWatcher> fsWatcher;
    QThreadPool *mThreadPool;

};

#endif // POOTLEPLUGIN_H
