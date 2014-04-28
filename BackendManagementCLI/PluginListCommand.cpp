#include "PluginListCommand.h"

#include "Common/ConfigParser.h"
#include "Common/protobufs/management/ListPluginsRequest.pb.h"
#include "Common/protobufs/management/ServerResponse.pb.h"

PluginListCommand::PluginListCommand() :
    messagingClient(0)
{
    message_queue_read_timer = new QTimer(this);
}

PluginListCommand::~PluginListCommand()
{
    if (messagingClient)
    {
        delete messagingClient;
    }
    if (message_queue_read_timer)
    {
        delete message_queue_read_timer;
    }
}

void PluginListCommand::printHelp(QString appName)
{
    qDebug("%s --list-plugins", appName.toStdString().c_str());
    qDebug("    This command shows a list of all plugins registered with the system\n");
}

bool PluginListCommand::isRequested(QStringList args)
{
    bool requested = false;
    if (args.length() == 2 && args.at(1) == "--list-plugins")
    {
        messagingClient = new MessagingClient();
        messagingClient->init();
        connect(messagingClient, SIGNAL(AMQPMessageReceived(AMQPMessage*)), this, SLOT(receivedResponse(AMQPMessage*)));
        connect(messagingClient, SIGNAL(AMQPCancel(AMQPMessage*)), this, SLOT(responseCanceled(AMQPMessage*)));
        connect(messagingClient, SIGNAL(AMQPError(QString)), this, SLOT(responseCanceled(QString)));

        requested = true;
    }
    return requested;
}

void PluginListCommand::execute()
{
    ConfigParser settings;
    QString exchange = settings.get("management_client.exchange");
    QString topic = settings.get("management_client.topic");
    QString queue = settings.get("management_client.queue");
    messagingClient->declareQueue(exchange, topic, queue);

    connect(message_queue_read_timer, SIGNAL(timeout()), messagingClient, SLOT(consumeFromQueue()));
    message_queue_read_timer->start(settings.get("messaging.poll_rate").toInt());

    ListPluginsRequest request;
    request.set_class_name(request.class_name());
    request.set_response_exchange(exchange.toStdString());
    request.set_response_topic("management_client.list.plugins");
    messagingClient->publish(exchange, "management.list.plugins", QString::fromStdString(request.SerializeAsString()));
}

void PluginListCommand::receivedResponse(AMQPMessage *message)
{
    AMQPQueue *messageQueue = message->getQueue();
    if(messageQueue != NULL)
    {
        messageQueue->Ack(message->getDeliveryTag());
    }

    uint32_t length = 0;
    QString message_body = message->getMessage(&length);

    ServerResponse response;
    response.ParseFromString(message_body.toStdString());

    QString responseMessage;
    if (response.error_message() == "")
    {
        responseMessage = QString::fromStdString(response.response_text());
    }
    else
    {
        responseMessage = QString::fromStdString(response.error_message());
    }
    emit finished(responseMessage);
}

void PluginListCommand::responseCanceled(AMQPMessage *message)
{
    Q_UNUSED(message);
    emit finished("Response Canceled");
}

void PluginListCommand::responseCanceled(QString error)
{
    emit finished("Request failed: " + error);
}
