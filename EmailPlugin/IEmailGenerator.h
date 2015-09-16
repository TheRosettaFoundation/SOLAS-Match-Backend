#ifndef EMAILGENERATOR_H
#define EMAILGENERATOR_H

#include <QString>
#include <QRunnable>
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

class IEmailGenerator : public QRunnable
{
public:
    IEmailGenerator();
    virtual void run() = 0;
    void setProtoBody(std::string proto);
    void setAMQPMessage(AMQPMessage *mess);
    void setEmailQueue(QSharedPointer<EmailQueue> emailQueue);
    QSharedPointer<Email> generateErrorEmail(QString error);

signals:
    void emailSent(bool success);

protected:
    std::string protoBody;
    QSharedPointer<EmailQueue> emailQueue;
    AMQPMessage *currentMessage;

};

#endif // EMAILGENERATOR_H
