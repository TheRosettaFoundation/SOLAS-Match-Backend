#include "CalculateTaskScoreJob.h"

#include <QtSql/QSqlQuery>
#include <QtSql/QSqlRecord>
#include <QDateTime>
#include <QDebug>
#include <QList>
#include <QThread>
#include <QUuid>

#include "Common/Models/Tag.h"
#include "Common/Models/User.h"

CalculateTaskScore::CalculateTaskScore(AMQPMessage *mess)
{
    this->message = mess;
}

void CalculateTaskScore::run()
{
    qDebug() << "Starting new thread " << this->thread()->currentThreadId();
    db = new MySQLHandler(QUuid::createUuid().toString());
    db->init();
    QList<User> *users = User::getUsers(db);
    QList<Task> *tasks = this->getTasks();  //Must use custom function to check message for task id
    if(users != NULL && users->length() > 0) {
        foreach(User user, *users) {
            qDebug() << "Processing User " << user.getUserId();
            QList<Tag> *userTags = Tag::getUserTags(db, user.getUserId());
            if(tasks != NULL && tasks->length() > 0) {
                foreach(Task task, *tasks) {
                    qDebug() << "\tProcessing task " << task.getTaskId();
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

                    QDateTime created_time = QDateTime::fromString(task.getCreatedTime(), "yyyy-MM-ddTHH:mm:ss");
                    //increase score by one per day since created time
                    score += created_time.daysTo(QDateTime::currentDateTime());

                    this->saveUserTaskScore(user.getUserId(), task.getTaskId(), score);
                }
            } else {
                qDebug() << "No tasks found";
            }
        }
    } else {
        qDebug() << "No users found";
    }

    AMQPQueue *messageQueue = message->getQueue();
    messageQueue->Ack(message->getDeliveryTag());

    db->close();
}

QList<Task> *CalculateTaskScore::getTasks()
{
    QList<Task> *ret = NULL;
    int message_task = this->getTaskIdFromMessage();
    ret = Task::getTasks(db, message_task);

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

    return ret;
}

int CalculateTaskScore::getTaskIdFromMessage()
{
    int ret = -1;
    uint32_t length = 0;

    char *body = this->message->getMessage(&length);

    if(length > 0) {
        ret = atoi(body);
    }

    return ret;
}

void CalculateTaskScore::saveUserTaskScore(int user_id, int task_id, int score)
{
    int old_score = this->getCurrentScore(user_id, task_id);
    if(old_score != score) {
        qDebug() << "CalculateTaskScore::updating score (" << QString::number(score)
                 << ") for user " << QString::number(user_id)
                 << ", task " << QString::number(task_id);
        QString args = QString::number(user_id) + ", " + QString::number(task_id)
                + ", " + QString::number(score);
        db->call("saveUserTaskScore", args);
    }
}
