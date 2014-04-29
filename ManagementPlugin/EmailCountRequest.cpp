#include "EmailCountRequest.h"

#include "../Common/PluginHandler.h"
#include "../Common/MessagingClient.h"
#include "../Common/protobufs/management/EmailCountProto.pb.h"
#include "../Common/protobufs/management/ServerResponse.pb.h"
#include "../Common/protobufs/plugin_data/EmailPluginData.pb.h"

EmailCountRequest::EmailCountRequest()
{
}

EmailCountRequest::~EmailCountRequest()
{
}

void EmailCountRequest::run()
{
    EmailCountProto request;
    request.ParseFromString(protoBody.toStdString());

    ServerResponse response;

    QSharedPointer<PluginHandler> pluginHandler = PluginHandler::instance();
    const WorkerInterface* emailPlugin = pluginHandler->getPlugin("EmailPlugin");

    if (emailPlugin)
    {
        const std::string data = emailPlugin->getPluginData();

        EmailPluginData emailData;
        if (emailData.ParseFromString(data))
        {
            QString responseText;
            responseText.sprintf("There are currently %d pending emails.", emailData.pending_email_count());
            response.set_response_text(responseText.toStdString());
        }
        else
        {
            response.set_error_message("Error: Failed to parse email data");
        }
    }
    else
    {
        response.set_error_message("Error: Failed to find email plugin");
    }

    MessagingClient client;
    client.init();

    client.publish(
        QString::fromStdString(request.response_exchange()),
        QString::fromStdString(request.response_topic()),
        QString::fromStdString(response.SerializeAsString())
    );
}
