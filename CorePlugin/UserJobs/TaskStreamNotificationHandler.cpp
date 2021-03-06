#include "TaskStreamNotificationHandler.h"

#include <QDebug>
#include <QThread>

#include "Common/MySQLHandler.h"
#include "Common/MessagingClient.h"
#include "Common/ConfigParser.h"
#include "Common/DataAccessObjects/UserDao.h"
#include "Common/protobufs/emails/UserTaskStreamEmail.pb.h"

using namespace SolasMatch::Common::Protobufs::Emails;

TaskStreamNotificationHandler::TaskStreamNotificationHandler()
{
    message = NULL;
}

TaskStreamNotificationHandler::TaskStreamNotificationHandler(AMQPMessage *mess)
{
    message = mess;
}

TaskStreamNotificationHandler::~TaskStreamNotificationHandler()
{
}

void TaskStreamNotificationHandler::run()
{
    qDebug() << "Starting new thread to send task stream notifications";
    ConfigParser settings;
    QString exchange = settings.get("messaging.exchange");
    QString topic = "email.user.task.stream";
    QSharedPointer<MySQLHandler> db = MySQLHandler::getInstance();
    MessagingClient client;
    if(client.init()) {
        QList<int> userIds = UserDao::getUserIdsPendingTaskStreamNotification(db);
        foreach (int id, userIds) {
            QSharedPointer<UserTaskStreamEmail> request =
                    QSharedPointer<UserTaskStreamEmail>(new UserTaskStreamEmail());
            request->set_user_id(id);
            request->set_email_type(EmailMessage::UserTaskStreamEmail);
            std::string body = request->SerializeAsString();
            client.publish(exchange, topic, body);
        }
    } else {
        qDebug() << "Unable to connect to RabbitMQ. Check conf.ini for settings.";
    }
}

void TaskStreamNotificationHandler::setAMQPMessage(AMQPMessage *message)
{
    this->message = message;
}
