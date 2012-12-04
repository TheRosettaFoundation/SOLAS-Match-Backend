#ifndef MODELGENERATOR_H
#define MODELGENERATOR_H

#include <QtSql/QSqlQuery>
#include "protobufs/models/User.pb.h"

class ModelGenerator
{
public:
    static User *GenerateUser(QSqlQuery *q);


};

#endif // MODELGENERATOR_H
