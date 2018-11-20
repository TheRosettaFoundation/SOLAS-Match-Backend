#include "ProjectQueueHandler.h"

#include <QThread>
#include <QTimer>
#include <QDebug>

#include "Common/ConfigParser.h"
#include "Common/protobufs/requests/RequestMessage.pb.h"
#include "Common/protobufs/requests/CalculateProjectDeadlinesRequest.pb.h"

#include "ProjectJobs/CalculateProjectDeadlines.h"

#include "Common/protobufs/emails/JSON.h"

using namespace SolasMatch::Common::Protobufs::Requests;

ProjectQueueHandler::ProjectQueueHandler()
{
    // Default Constructor
}

void ProjectQueueHandler::run()
{
    qDebug() << "Running ProjectQueueHandler on thread " << this->thread()->currentThreadId();
    this->registerRequestTypes();
    ConfigParser settings;
    QString exchange = "SOLAS_MATCH";
    QString queue = "CoreProjectQueue";
    QString topic = "projects.#";

    client = new MessagingClient();
    client->init();
    connect(client, SIGNAL(AMQPMessageReceived(AMQPMessage*)), this, SLOT(messageReceived(AMQPMessage*)));
    connect(client, SIGNAL(AMQPError(QString)), this, SLOT(handleAMQPError(QString)));
    client->declareQueue(exchange, topic, queue);

    QTimer *message_queue_read_timer = new QTimer();
    connect(message_queue_read_timer, SIGNAL(timeout()), client, SLOT(consumeFromQueue()));
    message_queue_read_timer->start(settings.get("messaging.poll_rate").toInt());
}

void ProjectQueueHandler::messageReceived(AMQPMessage *message)
{
    qDebug() << "ProjectQueueHandler: Received Message";

    AMQPQueue *messageQueue = message->getQueue();
    if(messageQueue != NULL)
    {
        messageQueue->Ack(message->getDeliveryTag());
    }

    uint32_t length = 0;
    char *body = message->getMessage(&length);

    SolasMatch::Common::Protobufs::Emails::JSON requestMessage;
    requestMessage.ParseFromString(std::string(body, length));

    int classId = QMetaType::type(QString::fromStdString(requestMessage.class_name()).toLatin1());
    if (classId == 0) {
        qDebug() << "ProjectQueueHandler: Invalid proto type: " << QString::fromStdString(requestMessage.class_name());
    } else {
        JobInterface *runnable = static_cast<JobInterface *>(QMetaType::create(classId));
        runnable->setAMQPMessage(message);
        this->mThreadPool->start(runnable);
    }
}

void ProjectQueueHandler::registerRequestTypes()
{
    CalculateProjectDeadlinesRequest projDeadlines = CalculateProjectDeadlinesRequest();
    qRegisterMetaType<CalculateProjectDeadlines>(QString::fromStdString(projDeadlines.class_name()).toLatin1());
}

void ProjectQueueHandler::setThreadPool(QThreadPool *tp)
{
    this->mThreadPool = tp;
}

bool ProjectQueueHandler::isEnabled()
{
    return true;
}
