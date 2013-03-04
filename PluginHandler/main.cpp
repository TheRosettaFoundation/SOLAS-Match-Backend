#include <QtCore/QCoreApplication>

#include <QDebug>
#include <QThreadPool>
#include <QThread>
#include <QFile>
#include <QTextStream>

#include "../Common/ConfigParser.h"

#include "PluginLoader.h"

QString logFile = "";

void myMessageHandler(QtMsgType type, const char *msg)
{
    QString txt;
    switch (type) {
        case QtDebugMsg:
            txt = QString("Debug: %1").arg(msg);
            break;
        case QtWarningMsg:
            txt = QString("Warning: %1").arg(msg);
            break;
        case QtCriticalMsg:
            txt = QString("Critical: %1").arg(msg);
            break;
        case QtFatalMsg:
            txt = QString("Fatal: %1").arg(msg);
            abort();
    }
    QFile outFile(logFile);
    if (outFile.open(QIODevice::WriteOnly | QIODevice::Append)) {
        QTextStream ts(&outFile);
        ts << txt << endl;
    } else {
        //Could not open file write to stdout instead
        outFile.open(stdout, QIODevice::WriteOnly);
        QTextStream ts(&outFile);
        ts << txt << endl;
    }
}

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    ConfigParser parser;
    logFile = parser.get("site.log");
    if (logFile != "") {
        qDebug() << "Redirecting output to " << logFile;
        qInstallMsgHandler(myMessageHandler);
    }

    QList<WorkerInterface *> *workers;
    PluginLoader mLoader;

    qDebug() << "Starting main thread" << a.thread()->currentThreadId();

    mLoader.loadPlugins();
    workers = mLoader.getPlugins();

    QThread *thread;

    qDebug() << "Plugins Loaded: starting workers...";
    foreach(WorkerInterface * worker, *workers) {
        if(worker->isEnabled()) {
            thread = new QThread();
            worker->connect(thread, SIGNAL(started()), SLOT(run()));
            worker->moveToThread(thread);
            thread->start();
        } else {
            qDebug() << "Worker is not enabled";
        }
    }

    return a.exec();
}
