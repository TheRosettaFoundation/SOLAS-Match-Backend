#ifndef MANAGEMENTPLUGIN_H
#define MANAGEMENTPLUGIN_H

#include "../Common/MessagingClient.h"

#include "../PluginHandler/WorkerInterface.h"

#include <AMQPcpp.h>
#include <QtPlugin>

class ManagementPlugin : public WorkerInterface
{
    Q_OBJECT
    Q_INTERFACES(WorkerInterface)

public:
    ManagementPlugin();
    virtual ~ManagementPlugin();
    void setThreadPool(QThreadPool *);
    bool isEnabled() const;
    const std::string getPluginData() const;

public slots:
    void messageReveived(AMQPMessage *message);
    void run();

private:
    void registerCustomTypes();

    QThreadPool *mThreadPool;
    MessagingClient *client;
    bool enabled;

};

#endif // MANAGEMENTPLUGIN_H
