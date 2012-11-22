#include "CalculateTaskScoreJob.h"

#include <QtSql/QSqlQuery>
#include <QtSql/QSqlRecord>
#include <QDateTime>
#include <QDebug>
#include <QList>
#include <QThread>
#include <QUuid>

#include <ctemplate/template.h>

#include "Common/MessagingClient.h"

#include "Common/Models/Tag.h"
#include "Common/Models/User.h"

#include "Common/protobufs/emails/EmailMessage.pb.h"
#include "Common/protobufs/emails/TaskScoreEmail.pb.h"

#define TEMPLATE_DIRECTORY "/etc/SOLAS-Match/templates/"

CalculateTaskScore::CalculateTaskScore()
{
    this->message = new AMQPMessage(NULL);
}

CalculateTaskScore::CalculateTaskScore(AMQPMessage *mess)
{
    this->message = mess;
}

CalculateTaskScore::~CalculateTaskScore()
{
    delete db;
    if(message) {
        delete message;
    }
}

void CalculateTaskScore::run()
{
    qDebug() << "Starting new thread " << this->thread()->currentThreadId();
    QDateTime started = QDateTime::currentDateTime();
    ctemplate::TemplateDictionary dict("user_task_score");
    db = new MySQLHandler(QUuid::createUuid().toString());
    if(db->init()) {
        QList<User> *users = User::getUsers(db);
        QList<Task> *tasks = this->getTasks();  //Must use custom function to check message for task id
        if(users != NULL && users->length() > 0) {
            foreach(User user, *users) {
                QList<Tag> *userTags = Tag::getUserTags(db, user.getUserId());
                if(tasks != NULL && tasks->length() > 0) {
                    foreach(Task task, *tasks) {
                        int score = 0;

                        if(user.getNativeLangId() == task.getSourceLangId()) {
                            score += 300;
                            if(user.getRegionId() == task.getSourceRegionId()) {
                                score += 100;
                            }
                        }

                        if(user.getNativeLangId() == task.getTargetLangId()) {
                            score += 150;
                            if(user.getRegionId() == task.getTargetRegionId()) {
                                score += 75;
                            }
                        }

                        QList<Tag> *taskTags = Tag::getTaskTags(db, task.getTaskId());
                        int increment_value = 100;
                        foreach(Tag user_tag, *userTags) {
                            foreach(Tag task_tag, *taskTags) {
                                if(user_tag.getTagId() == task_tag.getTagId()) {
                                    score += increment_value;
                                    increment_value *= 0.75;
                                }
                            }
                        }
                        delete taskTags;

                        QDateTime created_time = QDateTime::fromString(task.getCreatedTime(), "yyyy-MM-ddTHH:mm:ss");
                        //increase score by one per day since created time
                        score += created_time.daysTo(QDateTime::currentDateTime());

                        dict.ShowSection("SCORE");
                        dict["USER_ID"] = QString::number(user.getUserId()).toStdString();
                        dict["TASK_ID"] = QString::number(task.getTaskId()).toStdString();
                        dict["SCORE"] = QString::number(score).toStdString();
                        this->saveUserTaskScore(user.getUserId(), task.getTaskId(), score);
                    }
                } else {
                    qDebug() << "No tasks found";
                }
                delete userTags;
            }
        } else {
            qDebug() << "No users found";
            dict.ShowSection("ERROR");
            dict["ERROR_MESSAGE"] = "No users found";
        }

        AMQPQueue *messageQueue = message->getQueue();
        if(messageQueue != NULL)
        {
            messageQueue->Ack(message->getDeliveryTag());
        }

        delete users;
        delete tasks;

        db->close();
    } else {
        qDebug() << "Unable to Connect to SQL Server. Check conf.ini and try again.";
        dict.ShowSection("ERROR");
        dict.SetValue("ERROR_MESSAGE", "Unable to Connect to SQL Server. Check conf.ini and try again.");
    }

    int time_msecs = started.msecsTo(QDateTime::currentDateTime());
    int time_secs = time_msecs / 1000;
    time_msecs %= 1000;
    dict.ShowSection("TIMING");
    QString time_value = QString::number(time_secs) + "." +
            QString("%1 seconds").arg(time_msecs, 3, 10, QChar('0'));
    dict["TIME"] = time_value.toStdString();

    QString template_location = QString(TEMPLATE_DIRECTORY) + "score_results.tpl";
    std::string email_body;
    ctemplate::ExpandTemplate(template_location.toStdString(), ctemplate::DO_NOT_STRIP, &dict, &email_body);

    TaskScoreEmail *message_body = new TaskScoreEmail();
    message_body->set_email_type(EmailMessage::TaskScoreEmail);
    message_body->set_body(email_body);
    try {
        QString exchange_name = "SOLAS_MATCH";
        QString exchange_topic = "email.task.score";
        QString body = QString::fromStdString(message_body->SerializeAsString());

        MessagingClient publisher;
        publisher.init();
        publisher.publish(exchange_name, exchange_topic, body);
    } catch (AMQPException e) {
        qDebug() << "Failed to publish email task score: " << QString::fromStdString(e.getMessage());
    } catch (exception e) {
        qDebug() << "Failed to publish message" << QString::fromStdString(e.what());
    }
    delete message_body;
    qDebug() << "CalcUserTaskScore::Finished publishing";
}

QList<Task> *CalculateTaskScore::getTasks()
{
    QList<Task> *ret = NULL;
    int message_task = this->getTaskIdFromMessage();
    if(message_task > 0) {
        ret = Task::getTasks(db, message_task);
    } else {
        ret = Task::getActiveTasks(db);
    }

    return ret;
}

int CalculateTaskScore::getCurrentScore(int user_id, int task_id)
{
    int ret = -1;
    QString args = QString::number(user_id) + ", " + QString::number(task_id);
    QSqlQuery *q = db->call("getUserTaskScore", args);
    if(q->first()) {
        ret = db->getValueFromQuery("score", q).toInt();
    }
    delete q;

    return ret;
}

int CalculateTaskScore::getTaskIdFromMessage()
{
    int ret = -1;
    uint32_t length = 0;

    char *body = this->message->getMessage(&length);

    if(length > 0) {
        ret = atoi(body);

        delete body;
    }

    return ret;
}

void CalculateTaskScore::saveUserTaskScore(int user_id, int task_id, int score)
{
    int old_score = this->getCurrentScore(user_id, task_id);
    if(old_score != score) {
        QString args = QString::number(user_id) + ", " + QString::number(task_id)
                + ", " + QString::number(score);
        db->call("saveUserTaskScore", args);
    }
}
