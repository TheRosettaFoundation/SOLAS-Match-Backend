#ifndef PLUGINLOADER_H
#define PLUGINLOADER_H

#include <QObject>
#include <QMap>
#include <QRunnable>
#include <QThreadPool>

#include "WorkerInterface.h"

class PluginLoader
{
public:
    PluginLoader();
    void loadPlugins();
    QMap<QString, WorkerInterface *> *getPlugins();
    void addJobToThreadPool(QRunnable *job);
    QThreadPool *getThreadPool();

private:
    QMap<QString, WorkerInterface *> *plugins;
    QThreadPool *threadPool;

};

#endif // PLUGINLOADER_H
