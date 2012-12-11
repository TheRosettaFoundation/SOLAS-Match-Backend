#ifndef MODELGENERATOR_H
#define MODELGENERATOR_H

#include <QtSql/QSqlQuery>
#include <QSharedPointer>

#include "protobufs/models/Tag.pb.h"
#include "protobufs/models/User.pb.h"
#include "protobufs/models/Task.pb.h"
#include "protobufs/models/Organisation.pb.h"
#include "protobufs/models/ArchivedTask.pb.h"

class ModelGenerator
{
public:
    static QSharedPointer<Tag> GenerateTag(QSqlQuery *q);
    static QSharedPointer<User> GenerateUser(QSqlQuery *q);
    static QSharedPointer<Task> GenerateTask(QSqlQuery *q);
    static QSharedPointer<Organisation> GenerateOrg(QSqlQuery *q);
    static QSharedPointer<ArchivedTask> GenerateArchivedTask(QSqlQuery *q);

};

#endif // MODELGENERATOR_H
