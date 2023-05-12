#ifndef EMAILPLUGIN_H
#define EMAILPLUGIN_H

#include <AMQPcpp.h>
#include <QtPlugin>

#include "Smtp.h"
#include "../PluginHandler/WorkerInterface.h"

class EmailPlugin : public WorkerInterface
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID "org.therosettafoundation.solas" FILE "emailplugin.json")
    Q_INTERFACES(WorkerInterface)

public:
    EmailPlugin();
    void setThreadPool(QThreadPool *);
    bool isEnabled();

public slots:
    void messageReveived(AMQPMessage *message);
    void run();

private:
    void registerEmailTypes();
    QThreadPool *mThreadPool;
    bool enabled;
    Smtp *smtp;

};

#endif // EMAILPLUGIN_H
