#ifndef ORG_H
#define ORG_H

#include <QtSql/QSqlQuery>
#include <QList>
#include <QString>

#include "Common/MySQLHandler.h"

class Org
{
public:
    Org();
    Org(QSqlQuery *q);
    static Org getOrg(MySQLHandler *db, int org_id);
    int getId();
    QString getName();
    QString getHomePage();
    QString getBiography();
    void setId(int org_id);
    void setName(QString n);
    void setHomePage(QString url);
    void setBiography(QString bio);

private:
    int id;
    QString name;
    QString home_page;
    QString biography;

};

#endif // ORG_H
