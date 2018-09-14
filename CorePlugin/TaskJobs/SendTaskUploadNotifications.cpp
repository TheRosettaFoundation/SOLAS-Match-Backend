#include "SendTaskUploadNotifications.h"

#include <QDebug>

#include "Common/protobufs/requests/TaskUploadNotificationRequest.pb.h"

#include "Common/protobufs/models/Task.pb.h"
#include "Common/protobufs/models/User.pb.h"

#include "Common/protobufs/emails/TrackedTaskUploaded.pb.h"
#include "Common/protobufs/emails/ClaimedTaskSourceUpdated.pb.h"
#include "Common/protobufs/emails/ClaimedTaskUploaded.pb.h"

#include "Common/DataAccessObjects/TaskDao.h"

#include "Common/MySQLHandler.h"
#include "Common/MessagingClient.h"

using namespace SolasMatch::Common::Protobufs::Requests;
using namespace SolasMatch::Common::Protobufs::Emails;
using namespace SolasMatch::Common::Protobufs::Models;

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
        request.ParseFromString(std::string(body, length));

        QSharedPointer<MySQLHandler> db = MySQLHandler::getInstance();
        QSharedPointer<Task> task = TaskDao::getTask(db, request.task_id());

        if (!task.isNull()) {
            QList<QSharedPointer<User> > users = TaskDao::getSubscribedUsers(db, task->id());
            QSharedPointer<User> translator = TaskDao::getUserClaimedTask(db, task->id());

            std::string body = "";
            MessagingClient publisher;
            if (publisher.init()) {
                if (request.file_version() == 0) {
                    if (!translator.isNull()) {
                        ClaimedTaskSourceUpdated claimedUpdate;
                        claimedUpdate.set_email_type(claimedUpdate.email_type());
                        claimedUpdate.set_task_id(task->id());
                        claimedUpdate.set_user_id(translator->id());
                        body = claimedUpdate.SerializeAsString();
                        publisher.publish(exchange, topic, body);
                    }
                } else {
                  if (TaskDao::is_chunked_task(db, task->id())) {
                      QSharedPointer<Task> parentTask = TaskDao::getParentTask(db, task->id(), TRANSLATION);
                      if (!parentTask.isNull()) {
                          QSharedPointer<User> parentClaimer = TaskDao::getUserClaimedTask(db, parentTask->id());
                          TrackedTaskUploaded trackedUpload;
                          if (!parentClaimer.isNull()) {
                              trackedUpload.set_email_type(trackedUpload.email_type());
                              trackedUpload.set_task_id(task->id());
                              trackedUpload.set_translator_id(translator->id());
                              trackedUpload.set_user_id(parentClaimer->id());
                              body = trackedUpload.SerializeAsString();
                              publisher.publish(exchange, topic, body);
                          }
                      }
                      if (task->tasktype() == TRANSLATION) {
                          QSharedPointer<Task> revisionTask = TaskDao::getMatchingTask(db, task->id(), PROOFREADING);
                          if (!revisionTask.isNull()) {
                              QSharedPointer<User> revisionClaimer = TaskDao::getUserClaimedTask(db, revisionTask->id());
                              if (!revisionClaimer.isNull()) {
                                  trackedUpload.set_email_type(trackedUpload.email_type());
                                  trackedUpload.set_task_id(task->id());
                                  trackedUpload.set_translator_id(translator->id());
                                  trackedUpload.set_user_id(revisionClaimer->id());
                                  body = trackedUpload.SerializeAsString();
                                  publisher.publish(exchange, topic, body);
                              }
                          } else {
                              qDebug() << "SendTaskUploadNotifications: getMatchingTask returned Null";
                          }
                      }
                  } else {
                    foreach (QSharedPointer<User> user, users) {
                        TrackedTaskUploaded trackedUpload;
                        trackedUpload.set_email_type(trackedUpload.email_type());
                        trackedUpload.set_task_id(task->id());
                        trackedUpload.set_translator_id(translator->id());
                        trackedUpload.set_user_id(user->id());
                        body = trackedUpload.SerializeAsString();
                        publisher.publish(exchange, topic, body);
                    }

                    ClaimedTaskUploaded claimedUpload;
                    claimedUpload.set_email_type(claimedUpload.email_type());
                    claimedUpload.set_task_id(task->id());
                    claimedUpload.set_user_id(translator->id());
                    body = claimedUpload.SerializeAsString();
                    publisher.publish(exchange, topic, body);
                  }
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
