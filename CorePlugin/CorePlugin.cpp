#include "CorePlugin.h"

#include <QThread>
#include <QDebug>

#include "TaskQueueHandler.h"
#include "UserQueueHandler.h"
#include "ProjectQueueHandler.h"
#include "PootlePlugin.h"
#include "Common/ConfigParser.h"

Q_EXPORT_PLUGIN2(CorePlugin, CorePlugin)

CorePlugin::CorePlugin()
{
    ConfigParser settings;
    enabled = (QString::compare("y", settings.get("CorePlugin.enabled")) == 0);
}

void CorePlugin::run()
{
    qDebug() << "CorePlugin::Starting new Thread " << this->thread()->currentThreadId();
    TaskQueueHandler *taskListener = new TaskQueueHandler();
    taskListener->setThreadPool(this->mThreadPool);
    QThread *thread = new QThread();
    taskListener->connect(thread, SIGNAL(started()), SLOT(run()));
    taskListener->moveToThread(thread);
    thread->start();

    UserQueueHandler *userListener = new UserQueueHandler();
    userListener->setThreadPool(this->mThreadPool);
    thread = new QThread();
    userListener->connect(thread, SIGNAL(started()), SLOT(run()));
    userListener->moveToThread(thread);
    thread->start();

    ProjectQueueHandler *projectListener = new ProjectQueueHandler();
    projectListener->setThreadPool(this->mThreadPool);
    thread = new QThread();
    projectListener->connect(thread, SIGNAL(started()), SLOT(run()));
    projectListener->moveToThread(thread);
    thread->start();

    PootlePlugin *pootlePlugin = new PootlePlugin();
    pootlePlugin->setThreadPool(this->mThreadPool);
    thread = new QThread();
    pootlePlugin->connect(thread, SIGNAL(started()), SLOT(run()));
    pootlePlugin->moveToThread(thread);
    thread->start();
}

void CorePlugin::setThreadPool(QThreadPool *tp)
{
    this->mThreadPool = tp;
}

bool CorePlugin::isEnabled()
{
    return this->enabled;
}
