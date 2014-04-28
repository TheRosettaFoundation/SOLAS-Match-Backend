#include "ListPluginsHandler.h"

#include <QDebug>

#include "../Common/PluginHandler.h"
#include "../Common/MessagingClient.h"
#include "../Common/protobufs/management/ListPluginsRequest.pb.h"
#include "../Common/protobufs/management/ServerResponse.pb.h"

#include "../PluginHandler/WorkerInterface.h"


ListPluginsHandler::ListPluginsHandler()
{
}

ListPluginsHandler::~ListPluginsHandler()
{
}

void ListPluginsHandler::run()
{
    ListPluginsRequest request;
    request.ParseFromString(protoBody.toStdString());

    QSharedPointer<PluginHandler> pluginHandler = PluginHandler::instance();
    const QList<QString> plugins = pluginHandler->getPluginList();

    QString pluginList = "Plugins currently loaded:\n";
    foreach (QString plugin, plugins)
    {
        pluginList += "    " + plugin + "\n";
    }

    ServerResponse response;
    response.set_response_text(pluginList.toStdString());

    MessagingClient client;
    client.init();

    client.publish(
        QString::fromStdString(request.response_exchange()),
        QString::fromStdString(request.response_topic()),
        QString::fromStdString(response.SerializeAsString())
    );
}
