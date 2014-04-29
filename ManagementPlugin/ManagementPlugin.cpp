#include "ManagementPlugin.h"

#include <QSharedPointer>
#include <QTimer>

#include <QDebug>

#include "IRequestInterface.h"
#include "PluginActiveRequest.h"
#include "ListPluginsHandler.h"
#include "EmailCountRequest.h"

#include "Common/ConfigParser.h"
#include "Common/protobufs/management/ManagementRequest.pb.h"
#include "Common/protobufs/management/ServerResponse.pb.h"
#include "Common/protobufs/management/PluginEnabledRequest.pb.h"
#include "Common/protobufs/management/ListPluginsRequest.pb.h"
#include "Common/protobufs/management/EmailCountProto.pb.h"

Q_EXPORT_PLUGIN2(ManagementPlugin, ManagementPlugin)

ManagementPlugin::ManagementPlugin()
{
    ConfigParser settings;
    enabled = (QString::compare("y", settings.get("management.enabled")) == 0);
    client = new MessagingClient();
}

ManagementPlugin::~ManagementPlugin()
{
    delete client;
}

void ManagementPlugin::run()
{
    qDebug() << "ManagementPlugin::Starting new Thread " << this->thread()->currentThreadId();

    registerCustomTypes();

    ConfigParser settings;
    QString exchange = settings.get("messaging.exchange");
    QString topic = "management.#";
    QString queue = "management_queue";

    client->init();
    connect(client, SIGNAL(AMQPMessageReceived(AMQPMessage*)), this, SLOT(messageReveived(AMQPMessage*)));

    qDebug() << "ManagementPlugin::Now consuming from " << exchange << " exchange";
    client->declareQueue(exchange, topic, queue);

    QTimer *message_queue_read_timer = new QTimer();
    connect(message_queue_read_timer, SIGNAL(timeout()), client, SLOT(consumeFromQueue()));
    message_queue_read_timer->start(settings.get("messaging.poll_rate").toInt());
}

void ManagementPlugin::messageReveived(AMQPMessage *message)
{
    qDebug() << "ManagementPlugin::Received Message";

    AMQPQueue *messageQueue = message->getQueue();
    if(messageQueue != NULL)
    {
        messageQueue->Ack(message->getDeliveryTag());
    }

    uint32_t length = 0;
    QString message_body = message->getMessage(&length);

    ManagementRequest request;
    request.ParseFromString(message_body.toStdString());

    int classId = QMetaType::type(QString::fromStdString(request.class_name()).toLatin1());
    if (classId == 0) {
        qDebug() << "ManagementPlugin: Invalid proto type: " << QString::fromStdString(request.class_name());

        ServerResponse response;
        response.set_error_message("Invalid command: The server was not able to deserialize the request");
        client->publish(QString::fromStdString(request.response_exchange()), QString::fromStdString(request.response_topic()), QString::fromStdString(response.SerializeAsString()));
    } else {
        IRequestInterface* runnable = static_cast<IRequestInterface*>(QMetaType::construct(classId));
        runnable->setProtoBody(message_body);
        this->mThreadPool->start(runnable);
    }
}

void ManagementPlugin::registerCustomTypes()
{
    PluginEnabledRequest pluginEnabledRequest;
    qRegisterMetaType<PluginActiveRequest>(QString::fromStdString(pluginEnabledRequest.class_name()).toLatin1());
    ListPluginsRequest listPluginsRequest;
    qRegisterMetaType<ListPluginsHandler>(QString::fromStdString(listPluginsRequest.class_name()).toLatin1());
    EmailCountProto emailCountProto;
    qRegisterMetaType<EmailCountRequest>(QString::fromStdString(emailCountProto.class_name()).toLatin1());
}

void ManagementPlugin::setThreadPool(QThreadPool *tp)
{
    this->mThreadPool = tp;
}

bool ManagementPlugin::isEnabled() const
{
    return enabled;
}

const string ManagementPlugin::getPluginData() const
{
    return "";      // No data
}
