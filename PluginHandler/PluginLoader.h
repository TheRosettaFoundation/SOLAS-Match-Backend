#ifndef PLUGINLOADER_H
#define PLUGINLOADER_H

#include <QObject>
#include <QList>
#include <QRunnable>
#include <QThreadPool>

#include "WorkerInterface.h"

class PluginLoader
{
public:
    PluginLoader();
    void loadPlugins();
    QList<WorkerInterface *> *getPlugins();
    void addJobToThreadPool(QRunnable *job);
    QThreadPool *getThreadPool();

private:
    QList<WorkerInterface *> *plugins;
    QThreadPool *threadPool;

};

#endif // PLUGINLOADER_H
