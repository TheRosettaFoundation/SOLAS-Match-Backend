#ifndef USERDAO_H
#define USERDAO_H

#include <QtSql/QSqlQuery>
#include <QList>
#include <QString>
#include <QSharedPointer>

#include "Common/MySQLHandler.h"
#include "Common/protobufs/models/User.pb.h"
#include "Common/protobufs/models/Task.pb.h"

class UserDao
{
public:
    //return a list of users
    static QList<QSharedPointer<User> > getUsers(MySQLHandler *db,
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
    static QSharedPointer<User> getUser(MySQLHandler *db,
                         int id = -1,
                         QString name = "",
                         QString email = "",
                         QString pass = "",
                         QString bio = "",
                         QString non = "",
                         QString date = "",
                         int lang_id = -1,
                         int reg_id = -1);
    static QString getPasswordResetUuid(MySQLHandler *db, int id);
    static QList<QSharedPointer<Task> > getUserTopTasks(MySQLHandler *db, int userId,
                                                        int limit = 10, QString filter = "");

};

#endif  //USERDAO_H
