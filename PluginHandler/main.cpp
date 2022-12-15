#include <QtCore/QCoreApplication>

#include <QDebug>
#include <QDateTime>
#include <QThreadPool>
#include <QThread>
#include <QFile>
#include <QTextStream>

#include "../Common/ConfigParser.h"

#include "PluginLoader.h"

QString logFile = "";

void myMessageHandler(QtMsgType type, const QMessageLogContext &context, const QString &msg)
{
    QString txt;
    QString time = QDateTime::currentDateTime().toString("dd/MM/yyyy hh:mm:ss:zzz");
    switch (type) {
        case QtDebugMsg:
            txt = QString("[%1] Debug: %2").arg(time, msg);
            break;
        case QtInfoMsg:
            txt = QString("[%1] Info: %2").arg(time, msg);
            break;
        case QtWarningMsg:
            txt = QString("[%1] Warning: %2").arg(time, msg);
            break;
        case QtCriticalMsg:
            txt = QString("[%1] Critical: %2").arg(time, msg);
            break;
        case QtFatalMsg:
            txt = QString("[%1] Fatal: %2").arg(time, msg);
            abort();
    }
    QFile outFile(logFile);
    if (outFile.open(QIODevice::WriteOnly | QIODevice::Append)) {
        QTextStream ts(&outFile);
        ts << txt << Qt::endl;
    } else {
        //Could not open file write to stdout instead
        outFile.open(stdout, QIODevice::WriteOnly);
        QTextStream ts(&outFile);
        ts << txt << Qt::endl;
    }
}

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    ConfigParser parser;
    logFile = parser.get("site.log");
    if (logFile != "") {
        qDebug() << "Redirecting output to " << logFile;
        qInstallMessageHandler(myMessageHandler);
    }

    QList<WorkerInterface *> *workers;
    PluginLoader mLoader = PluginLoader();

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
