#include "TaskStreamNotificationHandler.h"

#include <QDebug>
#include <QThread>
#include <QUuid>
#include <QDateTime>

#include "Common/MySQLHandler.h"
#include "Common/MessagingClient.h"
#include "Common/DataAccessObjects/UserDao.h"
#include "Common/protobufs/emails/UserTaskStreamEmail.pb.h"

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
    qDebug() << "Starting new thread to send task stream notifications " << this->thread()->currentThreadId();
    QString exchange = "SOLAS_MATCH";
    QString topic = "email.user.task.stream";
    MySQLHandler *db = new MySQLHandler(QUuid::createUuid().toString());
    MessagingClient client;
    if(db->init()) {
        if(client.init()) {
            QList<int> userIds = UserDao::getUserIdsPendingTaskStreamNotification(db);
            foreach (int id, userIds) {
                QSharedPointer<UserTaskStreamEmail> request =
                        QSharedPointer<UserTaskStreamEmail>(new UserTaskStreamEmail());
                request->set_user_id(id);
                request->set_email_type(EmailMessage::UserTaskStreamEmail);
                QString body = QString::fromStdString(request->SerializeAsString());
                client.publish(exchange, topic, body);
            }
        } else {
            qDebug() << "Unable to connect to RabbitMQ. Check conf.ini for settings.";
        }
    } else {
        qDebug() << "Unable to connect to MySQL server. Check conf.ini for DB settings.";
    }

    delete db;
}
