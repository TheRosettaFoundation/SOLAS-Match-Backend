#include "PluginEnabledCommand.h"

#include "Common/ConfigParser.h"
#include "Common/protobufs/management/PluginEnabledRequest.pb.h"

#include <QTimer>
#include <QDebug>

PluginEnabledCommand::PluginEnabledCommand() :
    pluginName(""),
    messagingClient(0),
    message_queue_read_timer(0)
{
}

PluginEnabledCommand::~PluginEnabledCommand()
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

void PluginEnabledCommand::printHelp(QString appName)
{
    qDebug("%s --plugin-enabled <plugin-name>", appName.toStdString().c_str());
    qDebug("    This command determines if the specified plugin has been enabled");
    qDebug("    <plugin-name> is the name of the plugin being checked\n");
}

bool PluginEnabledCommand::isRequested(QStringList args)
{
    bool requested = false;
    if (args.length() == 3 && args.at(1) == "--plugin-enabled")
    {
        pluginName = args.at(2);

        messagingClient = new MessagingClient();
        messagingClient->init();
        connect(messagingClient, SIGNAL(AMQPMessageReceived(AMQPMessage*)), this, SLOT(receivedResponse(AMQPMessage*)));
        connect(messagingClient, SIGNAL(AMQPCancel(AMQPMessage*)), this, SLOT(responseCanceled(AMQPMessage*)));
        connect(messagingClient, SIGNAL(AMQPError(QString)), this, SLOT(responseCanceled(QString)));

        requested = true;
    }
    return requested;
}

void PluginEnabledCommand::execute()
{
    ConfigParser parser = ConfigParser();
    QString exchange = parser.get("management_client.exchange");
    QString topic = parser.get("management_client.topic");
    QString queue = "PluginEnabledCommandQueue";
    messagingClient->declareQueue(exchange, topic, queue);

    message_queue_read_timer = new QTimer();
    connect(message_queue_read_timer, SIGNAL(timeout()), messagingClient, SLOT(consumeFromQueue()));
    message_queue_read_timer->start(parser.get("messaging.poll_rate").toInt());

    PluginEnabledRequest request;
    request.set_class_name(request.class_name());
    request.set_response_exchange(exchange.toStdString());
    request.set_response_topic(topic.toStdString());
    request.set_plugin_name(pluginName.toStdString());
    messagingClient->publish(parser.get("messaging.exchange"), "management.plugin.enabled", QString::fromStdString(request.SerializeAsString()));
}

void PluginEnabledCommand::receivedResponse(AMQPMessage *message)
{
    Q_UNUSED(message);
    emit finished("Received Response");
}

void PluginEnabledCommand::responseCanceled(AMQPMessage *message)
{
    Q_UNUSED(message);
    emit finished("Response Canceled");
}

void PluginEnabledCommand::responseCanceled(QString error)
{
    emit finished("Request failed: " + error);
}
