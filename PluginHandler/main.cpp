#include <QtCore/QCoreApplication>

#include <QDebug>
#include <QThreadPool>
#include <QThread>

#include "PluginLoader.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    QList<WorkerInterface *> *workers;
    PluginLoader mLoader;

    qDebug() << "Starting main thread" << a.thread()->currentThreadId();

    mLoader.loadPlugins();
    workers = mLoader.getPlugins();

    QThread *thread;

    qDebug() << "Plugins Loaded: starting workers...";
    foreach(WorkerInterface * worker, *workers) {
        thread = new QThread();
        worker->connect(thread, SIGNAL(started()), SLOT(run()));
        worker->moveToThread(thread);
        thread->start();
    }

    return a.exec();
}
