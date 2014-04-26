#include "PluginLoader.h"

#include <QtCore/QCoreApplication>
#include <QDebug>
#include <QPluginLoader>
#include <QDir>

#include "Common/ConfigParser.h"

PluginLoader::PluginLoader()
{
    ConfigParser settings;
    plugins = new QMap<QString, WorkerInterface *>();
    threadPool = new QThreadPool();
    threadPool->setMaxThreadCount(settings.get("site.max_threads").toInt());
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
                worker->setThreadPool(this->getThreadPool());
                QString pluginName = filename.mid(3, filename.length() - 6);
                qDebug() << "PluginLoader::Adding plugin " << pluginName;
                plugins->insert(pluginName, worker);
            }
        } else {
            qDebug() << "PluginLoader::Failed to get object instance";
        }
    }
}

QMap<QString, WorkerInterface *> *PluginLoader::getPlugins()
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
