#ifndef USERDAO_H
#define USERDAO_H

#include <QtSql/QSqlQuery>
#include <QList>
#include <QString>

#include "Common/MySQLHandler.h"
#include "Common/protobufs/models/User.pb.h"

class UserDao
{
public:
    //return a list of users
    static QList<User*> *getUsers(MySQLHandler *db,
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
    static User *getUser(MySQLHandler *db,
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

};

#endif  //USERDAO_H
