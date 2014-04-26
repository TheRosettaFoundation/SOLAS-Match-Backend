#include "PluginHandler.h"

#include <QDebug>

#include "Common/ConfigParser.h"
#include "../PluginHandler/PluginLoader.h"

QSharedPointer<PluginHandler> PluginHandler::m_Instance;

QSharedPointer<PluginHandler> PluginHandler::instance()
{
    static QMutex mutex;
    if (m_Instance.isNull())
    {
        mutex.lock();

        if (m_Instance.isNull())
        {
            PluginHandler::m_Instance = QSharedPointer<PluginHandler>(new PluginHandler);
        }

        mutex.unlock();
    }

    return PluginHandler::m_Instance;
}

void PluginHandler::run()
{
    PluginLoader mLoader = PluginLoader();

    mLoader.loadPlugins();
    pluginMap = mLoader.getPlugins();

    QThread *thread;

    qDebug() << "Plugins Loaded: starting workers...";
    foreach(WorkerInterface * worker, *pluginMap) {
        if(worker->isEnabled()) {
            thread = new QThread();
            worker->connect(thread, SIGNAL(started()), SLOT(run()));
            worker->moveToThread(thread);
            thread->start();
        } else {
            qDebug() << "Worker is not enabled";
        }
    }
}

const WorkerInterface* PluginHandler::getPlugin(QString name)
{
    return pluginMap->value(name, NULL);
}
