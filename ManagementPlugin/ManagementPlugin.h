#ifndef MANAGEMENTPLUGIN_H
#define MANAGEMENTPLUGIN_H

#include <AMQPcpp.h>
#include <QtPlugin>

#include "../PluginHandler/WorkerInterface.h"

class ManagementPlugin : public WorkerInterface
{
    Q_OBJECT
    Q_INTERFACES(WorkerInterface)

public:
    ManagementPlugin();
    void setThreadPool(QThreadPool *);
    bool isEnabled() const;

public slots:
    void messageReveived(AMQPMessage *message);
    void run();

private:
    QThreadPool *mThreadPool;
    bool enabled;

};

#endif // MANAGEMENTPLUGIN_H
