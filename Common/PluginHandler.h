#ifndef PLUGINHANDLER_H
#define PLUGINHANDLER_H

#include <QMutex>
#include <QMap>
#include <QSharedPointer>

#include "../PluginHandler/WorkerInterface.h"

class PluginHandler
{
public:
    static QSharedPointer<PluginHandler> instance();

    void run();

    const WorkerInterface* getPlugin(QString name);

private:
    PluginHandler() {}

    PluginHandler(const PluginHandler &); // hide copy constructor
    PluginHandler& operator=(const PluginHandler &); // hide assign op
                                 // we leave just the declarations, so the compiler will warn us
                                 // if we try to use those two functions by accident

    static QSharedPointer<PluginHandler> m_Instance;

    QMap<QString, WorkerInterface*>* pluginMap;

};

#endif // PLUGINHANDLER_H
