#ifndef EMAILGENERATOR_H
#define EMAILGENERATOR_H

#include <QString>
#include <QSharedPointer>

#include "Email.h"
#include "Common/protobufs/emails/TaskScoreEmail.pb.h"
#include "Common/protobufs/emails/OrgMembershipAccepted.pb.h"
#include "Common/protobufs/emails/OrgMembershipRefused.pb.h"
#include "Common/protobufs/emails/PasswordResetEmail.pb.h"
#include "Common/protobufs/emails/TaskArchived.pb.h"
#include "Common/protobufs/emails/TaskClaimed.pb.h"
#include "Common/protobufs/emails/TaskTranslationUploaded.pb.h"
#include "Common/protobufs/emails/UserTaskClaim.pb.h"

class EmailGenerator
{
public:
    EmailGenerator();
    QSharedPointer<Email> generateEmail(TaskScoreEmail email_message);
    QSharedPointer<Email> generateEmail(OrgMembershipAccepted email_message);
    QSharedPointer<Email> generateEmail(OrgMembershipRefused email_message);
    QSharedPointer<Email> generateEmail(PasswordResetEmail email_message);
    QSharedPointer<Email> generateEmail(TaskArchived email_message);
    QSharedPointer<Email> generateEmail(TaskClaimed email_message);
    QSharedPointer<Email> generateEmail(TaskTranslationUploaded email_message);
    QSharedPointer<Email> generateEmail(UserTaskClaim email_message);

private:
    QSharedPointer<Email> generateErrorEmail(QString error_message);

};

#endif // EMAILGENERATOR_H
