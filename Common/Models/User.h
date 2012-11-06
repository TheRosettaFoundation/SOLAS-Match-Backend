#ifndef USER_H
#define USER_H

#include <QtSql/QSqlQuery>
#include <QList>
#include <QString>

#include "Common/MySQLHandler.h"

class User
{
public:
    User();
    User(QSqlQuery *q);
    //return a list of users
    static QList<User> *getUsers(MySQLHandler *db,
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
    static User getUser(MySQLHandler *db,
                                 int id = -1,
                                 QString name = "",
                                 QString email = "",
                                 QString pass = "",
                                 QString bio = "",
                                 QString non = "",
                                 QString date = "",
                                 int lang_id = -1,
                                 int reg_id = -1);
    void setUserId(int user_id);
    void setDisplayName(QString name);
    void setEmail(QString email);
    void setPassword(QString pass);
    void setBiography(QString bio);
    void setNonce(QString non);
    void setCreatedTime(QString date);
    void setNativeLangId(int lang_id);
    void setRegionId(int reg_id);
    int getUserId();
    QString getDisplayName();
    QString getEmail();
    QString getPassword();
    QString getBiography();
    QString getNonce();
    QString getCreatedTime();
    int getNativeLangId();
    int getRegionId();

private:
    int id;
    QString display_name;
    QString email;
    QString password;
    QString biography;
    QString nonce;
    QString created_time;
    int native_lang_id;
    int native_region_id;

};

#endif // USER_H
