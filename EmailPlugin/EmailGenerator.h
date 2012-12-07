#ifndef EMAILGENERATOR_H
#define EMAILGENERATOR_H

#include <QString>

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
    Email *generateEmail(TaskScoreEmail email_message);
    Email *generateEmail(OrgMembershipAccepted email_message);
    Email *generateEmail(OrgMembershipRefused email_message);
    Email *generateEmail(PasswordResetEmail email_message);
    Email *generateEmail(TaskArchived email_message);
    Email *generateEmail(TaskClaimed email_message);
    Email *generateEmail(TaskTranslationUploaded email_message);
    Email *generateEmail(UserTaskClaim email_message);

private:
    Email *generateErrorEmail(QString error_message);

};

#endif // EMAILGENERATOR_H
