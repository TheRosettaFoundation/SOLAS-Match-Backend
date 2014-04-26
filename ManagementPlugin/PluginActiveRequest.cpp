#include "PluginActiveRequest.h"

#include <QDebug>

#include "../Common/PluginHandler.h"
#include "../Common/MessagingClient.h"
#include "../Common/protobufs/management/PluginEnabledRequest.pb.h"

#include "../PluginHandler/WorkerInterface.h"

PluginActiveRequest::PluginActiveRequest()
{
}

PluginActiveRequest::~PluginActiveRequest()
{
}

void PluginActiveRequest::run()
{
    PluginEnabledRequest request;
    request.ParseFromString(protoBody.toStdString());

    QSharedPointer<PluginHandler> handler = PluginHandler::instance();
    const WorkerInterface* plugin = handler->getPlugin(QString::fromStdString(request.plugin_name()));

    if (plugin->isEnabled())
    {
        qDebug() << "CorePlugin is enabled";
    }
    else
    {
        qDebug() << "CorePlugin is NOT enabled";
    }
}
