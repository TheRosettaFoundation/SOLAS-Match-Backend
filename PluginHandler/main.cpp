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

    mLoader.loadPlugins();
    workers = mLoader.getPlugins();

    QThread *thread;

    qDebug() << "Plugins Loaded: starting workers...";
    foreach(WorkerInterface * worker, *workers) {
        thread = new QThread();
        worker->moveToThread(thread);
        thread->start();
        worker->run();
    }

    return a.exec();
}
