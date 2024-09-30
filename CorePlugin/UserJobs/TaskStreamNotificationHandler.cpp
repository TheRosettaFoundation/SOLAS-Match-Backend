#include "TaskStreamNotificationHandler.h"

#include <QDebug>
#include <QThread>

#include "Common/MySQLHandler.h"
#include "Common/ConfigParser.h"
#include "Common/DataAccessObjects/UserDao.h"
#include "Common/Definitions.h"

#include <QDateTime>
#include <QRandomGenerator>

#include "../EmailPlugin/Generators/UserTaskStreamEmailGenerator.h"

void TaskStreamNotificationHandler::run()
{
    qDebug() << "TaskStreamNotificationHandler";
    ConfigParser settings;
    QSharedPointer<MySQLHandler> db = MySQLHandler::getInstance();
        QString sentDateTime = QDateTime::currentDateTime().toString("yyyy-MM-dd HH:59:58");
        QList<int> full_list_user_ids = UserDao::getUserIdsPendingTaskStreamNotification(db);
        QList<int> userIds = QList<int>(); // This will contain the cut down list of user_id(s) which will actually be sent emails
        qDebug() << "full_list_user_ids.count(): " << QString::number(full_list_user_ids.count());
UserTaskStreamEmailGenerator::run(3297);
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
            int random = QRandomGenerator::global()->bounded(max_allowed); // Pick max_allowed elements starting at a random element (circulating back to start, if necessary)
            qDebug() << "count, max_allowed, random: " << QString::number(count) << ", " << QString::number(max_allowed) << ", " << QString::number(random);
            int i = 0;
            foreach (int id, userIds) {
                if (((i >= random) && (i < random + max_allowed)) || ((i >= (random - count)) && (i < random + max_allowed - count))) {
                    UserTaskStreamEmailGenerator::run(id);
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

        // Earthquake
        QList<int> users_list_for_earthquake = UserDao::get_users_list_for_earthquake(db);
        qDebug() << "users_list_for_earthquake.count(): " << QString::number(users_list_for_earthquake.count());
        count = users_list_for_earthquake.count();
        max_allowed = 1000; // per hour
        if (count < max_allowed) max_allowed = count;
        if (max_allowed > 0) {
            int random = QRandomGenerator::global()->bounded(max_allowed); // Pick max_allowed elements starting at a random element (circulating back to start, if necessary)
            qDebug() << "count, max_allowed, random Earthquake: " << QString::number(count) << ", " << QString::number(max_allowed) << ", " << QString::number(random);
            int i = 0;
            foreach (int id, users_list_for_earthquake) {
                if (((i >= random) && (i < random + max_allowed)) || ((i >= (random - count)) && (i < random + max_allowed - count))) {
                    UserTaskStreamEmailGenerator::run(-id); // Negative means Earthquake
                } else {
                    qDebug() << "TaskStreamNotificationHandler: Discarded user id Earthquake " << QString::number(id);
                }
                i++;
            }
        }
}
