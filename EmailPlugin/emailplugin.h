#ifndef EMAILPLUGIN_H
#define EMAILPLUGIN_H

#include "EmailPlugin_global.h"

#include <AMQPcpp.h>
#include <QtPlugin>

#include "../PluginHandler/WorkerInterface.h"

class EmailPlugin : public WorkerInterface
{
    Q_OBJECT
    Q_INTERFACES(WorkerInterface)

public:
    EmailPlugin();
    void setThreadPool(QThreadPool *);

public slots:
    void messageReveived(AMQPMessage *message);
    void run();

private:
    QThreadPool *mThreadPool;

};

#endif // EMAILPLUGIN_H
