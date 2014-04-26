#include "PluginActiveRequest.h"

#include <QDebug>

#include "../Common/PluginHandler.h"

#include "../PluginHandler/WorkerInterface.h"

PluginActiveRequest::PluginActiveRequest()
{
}

PluginActiveRequest::~PluginActiveRequest()
{
}

void PluginActiveRequest::run()
{
    QSharedPointer<PluginHandler> handler = PluginHandler::instance();
    const WorkerInterface* plugin = handler->getPlugin("CorePlugin");
    if (plugin->isEnabled())
    {
        qDebug() << "CorePlugin is enabled";
    }
    else
    {
        qDebug() << "CorePlugin is NOT enabled";
    }
}
