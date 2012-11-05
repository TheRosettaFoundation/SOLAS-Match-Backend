#ifndef EMAILPLUGIN_H
#define EMAILPLUGIN_H

#include <AMQPcpp.h>
#include <QtPlugin>

#include "Smtp.h"
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
    void deleteSmtp();
    void run();

private:
    QThreadPool *mThreadPool;
    Smtp *smtp;

};

#endif // EMAILPLUGIN_H
