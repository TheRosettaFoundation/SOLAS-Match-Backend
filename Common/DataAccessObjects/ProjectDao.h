#ifndef PROJECTDAO_H
#define PROJECTDAO_H

#include <QtSql/QSqlQuery>
#include <QList>
#include <QString>
#include <QSharedPointer>

#include "Common/protobufs/models/Project.pb.h"
#include "Common/protobufs/models/ArchivedProject.pb.h"
#include "Common/MySQLHandler.h"

using namespace  SolasMatch::Common::Protobufs::Models;

class ProjectDao
{
public:
    static QList<QSharedPointer<Project> > getProjects(QSharedPointer<MySQLHandler> db, int id = -1, QString title = "", QString desc = "",
                                                       QString impact = "", QString deadline = "", int orgId = -1, QString ref = "",
                                      int wordCount = -1, QString created = "", QString language = "", QString country = "", int imageUploaded  = -1, int imageApproved = -1);
    static QSharedPointer<Project> getProject(QSharedPointer<MySQLHandler> db, int id = -1, QString title = "", QString desc = "",
                                              QString impact = "", QString deadline = "", int orgId = -1, QString ref = "",
                                      int wordCount = -1, QString created = "", QString language = "", QString country = "", int imageUploaded  = -1, int imageApproved = -1);
    static QSharedPointer<ArchivedProject> getArchivedProject(QSharedPointer<MySQLHandler> db, int id = -1);
    static QList<QSharedPointer<ArchivedProject> > getArchivedProjects(QSharedPointer<MySQLHandler> db, int id = -1);
    static std::string discourse_parameterize(const std::string a);
};

#endif // PROJECTDAO_H
