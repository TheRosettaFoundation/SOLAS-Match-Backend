#ifndef EMAILGENERATOR_H
#define EMAILGENERATOR_H

#include <QString>
#include <QQueue>
#include <QSharedPointer>
#include <QDebug>

#include <ctemplate/template.h>

#include "Email.h"
#include "EmailDefinitions.h"

#include "Common/ConfigParser.h"
#include "Common/MySQLHandler.h"

#include "Common/DataAccessObjects/UserDao.h"
#include "Common/DataAccessObjects/OrganisationDao.h"
#include "Common/DataAccessObjects/TaskDao.h"
#include "Common/DataAccessObjects/ProjectDao.h"

#include "Common/protobufs/models/User.pb.h"
#include "Common/protobufs/models/Task.pb.h"
#include "Common/protobufs/models/Project.pb.h"
#include "Common/protobufs/models/ArchivedTask.pb.h"
#include "Common/protobufs/models/Organisation.pb.h"

class IEmailGenerator
{
public:
    IEmailGenerator();
    QSharedPointer<Email> generateErrorEmail(QString error);

protected:
};

#endif // EMAILGENERATOR_H
