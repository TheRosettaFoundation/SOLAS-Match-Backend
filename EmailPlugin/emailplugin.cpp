#include "emailplugin.h"

#include <QDebug>
#include <QTimer>

#include "Smtp.h"

#include "../Common/MessagingClient.h"

Q_EXPORT_PLUGIN2(EmailPlugin, EmailPlugin)

EmailPlugin::EmailPlugin()
{
}

void EmailPlugin::run()
{
    qDebug() << "EmailPlugin::Starting new Thread " << this->thread()->currentThreadId();
    QString exchange = "SOLAS_MATCH";
    QString topic = "email.#";
    QString queue = "email_queue";
    MessagingClient *client;

    client = new MessagingClient();
    client->init();
    connect(client, SIGNAL(AMQPMessageReceived(AMQPMessage*)), this, SLOT(messageReveived(AMQPMessage*)));

    try {
        qDebug() << "EmailPlugin::Now consuming from " << exchange << " exchange";
        client->declareQueue(exchange, topic, queue);

        QTimer *message_queue_read_timer = new QTimer();
        connect(message_queue_read_timer, SIGNAL(timeout()), client, SLOT(consumeFromQueue()));
        message_queue_read_timer->start(50);

        Smtp *email = new Smtp("david.ocarroll@ul.ie", "spaceindaver0@gmail.com",
                               "Test Email", "A sample email to test");
        delete email;
    } catch(AMQPException e) {
        qDebug() << "ERROR: " << QString::fromStdString(e.getMessage());
    }
}

void EmailPlugin::messageReveived(AMQPMessage *message)
{
    uint32_t length = 0;
    qDebug() << "Received Message: " << message->getMessage(&length);
}

void EmailPlugin::setThreadPool(QThreadPool *tp)
{
    this->mThreadPool = tp;
}
