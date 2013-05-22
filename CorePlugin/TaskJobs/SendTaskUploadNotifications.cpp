#include "SendTaskUploadNotifications.h"

#include <QDebug>

#include "Common/protobufs/requests/TaskUploadNotificationRequest.pb.h"

#include "Common/protobufs/models/Task.pb.h"
#include "Common/protobufs/models/User.pb.h"

#include "Common/protobufs/emails/TrackedTaskUploaded.pb.h"
#include "Common/protobufs/emails/TrackedTaskSourceUpdated.pb.h"
#include "Common/protobufs/emails/ClaimedTaskSourceUpdated.pb.h"
#include "Common/protobufs/emails/ClaimedTaskUploaded.pb.h"

#include "Common/DataAccessObjects/TaskDao.h"

#include "Common/MySQLHandler.h"
#include "Common/MessagingClient.h"

SendTaskUploadNotifications::SendTaskUploadNotifications()
{
    //Default Constructor
}

void SendTaskUploadNotifications::run()
{
    qDebug() << "Starting new thread to send task upload notifications";
    QString exchange = "SOLAS_MATCH";
    QString topic = "email";
    uint32_t length = 0;
    char *body = this->message->getMessage(&length);

    if (length > 0) {
        TaskUploadNotificationRequest request;
        request.ParseFromString(body);

        QSharedPointer<MySQLHandler> db = MySQLHandler::getInstance();
        QSharedPointer<Task> task = TaskDao::getTask(db, request.task_id());

        if (!task.isNull()) {
            QList<QSharedPointer<User> > users = TaskDao::getSubscribedUsers(db, task->id());
            QSharedPointer<User> translator = TaskDao::getTaskTranslator(db, task->id());

            QString body = "";
            MessagingClient publisher;
            if (publisher.init()) {
                if (request.file_version() == 0) {
                    foreach (QSharedPointer<User> user, users) {
                        TrackedTaskSourceUpdated trackedUpdate;
                        trackedUpdate.set_email_type(trackedUpdate.email_type());
                        trackedUpdate.set_task_id(task->id());
                        trackedUpdate.set_user_id(user->id());
                        if (!translator.isNull()) {
                            trackedUpdate.set_translator_id(translator->id());
                        }
                        body = QString::fromStdString(trackedUpdate.SerializeAsString());
                        publisher.publish(exchange, topic, body);
                    }

                    if (!translator.isNull()) {
                        ClaimedTaskSourceUpdated claimedUpdate;
                        claimedUpdate.set_email_type(claimedUpdate.email_type());
                        claimedUpdate.set_task_id(task->id());
                        claimedUpdate.set_user_id(translator->id());
                        body = QString::fromStdString(claimedUpdate.SerializeAsString());
                        publisher.publish(exchange, topic, body);
                    }
                } else {
                    foreach (QSharedPointer<User> user, users) {
                        TrackedTaskUploaded trackedUpload;
                        trackedUpload.set_email_type(trackedUpload.email_type());
                        trackedUpload.set_task_id(task->id());
                        trackedUpload.set_translator_id(translator->id());
                        trackedUpload.set_user_id(user->id());
                        body = QString::fromStdString(trackedUpload.SerializeAsString());
                        publisher.publish(exchange, topic, body);
                    }

                    ClaimedTaskUploaded claimedUpload;
                    claimedUpload.set_email_type(claimedUpload.email_type());
                    claimedUpload.set_task_id(task->id());
                    claimedUpload.set_user_id(translator->id());
                    body = QString::fromStdString(claimedUpload.SerializeAsString());
                    publisher.publish(exchange, topic, body);
                }
            } else {
                qDebug() << "SendTaskUploadNotifications: Failed to initialise messaging client";
            }
        } else {
            qDebug() << "SendTaskUploadNotifications: Unable to find relevant data in the DB, "
                     << "Searched for task ID " << QString::number(request.task_id());
        }
    } else {
        qDebug() << "SendTaskUploadNotifications: AMQPMessage body is empty";
    }
}

void SendTaskUploadNotifications::setAMQPMessage(AMQPMessage *message)
{
    this->message = message;
}
