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
#include "protobufs/models/UserTaskStreamNotification.pb.h"

class ModelGenerator
{
public:
    static void Generate(QSharedPointer<QSqlQuery> q, QSharedPointer<Tag>);
    static void Generate(QSharedPointer<QSqlQuery> q, QSharedPointer<User>);
    static void Generate(QSharedPointer<QSqlQuery> q, QSharedPointer<Task>);
    static void Generate(QSharedPointer<QSqlQuery> q, QSharedPointer<Organisation>);
    static void Generate(QSharedPointer<QSqlQuery> q, QSharedPointer<ArchivedTask>);
    static void Generate(QSharedPointer<QSqlQuery> q, QSharedPointer<Project>);
    static void Generate(QSharedPointer<QSqlQuery> q, QSharedPointer<ArchivedProject>);
    static void Generate(QSharedPointer<QSqlQuery> q, QSharedPointer<Language>);
    static void Generate(QSharedPointer<QSqlQuery> q, QSharedPointer<BannedUser>);
    static void Generate(QSharedPointer<QSqlQuery> q, QSharedPointer<Locale>);
    static void Generate(QSharedPointer<QSqlQuery> q, QSharedPointer<UserTaskStreamNotification>);

};

#endif // MODELGENERATOR_H
