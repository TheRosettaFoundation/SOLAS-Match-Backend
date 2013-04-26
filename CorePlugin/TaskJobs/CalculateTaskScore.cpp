#include "CalculateTaskScore.h"

#include <ctemplate/template.h>
#include <QtSql/QSqlQuery>
#include <QtSql/QSqlRecord>
#include <QDateTime>
#include <QDebug>
#include <QList>
#include <QThread>

#include "Common/MessagingClient.h"
#include "Common/ConfigParser.h"

#include "Common/DataAccessObjects/TaskDao.h"
#include "Common/DataAccessObjects/UserDao.h"
#include "Common/DataAccessObjects/TagDao.h"

#include "Common/protobufs/requests/UserTaskScoreRequest.pb.h"

#include "Common/protobufs/models/User.pb.h"
#include "Common/protobufs/models/Tag.pb.h"
#include "Common/protobufs/models/Locale.pb.h"

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
    // Default Destructor
}

void CalculateTaskScore::run()
{
    qDebug() << "CalculateTaskScore: Starting new thread " << this->thread()->currentThreadId();
    ConfigParser settings;
    QDateTime started = QDateTime::currentDateTime();
    ctemplate::TemplateDictionary dict("user_task_score");
    db = MySQLHandler::getInstance();
    if(db->init()) {
        QList<QSharedPointer<User> > users = UserDao::getUsers(db);
        QList<QSharedPointer<Task> > tasks = this->getTasks();  //Must use custom function to check message for task id
        if(users.length() > 0) {
            foreach(QSharedPointer<User> user, users) {
                Locale userNativeLocale = user->nativelocale();
                QList<QSharedPointer<Tag> > userTags = TagDao::getUserTags(db, user->id());
                if(tasks.length() > 0) {
                    foreach(QSharedPointer<Task> task, tasks) {
                        int score = 0;

                        Locale taskSourceLocale = task->sourcelocale();

                        if(userNativeLocale.languagecode() == taskSourceLocale.languagecode()) {
                            score += 200;
                            if(userNativeLocale.countrycode() == taskSourceLocale.countrycode()) {
                                score += 75;
                            }
                        }

                        Locale taskTargetLocale = task->targetlocale();

                        if(userNativeLocale.languagecode() == taskTargetLocale.languagecode()) {
                            score += 300;
                            if(userNativeLocale.countrycode() == taskTargetLocale.countrycode()) {
                                score += 100;
                            }
                        }

                        QList<QSharedPointer<Tag> > taskTags = TagDao::getTaskTags(db, task->id());
                        int increment_value = 100;
                        foreach(QSharedPointer<Tag> user_tag, userTags) {
                            foreach(QSharedPointer<Tag> task_tag, taskTags) {
                                if(user_tag->id() == task_tag->id()) {
                                    score += increment_value;
                                    increment_value *= 0.75;
                                }
                            }
                        }

                        QDateTime created_time = QDateTime::fromString(
                                    QString::fromStdString(task->createdtime()), "yyyy-MM-ddTHH:mm:ss");
                        //increase score by one per day since created time
                        score += created_time.daysTo(QDateTime::currentDateTime());

                        ctemplate::TemplateDictionary *score_sect = dict.AddSectionDictionary("SCORE_SECT");
                        score_sect->SetIntValue("USER_ID", user->id());
                        score_sect->SetIntValue("TASK_ID", task->id());
                        score_sect->SetIntValue("SCORE", score);
                        this->saveUserTaskScore(user->id(), task->id(), score);
                    }
                } else {
                    qDebug() << "No tasks found";
                    dict.ShowSection("ERROR");
                    dict["ERROR_MESSAGE"] = "No tasks found";
                }
            }
        } else {
            qDebug() << "No users found";
            dict.ShowSection("ERROR");
            dict["ERROR_MESSAGE"] = "No users found";
        }

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
        QString exchange_name = settings.get("messaging.exchange");
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

QList<QSharedPointer<Task> > CalculateTaskScore::getTasks()
{
    QList<QSharedPointer<Task> > ret = QList<QSharedPointer<Task> >();
    int message_task = this->getTaskIdFromMessage();
    if(message_task > 0) {
        ret = TaskDao::getTasks(db, message_task);
    } else {
        ret = TaskDao::getActiveTasks(db);
    }

    return ret;
}

int CalculateTaskScore::getTaskIdFromMessage()
{
    int ret = -1;
    uint32_t length = 0;

    char *body = this->message->getMessage(&length);

    if(length > 0) {
        UserTaskScoreRequest request;
        request.ParseFromString(body);
        if(request.has_task_id()) {
            ret = request.task_id();
        }
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

int CalculateTaskScore::getCurrentScore(int user_id, int task_id)
{
    int ret = -1;
    QString args = QString::number(user_id) + ", " + QString::number(task_id);
    QSharedPointer<QSqlQuery> q = db->call("getUserTaskScore", args);
    if(q->first()) {
        ret = db->getValueFromQuery("score", q).toInt();
    }

    return ret;
}
