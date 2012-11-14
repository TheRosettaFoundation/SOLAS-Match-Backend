#include "Org.h"

Org::Org()
{
    this->biography = "";
    this->id = -1;
    this->home_page = "";
    this->name = "";
}

Org::Org(QSqlQuery *q)
{
    this->setId(MySQLHandler::getValueFromQuery("id", q).toInt());
    this->setName(MySQLHandler::getValueFromQuery("name", q).toString());
    this->setBiography(MySQLHandler::getValueFromQuery("biography", q).toString());
    this->setHomePage(MySQLHandler::getValueFromQuery("home_page", q).toString());
}

Org Org::getOrg(MySQLHandler *db, int org_id)
{
    Org org;
    QString args = QString::number(org_id);
    args += ", null, null, null";
    QSqlQuery *result = db->call("getOrg", args);
    if(result->first())
    {
        org = Org(result);
    }

    return org;
}

int Org::getId()
{
    return this->id;
}

QString Org::getName()
{
    return this->name;
}

QString Org::getBiography()
{
    return this->biography;
}

QString Org::getHomePage()
{
    return this->home_page;
}

void Org::setId(int org_id)
{
    this->id = org_id;
}

void Org::setName(QString n)
{
    this->name = n;
}

void Org::setBiography(QString bio)
{
    this->biography = bio;
}

void Org::setHomePage(QString url)
{
    this->home_page = url;
}
