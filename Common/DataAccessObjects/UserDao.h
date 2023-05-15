#ifndef USERDAO_H
#define USERDAO_H

#include <QtSql/QSqlQuery>
#include <QList>
#include <QString>
#include <QSharedPointer>

#include "Common/Definitions.h"
#include "Common/MySQLHandler.h"
#include "Common/protobufs/models/User.pb.h"
#include "Common/protobufs/models/Task.pb.h"
#include "Common/protobufs/models/BannedUser.pb.h"
#include "Common/protobufs/models/UserTaskStreamNotification.pb.h"
#include "Common/protobufs/models/ArchivedTask.pb.h"

using namespace  SolasMatch::Common::Protobufs::Models;

class UserDao
{
public:
    //return a list of users
    static QList<QSharedPointer<User> > getUsers(QSharedPointer<MySQLHandler> db,
                                 int id = -1,
                                 QString name = "",
                                 QString email = "",
                                 QString pass = "",
                                 QString bio = "",
                                 QString non = "",
                                 QString date = "",
                                 int lang_id = -1,
                                 int reg_id = -1);
    //return a single user
    static QSharedPointer<User> getUser(QSharedPointer<MySQLHandler> db,
                         int id = -1,
                         QString name = "",
                         QString email = "",
                         QString pass = "",
                         QString bio = "",
                         QString non = "",
                         QString date = "",
                         int lang_id = -1,
                         int reg_id = -1);
    static QSharedPointer<BannedUser> getBanData(QSharedPointer<MySQLHandler> db, int userId);
    static QList<QSharedPointer<Task> > getUserTasks(QSharedPointer<MySQLHandler> db, int userId, int limit = RETURN_ALL, int offset = 0);
    static QList<QSharedPointer<ArchivedTask> > getUserArchivedTasks(QSharedPointer<MySQLHandler> db, int userId, int limit = RETURN_ALL);
    static QString getRegistrationId(QSharedPointer<MySQLHandler> db, int userId);
    static QString get_password_reset_request_uuid(QSharedPointer<MySQLHandler> db, int user_id);
    static QList<QSharedPointer<Task> > getUserTopTasks(QSharedPointer<MySQLHandler> db, int userId, bool strict = false,
                                                        int limit = 10, int offset = RETURN_ALL, int taskTypeId = -1,
                                                        QString sourceLanguageCode = "", QString targetLanguageCode = "");
    static QList<int> getUserIdsPendingTaskStreamNotification(QSharedPointer<MySQLHandler> db);
    static QSharedPointer<UserTaskStreamNotification> getUserTaskStreamNotification(QSharedPointer<MySQLHandler> db,
                                                        int userId);
    static bool taskStreamNotificationSent(QSharedPointer<MySQLHandler> db, int userId, QString sentDate);

    static QList<QSharedPointer<Locale> > getUserSecondaryLanguages(QSharedPointer<MySQLHandler> db, int userId);
    static QMultiMap<int, LCCode> getUserLCCodes(QSharedPointer<MySQLHandler> db, int limit = RETURN_ALL, int offset = RETURN_ALL);
    static QMultiMap<int, int> getUserTagIds(QSharedPointer<MySQLHandler> db, int limit = RETURN_ALL, int offset = RETURN_ALL);
    static QMultiMap<int, LCCode> getUserNativeLCCodes(QSharedPointer<MySQLHandler> db, int limit = RETURN_ALL, int offset = RETURN_ALL);
    static QString getUserRealName(QSharedPointer<MySQLHandler> db, int userId);
    static QList<QSharedPointer<User> > getRecordWarningUsers(QSharedPointer<MySQLHandler> db);
    static void insertWillBeDeletedUser(QSharedPointer<MySQLHandler> db, int user_id);
    static void log_email_sent(QSharedPointer<MySQLHandler> db, int recipient_id, int task_id, int project_id, int org_id, int translator_id, int admin_id, int badge_id, QString topic);
    static void queue_email(QSharedPointer<MySQLHandler> db, int recipient_id, QString recipient, QString subject, QString body, int priority = 3)
    static QMap<QString, QVariant> get_email_request(QSharedPointer<MySQLHandler> db)
    static QList<int> get_users_list_for_earthquake(QSharedPointer<MySQLHandler> db);
    static QList<QSharedPointer<Task> > get_user_earthquake_tasks(QSharedPointer<MySQLHandler> db, int userId);
};

#endif  //USERDAO_H
