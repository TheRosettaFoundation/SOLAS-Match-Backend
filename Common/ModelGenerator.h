#ifndef MODELGENERATOR_H
#define MODELGENERATOR_H

#include <QtSql/QSqlQuery>
#include <QSharedPointer>

#include "protobufs/models/Badge.pb.h"
#include "protobufs/models/Tag.pb.h"
#include "protobufs/models/User.pb.h"
#include "protobufs/models/Task.pb.h"
#include "protobufs/models/Organisation.pb.h"
#include "protobufs/models/ArchivedTask.pb.h"
#include "protobufs/models/Project.pb.h"
#include "protobufs/models/ArchivedProject.pb.h"
#include "protobufs/models/Language.pb.h"
#include "protobufs/models/BannedUser.pb.h"
#include "protobufs/models/UserTaskStreamNotification.pb.h"

using namespace  SolasMatch::Common::Protobufs::Models;

class ModelGenerator
{
public:
    static void Generate(QSharedPointer<QSqlQuery> q, QSharedPointer<ArchivedProject>, QMap<QString, int> fieldMap);
    static void Generate(QSharedPointer<QSqlQuery> q, QSharedPointer<ArchivedTask>, QMap<QString, int> fieldMap);
    static void Generate(QSharedPointer<QSqlQuery> q, QSharedPointer<Badge>, QMap<QString, int> fieldMap);
    static void Generate(QSharedPointer<QSqlQuery> q, QSharedPointer<Tag>, QMap<QString, int> fieldMap);
    static void Generate(QSharedPointer<QSqlQuery> q, QSharedPointer<User>, QMap<QString, int> fieldMap);
    static void Generate(QSharedPointer<QSqlQuery> q, QSharedPointer<Task>, QMap<QString, int> fieldMap);
    static void Generate(QSharedPointer<QSqlQuery> q, QSharedPointer<Organisation>, QMap<QString, int> fieldMap);
    static void Generate(QSharedPointer<QSqlQuery> q, QSharedPointer<Project>, QMap<QString, int> fieldMap);
    static void Generate(QSharedPointer<QSqlQuery> q, QSharedPointer<Language>, QMap<QString, int> fieldMap);
    static void Generate(QSharedPointer<QSqlQuery> q, QSharedPointer<BannedUser>, QMap<QString, int> fieldMap);
    static void Generate(QSharedPointer<QSqlQuery> q, QSharedPointer<Locale>, QMap<QString, int> fieldMap);
    static void Generate(QSharedPointer<QSqlQuery> q, QSharedPointer<UserTaskStreamNotification>, QMap<QString, int> fieldMap);

};

#endif // MODELGENERATOR_H
