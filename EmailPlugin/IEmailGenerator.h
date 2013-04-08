#ifndef EMAILGENERATOR_H
#define EMAILGENERATOR_H

#include <QString>
#include <QRunnable>
#include <QQueue>
#include <QSharedPointer>

#include "Email.h"
#include "Common/protobufs/emails/TaskScoreEmail.pb.h"
#include "Common/protobufs/emails/OrgMembershipAccepted.pb.h"
#include "Common/protobufs/emails/OrgMembershipRefused.pb.h"
#include "Common/protobufs/emails/OrgTaskDeadlinePassed.pb.h"
#include "Common/protobufs/emails/PasswordResetEmail.pb.h"
#include "Common/protobufs/emails/TaskArchived.pb.h"
#include "Common/protobufs/emails/TaskClaimed.pb.h"
#include "Common/protobufs/emails/TaskTranslationUploaded.pb.h"
#include "Common/protobufs/emails/UserTaskClaim.pb.h"
#include "Common/protobufs/emails/UserClaimedTaskDeadlinePassed.pb.h"
#include "Common/protobufs/emails/FeedbackEmail.pb.h"

#include "Common/ConfigParser.h"
#include "Common/MySQLHandler.h"

#include <QUuid>
#include <QDebug>

#include <ctemplate/template.h>

#include "Definitions.h"

#include "Common/MySQLHandler.h"
#include "Common/ConfigParser.h"

#include "Common/DataAccessObjects/UserDao.h"
#include "Common/DataAccessObjects/OrganisationDao.h"
#include "Common/DataAccessObjects/TaskDao.h"
#include "Common/DataAccessObjects/ProjectDao.h"

#include "Common/protobufs/models/User.pb.h"
#include "Common/protobufs/models/Task.pb.h"
#include "Common/protobufs/models/Project.pb.h"
#include "Common/protobufs/models/ArchivedTask.pb.h"
#include "Common/protobufs/models/Organisation.pb.h"

#define TEMPLATE_DIRECTORY "/etc/SOLAS-Match/templates/"

class IEmailGenerator : public QRunnable
{
public:
    IEmailGenerator();
    virtual void run() = 0;
    void setProtoBody(QString proto);
    void setAMQPMessage(AMQPMessage *mess);
    void setEmailQueue(QSharedPointer<EmailQueue> emailQueue);
    QSharedPointer<Email> generateErrorEmail(QString error);

signals:
    void emailSent(bool success);

protected:
    QString protoBody;
    QSharedPointer<EmailQueue> emailQueue;
    AMQPMessage *currentMessage;

};

#endif // EMAILGENERATOR_H
