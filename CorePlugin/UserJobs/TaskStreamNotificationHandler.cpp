#include "TaskStreamNotificationHandler.h"

#include <QDebug>
#include <QThread>

#include "Common/MySQLHandler.h"
#include "Common/MessagingClient.h"
#include "Common/ConfigParser.h"
#include "Common/DataAccessObjects/UserDao.h"
#include "Common/protobufs/emails/UserTaskStreamEmail.pb.h"
#include "Common/Definitions.h"
#include "Common/protobufs/models/UserTaskStreamNotification.pb.h"

#include <QDateTime>
//#include <QRandomGenerator>

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
        QString sentDateTime = QDateTime::currentDateTime().toString("yyyy-MM-dd HH:mm:ss");
        QList<int> full_list_user_ids = UserDao::getUserIdsPendingTaskStreamNotification(db);
        QList<int> userIds = QList<int>(); // This will contain the cut down list of user_id(s) which will actually be sent emails
        qDebug() << "full_list_user_ids.count(): " << QString::number(full_list_user_ids.count());
        foreach (int user_id, full_list_user_ids) {
            bool sendEmail = true;
            QList<QSharedPointer<Task> > userTasks;
            QSharedPointer<UserTaskStreamNotification> notifData = UserDao::getUserTaskStreamNotification(db, user_id);
            if (!notifData.isNull() ) {
                if (notifData->strict()) {
                    userTasks = UserDao::getUserTopTasks(db, user_id, true, 25);
                } else {
                    userTasks = UserDao::getUserTopTasks(db, user_id, false, 25);
                }
                if (userTasks.count() < 1) {
                    sendEmail = false;
                    // qDebug() << "TaskStreamNotificationHandler: Failed to generate task stream email: No tasks found for user " << QString::number(user_id);
                }
            } else {
                sendEmail = false;
            }

            if (sendEmail) {
                int tasks_within_cutoff = 0;
                foreach (QSharedPointer<Task> task, userTasks) {
                    QDateTime deadline_DT = QDateTime::fromString(QString::fromStdString(task->deadline()), "yyyy-MM-ddTHH:mm:ss.zzz");
                    if (deadline_DT > QDateTime::currentDateTimeUtc().addMonths(-settings.get("mail.task_stream_cutoff_months").toInt())) { // Only notify about tasks with deadline within last (3) months
                        tasks_within_cutoff++;
                    }
                }
                if (tasks_within_cutoff > 0) {
                    userIds.append(user_id); // Really send an email to this user_id
                } else {
                    // qDebug() << "TaskStreamNotificationHandler: No tasks within cutoff for user " << QString::number(user_id);
                    sendEmail = false;
                }
            }

            if (!sendEmail) {
                if (UserDao::taskStreamNotificationSent(db, user_id, sentDateTime)) {
                    // qDebug() << "TaskStreamNotificationHandler: Updated last sent date for user id " << QString::number(user_id);
                } else {
                    qDebug() << "TaskStreamNotificationHandler: Failed to update last sent date for user id " << QString::number(user_id);
                }
            }
        }
        int count = userIds.count();
        int max_allowed = 8000; // per hour
        if (count < max_allowed) max_allowed = count;
        if (max_allowed > 0) {
int random = rand()%max_allowed;
//        int random = QRandomGenerator::global()->bounded(max_allowed); // Pick max_allowed elements starting at a random element (circulating back to start, if necessary)
            qDebug() << "count, max_allowed, random: " << QString::number(count) << ", " << QString::number(max_allowed) << ", " << QString::number(random);
            int i = 0;
            foreach (int id, userIds) {
                if (((i >= random) && (i < random + max_allowed)) || ((i >= (random - count)) && (i < random + max_allowed - count))) {
                    QSharedPointer<UserTaskStreamEmail> request = QSharedPointer<UserTaskStreamEmail>(new UserTaskStreamEmail());
                    request->set_user_id(id);
                    request->set_email_type(EmailMessage::UserTaskStreamEmail);
                    std::string body = request->SerializeAsString();
                    client.publish(exchange, topic, body);
                } else {
                    if (UserDao::taskStreamNotificationSent(db, id, sentDateTime)) {
                        // qDebug() << "TaskStreamNotificationHandler: Updated last sent date for user id " << QString::number(id);
                    } else {
                        qDebug() << "TaskStreamNotificationHandler: Failed to update last sent date for user id " << QString::number(id);
                    }
                    qDebug() << "TaskStreamNotificationHandler: Discarded user id " << QString::number(id);
                }
                i++;
            }
        }
    } else {
        qDebug() << "Unable to connect to RabbitMQ. Check conf.ini for settings.";
    }
}

void TaskStreamNotificationHandler::setAMQPMessage(AMQPMessage *message)
{
    this->message = message;
}
