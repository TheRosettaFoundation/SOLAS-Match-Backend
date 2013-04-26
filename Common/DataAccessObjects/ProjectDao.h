#ifndef PROJECTDAO_H
#define PROJECTDAO_H

#include <QtSql/QSqlQuery>
#include <QList>
#include <QString>
#include <QSharedPointer>

#include "Common/protobufs/models/Project.pb.h"
#include "Common/MySQLHandler.h"

class ProjectDao
{
public:
    static QList<QSharedPointer<Project> > getProjects(QSharedPointer<MySQLHandler> db, int id = -1, QString title = "", QString desc = "",
                                                       QString impact = "", QString deadline = "", int orgId = -1, QString ref = "",
                                      int wordCount = -1, QString created = "", QString language = "", QString country = "");
    static QSharedPointer<Project> getProject(QSharedPointer<MySQLHandler> db, int id = -1, QString title = "", QString desc = "",
                                              QString impact = "", QString deadline = "", int orgId = -1, QString ref = "",
                                      int wordCount = -1, QString created = "", QString language = "", QString country = "");
};

#endif // PROJECTDAO_H
