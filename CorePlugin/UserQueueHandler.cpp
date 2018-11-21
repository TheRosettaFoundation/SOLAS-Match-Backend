#include "UserQueueHandler.h"

#include <QThread>
#include <QTimer>
#include <QDebug>

#include "Common/ConfigParser.h"
#include "Common/protobufs/requests/RequestMessage.pb.h"
#include "Common/protobufs/requests/StatisticsUpdateRequest.pb.h"
#include "Common/protobufs/requests/UserTaskStreamNotificationRequest.pb.h"
#include "Common/protobufs/requests/OrgCreatedNotificationRequest.pb.h"
#include "Common/protobufs/notifications/TaskRevokedNotification.pb.h"

#include "UserJobs/TaskStreamNotificationHandler.h"
#include "UserJobs/StatisticsUpdate.h"
#include "UserJobs/OrgCreatedNotifications.h"
#include "UserJobs/TaskRevokedNotificationHandler.h"

#include "Common/protobufs/emails/JSON.h"

using namespace SolasMatch::Common::Protobufs::Requests;
using namespace SolasMatch::Common::Protobufs::Notifications;

UserQueueHandler::UserQueueHandler()
{
    // Default Constructor
}

void UserQueueHandler::run()
{
    qDebug() << "Running UserQueueHandler on thread " << this->thread()->currentThreadId();
    this->registerRequestTypes();
    ConfigParser settings;
    QString exchange = settings.get("messaging.exchange");
    QString topic = "users.#";
    QString queue = "CoreUsersQueue";

    client = new MessagingClient();
    client->init();
    connect(client, SIGNAL(AMQPMessageReceived(AMQPMessage*)), this, SLOT(messageReceived(AMQPMessage*)));
    connect(client, SIGNAL(AMQPError(QString)), this, SLOT(handleAMQPError(QString)));
    client->declareQueue(exchange, topic, queue);

    QTimer *message_queue_read_timer = new QTimer();
    connect(message_queue_read_timer, SIGNAL(timeout()), client, SLOT(consumeFromQueue()));
    message_queue_read_timer->start(settings.get("messaging.poll_rate").toInt());
}

void UserQueueHandler::messageReceived(AMQPMessage *message)
{
    qDebug() << "UserQueueHandler: Message received";

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
        qDebug() << "UserQueueHandler JSON: Invalid proto type: " << QString::fromStdString(requestMessage.class_name());
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
        qDebug() << "UserQueueHandler: Invalid proto type: " << QString::fromStdString(requestMessage.class_name());
    } else {
        JobInterface *runnable = static_cast<JobInterface *>(QMetaType::create(classId));
        runnable->setAMQPMessage(message);
        this->mThreadPool->start(runnable);
    }
  }
}

void UserQueueHandler::handleAMQPError(QString error)
{
    qDebug() << "UserQueueHandler: AMQPError: " << error;
}

void UserQueueHandler::setThreadPool(QThreadPool *tp)
{
    this->mThreadPool = tp;
}

bool UserQueueHandler::isEnabled()
{
    return true;
}

void UserQueueHandler::registerRequestTypes()
{
    StatisticsUpdateRequest statUpdate = StatisticsUpdateRequest();
    qRegisterMetaType<StatisticsUpdate>(QString::fromStdString(statUpdate.class_name()).toLatin1());
    UserTaskStreamNotificationRequest streamReq = UserTaskStreamNotificationRequest();
    qRegisterMetaType<TaskStreamNotificationHandler>(QString::fromStdString(streamReq.class_name()).toLatin1());
    OrgCreatedNotificationRequest orgCreated = OrgCreatedNotificationRequest();
    qRegisterMetaType<OrgCreatedNotifications>(QString::fromStdString(orgCreated.class_name()).toLatin1());
    TaskRevokedNotification taskRevoked = TaskRevokedNotification();
    qRegisterMetaType<TaskRevokedNotificationHandler>(QString::fromStdString(taskRevoked.class_name()).toLatin1());
}
