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
using namespace SolasMatch::Common::Protobufs::Emails;
using namespace SolasMatch::Common::Protobufs::Requests;
using namespace SolasMatch::Common::Protobufs::Models;

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
static int countx = 0;
void CalculateTaskScore::run()
{

    qDebug() << "CalculateTaskScore: Starting new thread";

    ConfigParser settings;
    QDateTime started = QDateTime::currentDateTime();
    ctemplate::TemplateDictionary dict("user_task_score");
    db = MySQLHandler::getInstance();
    QMultiMap<int, LCCode> users = UserDao::getUserNativeLCCodes(db);
    QList<QSharedPointer<Task> > tasks = this->getTasks();  //Must use custom function to check message for task id

    QMultiMap<int, LCCode> userSecondaryLanguages = UserDao::getUserLCCodes(db);
    QMultiMap<int, int> userTags = UserDao::getUserTagIds(db);
    QMultiMap<int, int> taskTags = TaskDao::getTaskTagIds(db);

    if(users.count() > 0) {
        for(QMultiMap<int, LCCode>::ConstIterator usersIter = users.constBegin(); usersIter != users.constEnd(); ++usersIter) {
            if(tasks.length() > 0) {
                const LCCode userNativeLCCode = users.value(usersIter.key());
                QList<TaskScore> taskScores;
                foreach(QSharedPointer<Task> task, tasks) {
                    int score = 0;

                    Locale taskSourceLocale = task->sourcelocale();

                    if(userNativeLCCode.first == taskSourceLocale.languagecode()) {
                        score += 750;
                        if(userNativeLCCode.second == taskSourceLocale.countrycode()) {
                            score += 75;
                        }
                    }

                    Locale taskTargetLocale = task->targetlocale();

                    if(userNativeLCCode.first == taskTargetLocale.languagecode()) {
                        score += 1000;
                        if(userNativeLCCode.second == taskTargetLocale.countrycode()) {
                            score += 100;
                        }
                    }

                    if(userSecondaryLanguages.contains(usersIter.key())) {
                        const QList<LCCode> lcCodes = userSecondaryLanguages.values(usersIter.key());
                        if(lcCodes.end() != std::find_if(lcCodes.begin(), lcCodes.end(), LidMatch(taskSourceLocale.languagecode()))) {
                            score += 500;
                            if(lcCodes.end() != std::find_if(lcCodes.begin(), lcCodes.end(), CidMatch(taskSourceLocale.countrycode())) ) {
                                score += 50;
                            }
                        }
                        if(lcCodes.end() != std::find_if(lcCodes.begin(), lcCodes.end(), LidMatch(taskTargetLocale.languagecode()))) {
                            score += 500;
                            if(lcCodes.end() != std::find_if(lcCodes.begin(), lcCodes.end(), CidMatch(taskTargetLocale.countrycode())) ) {
                                score += 50;
                            }
                        }
                    }

                    if(userTags.contains(usersIter.key()) && taskTags.contains(task->id())) {
                        int increment_value = 250;
                        QList<int> userTagIds = userTags.values(usersIter.key());
                        QList<int> userTaskTagIds = taskTags.values(task->id());

                        foreach(int userTagId, userTagIds) {
                            if(userTaskTagIds.contains(userTagId)) {
                                    score += increment_value;
                                    increment_value *= 0.75;
                            }
                        }
                    }

                    QDateTime created_time = QDateTime::fromString(
                                            QString::fromStdString(task->createdtime()), Qt::ISODate);
                    //increase score by one per day since created time
                    score += created_time.daysTo(QDateTime::currentDateTime());
                    taskScores.append(TaskScore(task->id(), score));
                }

                    this->saveUserTaskScore(usersIter.key(),taskScores);

            } else {
                qDebug() << "No tasks found";
                dict.ShowSection("ERROR");
                dict.SetValue("ERROR_MESSAGE","No tasks found");
            }

        }
    } else {
        qDebug() << "No users found";
        dict.ShowSection("ERROR");
        dict.SetValue("ERROR_MESSAGE","No users found");
    }

    int time_msecs = started.msecsTo(QDateTime::currentDateTime());
    int time_secs = time_msecs / 1000;
    time_msecs %= 1000;
    QString time_value = QString::number(time_secs) + "." +
            QString("%1 seconds").arg(time_msecs, 3, 10, QChar('0'));
    dict.SetValue("TIME", time_value.toStdString());
    dict.SetIntValue("TOTAL_USERS", users.size());
    dict.SetIntValue("TOTAL_TASKS", tasks.size());
    dict.SetIntValue("UPDATE_COUNT", countx);

    QString template_location = QString(TEMPLATE_DIRECTORY) + "score_results.tpl";
    std::string email_body;
    ctemplate::ExpandTemplate(template_location.toStdString(), ctemplate::DO_NOT_STRIP, &dict, &email_body);

    TaskScoreEmail message_body = TaskScoreEmail();
    message_body.set_email_type(EmailMessage::TaskScoreEmail);
    message_body.set_body(email_body);
    try {
        QString exchange_name = settings.get("messaging.exchange");
        QString exchange_topic = "email.task.score";
        QString body = QString::fromStdString(message_body.SerializeAsString());

        MessagingClient publisher;
        publisher.init();
        publisher.publish(exchange_name, exchange_topic, body);
    } catch (AMQPException e) {
        qDebug() << "Failed to publish email task score: " << QString::fromStdString(e.getMessage());
    } catch (exception e) {
        qDebug() << "Failed to publish message" << QString::fromStdString(e.what());
    }
    countx = 0;
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


void CalculateTaskScore::saveUserTaskScore(int user_id, QList<TaskScore > scores)
{
        QList<QString> argList;
        foreach(TaskScore score,scores){
            int old_score = this->getCurrentScore(user_id, score.first);
            if(old_score != score.second) {
                ++countx;
            QString args = QString::number(user_id) + ", " + QString::number(score.first)
                + ", " + QString::number(score.second);
                argList.append(args);
            }
        }
        if(!argList.empty())       db->multicall("saveUserTaskScore", argList);
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

void CalculateTaskScore::setAMQPMessage(AMQPMessage *message)
{
    this->message = message;
}
