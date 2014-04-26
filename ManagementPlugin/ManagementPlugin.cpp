#include "ManagementPlugin.h"

#include <QSharedPointer>
#include <QTimer>

#include <QDebug>

#include "IRequestInterface.h"
#include "PluginActiveRequest.h"

#include "Common/ConfigParser.h"

#include "Common/MessagingClient.h"

Q_EXPORT_PLUGIN2(ManagementPlugin, ManagementPlugin)

ManagementPlugin::ManagementPlugin()
{
    ConfigParser settings;
    enabled = (QString::compare("y", settings.get("management.enabled")) == 0);
}

void ManagementPlugin::run()
{
    qDebug() << "ManagementPlugin::Starting new Thread " << this->thread()->currentThreadId();
    ConfigParser settings;
    QString exchange = settings.get("messaging.exchange");
    QString topic = "management.#";
    QString queue = "management_queue";
    MessagingClient *client;

    client = new MessagingClient();
    client->init();
    connect(client, SIGNAL(AMQPMessageReceived(AMQPMessage*)), this, SLOT(messageReveived(AMQPMessage*)));

    qDebug() << "ManagementPlugin::Now consuming from " << exchange << " exchange";
    client->declareQueue(exchange, topic, queue);

    QTimer *message_queue_read_timer = new QTimer();
    connect(message_queue_read_timer, SIGNAL(timeout()), client, SLOT(consumeFromQueue()));
    message_queue_read_timer->start(settings.get("messaging.poll_rate").toInt());

    QSharedPointer<IRequestInterface> request = QSharedPointer<IRequestInterface>(new PluginActiveRequest());
    request->run();
}

void ManagementPlugin::messageReveived(AMQPMessage *message)
{
    qDebug() << "ManagementPlugin::Received Message";

    AMQPQueue *messageQueue = message->getQueue();
    if(messageQueue != NULL)
    {
        messageQueue->Ack(message->getDeliveryTag());
    }

    //uint32_t length = 0;
    //QString message_body = message->getMessage(&length);
}

void ManagementPlugin::setThreadPool(QThreadPool *tp)
{
    this->mThreadPool = tp;
}

bool ManagementPlugin::isEnabled() const
{
    return enabled;
}

