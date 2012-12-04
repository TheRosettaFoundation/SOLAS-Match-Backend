#ifndef MODELGENERATOR_H
#define MODELGENERATOR_H

#include <QtSql/QSqlQuery>

#include "protobufs/models/User.pb.h"
#include "protobufs/models/Tag.pb.h"

class ModelGenerator
{
public:
    static User *GenerateUser(QSqlQuery *q);
    static Tag *GenerateTag(QSqlQuery *q);

};

#endif // MODELGENERATOR_H
