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

    if (this->calculationStillRunning()) {
        qDebug() << "CalculateTaskScore: Previous calculation is still running, so skipping this iteration";
        return;
    }

    QMultiMap<int, LCCode> users = UserDao::getUserNativeLCCodes(db);
    QList<QSharedPointer<Task> > tasks = this->getTasks();  //Must use custom function to check message for task id

    QMultiMap<int, LCCode> userSecondaryLanguages = UserDao::getUserLCCodes(db);
    QMultiMap<int, int> userTags = UserDao::getUserTagIds(db);
    QMultiMap<int, int> taskTags = TaskDao::getTaskTagIds(db);

//uint32_t ucount = users.count();
//uint32_t tlength = tasks.length();
//qDebug() << "FOR UserTaskStreamEmailGenerator: #users: " << ucount << ", #tasks: " << tlength;
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
                    // 20160123...
                    // Updating the score every day causes every single row of UserTaskScores to be updated
                    // Unfortunately a row update is very expensive (23ms when last measured & growing?)
                    // I have tried removing foreign key constraints form the table and this does not help.
                    // There are three other keys but at least two of them are needed.
                    // Maybe a different database configuration or different engine for the table might help?
                    // So I am moving the "daysTo" calculation to the database procedure "getUserTopTasks"
                    // where it is inexpensively calculated as part of the ORDER BY clause (with a maximum value of 700)
                    // "ORDER BY (uts.score+LEAST(DATEDIFF(CURDATE(), t.`created-time`), 700))"
                    // score += created_time.daysTo(QDateTime::currentDateTime());
                    taskScores.append(TaskScore(task->id(), score));
                }

                    this->saveUserTaskScore(usersIter.key(),taskScores);

//uint32_t user_id_iterator = usersIter.key();
//qDebug() << "FOR UserTaskStreamEmailGenerator: After save, user_id: " << user_id_iterator;
            } else {
                qDebug() << "No tasks found";
                dict.ShowSection("ERROR");
                dict.SetValue("ERROR_MESSAGE","No tasks found");
            }

            // Record the last Time that any Tasks were processed for any user (saveUserTaskScore)
            db->call("recordUserTaskScoresUpdatedTime", QString::number(QDateTime::currentMSecsSinceEpoch()));
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
        std::string body = message_body.SerializeAsString();

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
        request.ParseFromString(std::string(body, length));
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

bool CalculateTaskScore::calculationStillRunning()
{
    QSharedPointer<QSqlQuery> q = db->call("getUserTaskScoresUpdatedTime", "");
    if (q->first()) {
        qint64 unixEpoch = db->getValueFromQuery("unix_epoch", q).toLongLong();
qint64 delta = QDateTime::currentMSecsSinceEpoch() - unixEpoch;
        if ((QDateTime::currentMSecsSinceEpoch() - unixEpoch) < 30*60*1000) { // Half an hour
qDebug() << "calculationStillRunning ms (SKIP): " << delta;
            return true; // Skip calculation
        } else {
qDebug() << "calculationStillRunning ms (not skip): " << delta;
            return false;
        }
    } else {
qDebug() << "calculationStillRunning (NO RECORD)";
        return false;
    }
}
