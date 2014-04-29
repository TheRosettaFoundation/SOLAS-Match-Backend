#ifndef COREPLUGIN_H
#define COREPLUGIN_H

#include <QObject>
#include <QtPlugin>
#include <QThreadPool>

#include "PluginHandler/WorkerInterface.h"

class CorePlugin : public WorkerInterface
{
    Q_OBJECT
    Q_INTERFACES(WorkerInterface)

public:
    CorePlugin();
    void setThreadPool(QThreadPool *);
    bool isEnabled() const;
    const std::string getPluginData() const;

public slots:
    void run();

private:
    QThreadPool *mThreadPool;
    bool enabled;

};

#endif // COREPLUGIN_H
