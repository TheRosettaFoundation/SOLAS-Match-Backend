#include "EmailCountCommand.h"

#include "Common/ConfigParser.h"
#include "Common/protobufs/management/EmailCountProto.pb.h"
#include "Common/protobufs/management/ServerResponse.pb.h"

#include <QDebug>

EmailCountCommand::EmailCountCommand()
{
    messagingClient = new MessagingClient();
    message_queue_read_timer = new QTimer();
}

EmailCountCommand::~EmailCountCommand()
{
    delete messagingClient;
    delete message_queue_read_timer;
}

void EmailCountCommand::printHelp(QString appName)
{
    qDebug("%s --email-count", appName.toStdString().c_str());
    qDebug("    Display the number of currently pending emails\n");
}

bool EmailCountCommand::isRequested(QStringList args)
{
    bool requested = false;
    if (args.length() == 2 && args.at(1) == "--email-count")
    {
        requested = true;

        messagingClient->init();
        connect(messagingClient, SIGNAL(AMQPMessageReceived(AMQPMessage*)), this, SLOT(receivedResponse(AMQPMessage*)));
        connect(messagingClient, SIGNAL(AMQPCancel(AMQPMessage*)), this, SLOT(responseCanceled(AMQPMessage*)));
        connect(messagingClient, SIGNAL(AMQPError(QString)), this, SLOT(responseCanceled(QString)));
    }
    return requested;
}

void EmailCountCommand::execute()
{
    ConfigParser settings;
    QString exchange = settings.get("management_client.exchange");
    QString topic = settings.get("management_client.topic");
    QString queue = settings.get("management_client.queue");
    messagingClient->declareQueue(exchange, topic, queue);

    connect(message_queue_read_timer, SIGNAL(timeout()), messagingClient, SLOT(consumeFromQueue()));
    message_queue_read_timer->start(settings.get("messaging.poll_rate").toInt());

    EmailCountProto request;
    request.set_class_name(request.class_name());
    request.set_response_exchange(exchange.toStdString());
    request.set_response_topic("management_client.email.count");

    messagingClient->publish(exchange, "management.email.count", QString::fromStdString(request.SerializeAsString()));
}

void EmailCountCommand::receivedResponse(AMQPMessage *message)
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

void EmailCountCommand::responseCanceled(AMQPMessage *message)
{
    AMQPQueue *messageQueue = message->getQueue();
    if(messageQueue != NULL)
    {
        messageQueue->Ack(message->getDeliveryTag());
    }

    emit finished("Response Canceled");
}

void EmailCountCommand::responseCanceled(QString error)
{
    emit finished("Request failed: " + error);
}
