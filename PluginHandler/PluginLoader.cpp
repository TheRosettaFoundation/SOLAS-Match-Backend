#include "PluginLoader.h"

#include <QtCore/QCoreApplication>
#include <QDebug>
#include <QPluginLoader>
#include <QDir>

PluginLoader::PluginLoader()
{
    plugins = new QList<WorkerInterface *>();
    threadPool = new QThreadPool();
    threadPool->setMaxThreadCount(25);
}

void PluginLoader::loadPlugins()
{
    QDir pluginsDir(qApp->applicationDirPath());
#if defined(Q_OS_WIN)
    if (pluginsDir.dirName().toLower() == "debug" || pluginsDir.dirName().toLower() == "release")
        pluginsDir.cdUp();
#elif defined(Q_OS_MAC)
    if (pluginsDir.dirName() == "MacOS") {
        pluginsDir.cdUp();
        pluginsDir.cdUp();
        pluginsDir.cdUp();
    }
#endif
    pluginsDir.cdUp();
    pluginsDir.cd("plugins");
    qDebug() << "PluginLoader::Loading plugins from directory: " << pluginsDir.absolutePath();
    foreach(QString filename, pluginsDir.entryList(QDir::Files)) {
        qDebug() << "PluginLoader::Found file " << filename;
        QPluginLoader pluginLoader(pluginsDir.absoluteFilePath(filename));
        QObject *plugin = pluginLoader.instance();
        if(plugin) {
            WorkerInterface *worker = qobject_cast<WorkerInterface *>(plugin);
            if(worker) {
                qDebug() << "PluginLoader::Adding plugin " << filename;
                worker->setThreadPool(this->getThreadPool());
                plugins->append(worker);
            }
        } else {
            qDebug() << "PluginLoader::Failed to get object instance";
        }
    }
}

QList<WorkerInterface *> *PluginLoader::getPlugins()
{
    return plugins;
}

QThreadPool *PluginLoader::getThreadPool()
{
    return threadPool;
}

void PluginLoader::addJobToThreadPool(QRunnable *job)
{
    this->threadPool->start(job);
}
