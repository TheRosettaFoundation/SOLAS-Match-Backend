#ifndef POOTLEPLUGIN_H
#define POOTLEPLUGIN_H

#include <QFile>
#include <QObject>
#include <QtPlugin>
#include <QThreadPool>
#include <QStringList>
#include <QSharedPointer>
#include <QFileSystemWatcher>
#include <QtNetwork/QNetworkAccessManager>

#include "PluginHandler/WorkerInterface.h"

class PootlePlugin : public WorkerInterface
{
    Q_OBJECT
    Q_INTERFACES(WorkerInterface)

public:
    PootlePlugin();
    void setThreadPool(QThreadPool *);
    bool isEnabled();

public slots:
    void run();
    void directoryChanged(QString location);
    void processDirectory();
    void apiRequestFinished(QNetworkReply*);

private:
    void processMetaFile(QFile *file, QString location);
    void uploadOutputFile(QString fileDirectory);
    int getTaskIdFromPath(QString path);
    bool removeDir(QString);
    QSharedPointer<QFileSystemWatcher> fsWatcher;
    QThreadPool *mThreadPool;
    QStringList dirsToBeProcessed;
    QNetworkAccessManager *apiClient;

};

#endif // POOTLEPLUGIN_H
