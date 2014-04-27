#include "PluginActiveRequest.h"

#include <QDebug>

#include "../Common/PluginHandler.h"
#include "../Common/MessagingClient.h"
#include "../Common/protobufs/management/PluginEnabledRequest.pb.h"
#include "../Common/protobufs/management/ServerResponse.pb.h"

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

    ServerResponse response;
    if (plugin)
    {
        if (plugin->isEnabled())
        {
            response.set_response_text("Plugin " + request.plugin_name() + " is enabled");
        }
        else
        {
            response.set_response_text("Plugin " + request.plugin_name() + " is not enabled");
        }
    }
    else
    {
        response.set_error_message("No plugin with name " + request.plugin_name() + " was found");
    }

    MessagingClient client;
    client.init();

    client.publish(
        QString::fromStdString(request.response_exchange()),
        QString::fromStdString(request.response_topic()),
        QString::fromStdString(response.SerializeAsString())
    );
}
