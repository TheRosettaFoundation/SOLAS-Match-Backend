#ifndef MODELGENERATOR_H
#define MODELGENERATOR_H

#include <QtSql/QSqlQuery>

#include "protobufs/models/Tag.pb.h"
#include "protobufs/models/User.pb.h"
#include "protobufs/models/Task.pb.h"
#include "protobufs/models/Organisation.pb.h"
#include "protobufs/models/ArchivedTask.pb.h"

class ModelGenerator
{
public:
    static Tag *GenerateTag(QSqlQuery *q);
    static User *GenerateUser(QSqlQuery *q);
    static Task *GenerateTask(QSqlQuery *q);
    static Organisation *GenerateOrg(QSqlQuery *q);
    static ArchivedTask *GenerateArchivedTask(QSqlQuery *q);

};

#endif // MODELGENERATOR_H
