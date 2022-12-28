#include "TaskQueueHandler.h"

#include <QThread>
#include <QTimer>
#include <QDebug>

#include "Common/ConfigParser.h"
#include "Common/protobufs/requests/RequestMessage.pb.h"
#include "Common/protobufs/requests/DeadlineCheckRequest.pb.h"
#include "Common/protobufs/requests/UserTaskScoreRequest.pb.h"
#include "Common/protobufs/requests/TaskUploadNotificationRequest.pb.h"

#include "TaskJobs/CalculateTaskScore.h"
#include "TaskJobs/DeadlineChecker.h"
#include "TaskJobs/SendTaskUploadNotifications.h"

#include "Common/protobufs/emails/JSON.h"

using namespace SolasMatch::Common::Protobufs::Requests;

TaskQueueHandler::TaskQueueHandler()
{
    // Default Constructor
}

void TaskQueueHandler::run()
{
    qDebug() << "Running TaskQueueHandler on thread " << this->thread()->currentThreadId();
    this->registerRequestTypes();
    ConfigParser settings;
    QString exchange = settings.get("messaging.exchange");
    QString queue = "CoreTaskQueue";
    QString topic = "tasks.#";

    client = new MessagingClient();
    client->init();
    connect(client, SIGNAL(AMQPMessageReceived(AMQPMessage*)), this, SLOT(messageReceived(AMQPMessage*)));
    connect(client, SIGNAL(AMQPError(QString)), this, SLOT(handleAMQPError(QString)));

    qDebug() << "Connecting to exchange " << exchange;
    client->declareQueue(exchange, topic, queue);

    QTimer *message_queue_read_timer = new QTimer();
    connect(message_queue_read_timer, SIGNAL(timeout()), client, SLOT(consumeFromQueue()));
    message_queue_read_timer->start(settings.get("messaging.poll_rate").toInt());

    // QTimer::singleShot(1000, this, SLOT(calculateAllTasksScore()));   //Run on startup
}

void TaskQueueHandler::messageReceived(AMQPMessage *message)
{
    qDebug() << "TaskQueueHandler: Received Message";

    AMQPQueue *messageQueue = message->getQueue();
    if(messageQueue != NULL)
    {
        messageQueue->Ack(message->getDeliveryTag());
    }

    uint32_t length = 0;
    char *body = message->getMessage(&length);

  if (SolasMatch::Common::Protobufs::Emails::JSON::isJSON(std::string(body, length))) {
    SolasMatch::Common::Protobufs::Emails::JSON requestMessage;
    requestMessage.ParseFromString(std::string(body, length));

    int classId = QMetaType::type(QString::fromStdString(requestMessage.class_name()).toLatin1());
    if (classId == 0) {
        qDebug() << "TaskQueueHandler JSON: Invalid proto type: " << QString::fromStdString(requestMessage.class_name());
    } else {
        JobInterface *runnable = static_cast<JobInterface *>(QMetaType::create(classId));
        runnable->setAMQPMessage(message);
        this->mThreadPool->start(runnable);
    }
  } else {
    RequestMessage requestMessage;
    requestMessage.ParseFromString(std::string(body, length));

    int classId = QMetaType::type(QString::fromStdString(requestMessage.class_name()).toLatin1());
    if (classId == 0) {
        qDebug() << "TaskQueueHandler: Invalid proto type: " << QString::fromStdString(requestMessage.class_name());
    } else {
        JobInterface *runnable = static_cast<JobInterface *>(QMetaType::create(classId));
        runnable->setAMQPMessage(message);
        this->mThreadPool->start(runnable);
    }
  }
}

void TaskQueueHandler::handleAMQPError(QString error)
{
    qDebug() << "TaskQueueHandler: AMQPError: " << error;
}

void TaskQueueHandler::registerRequestTypes()
{
    UserTaskScoreRequest scoreReq = UserTaskScoreRequest();
    qRegisterMetaType<CalculateTaskScore>(QString::fromStdString(scoreReq.class_name()).toLatin1());
    DeadlineCheckRequest deadlineReq = DeadlineCheckRequest();
    qRegisterMetaType<DeadlineChecker>(QString::fromStdString(deadlineReq.class_name()).toLatin1());
    TaskUploadNotificationRequest uploadRequest = TaskUploadNotificationRequest();
    qRegisterMetaType<SendTaskUploadNotifications>(QString::fromStdString(uploadRequest.class_name()).toLatin1());
}

void TaskQueueHandler::calculateAllTasksScore()
{
    qDebug() << "Calculating user task scores";
    QRunnable *job = new CalculateTaskScore();
    this->mThreadPool->start(job);
}

void TaskQueueHandler::setThreadPool(QThreadPool *tp)
{
    this->mThreadPool = tp;
}

bool TaskQueueHandler::isEnabled()
{
    return true;
}
