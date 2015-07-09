#ifndef COREPLUGIN_H
#define COREPLUGIN_H

#include <QObject>
#include <QtPlugin>
#include <QThreadPool>

#include "PluginHandler/WorkerInterface.h"

class CorePlugin : public WorkerInterface
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID "org.therosettafoundation.solas" FILE "CorePlugin.json")
    Q_INTERFACES(WorkerInterface)

public:
    CorePlugin();
    void setThreadPool(QThreadPool *);
    bool isEnabled();

public slots:
    void run();

private:
    QThreadPool *mThreadPool;
    bool enabled;

};

#endif // COREPLUGIN_H
