#ifndef MODELGENERATOR_H
#define MODELGENERATOR_H

#include <QtSql/QSqlQuery>
#include <QSharedPointer>

#include "protobufs/models/Tag.pb.h"
#include "protobufs/models/User.pb.h"
#include "protobufs/models/Task.pb.h"
#include "protobufs/models/Organisation.pb.h"
#include "protobufs/models/ArchivedTask.pb.h"
#include "protobufs/models/Project.pb.h"
#include "protobufs/models/ArchivedProject.pb.h"
#include "protobufs/models/Language.pb.h"
#include "protobufs/models/BannedUser.pb.h"

class ModelGenerator
{
public:
    static QSharedPointer<Tag> GenerateTag(QSharedPointer<QSqlQuery> q);
    static QSharedPointer<User> GenerateUser(QSharedPointer<QSqlQuery> q);
    static QSharedPointer<Task> GenerateTask(QSharedPointer<QSqlQuery> q);
    static QSharedPointer<Organisation> GenerateOrg(QSharedPointer<QSqlQuery> q);
    static QSharedPointer<ArchivedTask> GenerateArchivedTask(QSharedPointer<QSqlQuery> q);
    static QSharedPointer<Project> GenerateProject(QSharedPointer<QSqlQuery> q);
    static QSharedPointer<ArchivedProject> GenerateArchivedProject(QSharedPointer<QSqlQuery> q);
    static QSharedPointer<Language> GenerateLanguage(QSharedPointer<QSqlQuery> q);
    static QSharedPointer<BannedUser> GenerateBannedUser(QSharedPointer<QSqlQuery> q);
    static QSharedPointer<Locale> GenerateLocale(QSharedPointer<QSqlQuery> q);


};

#endif // MODELGENERATOR_H
