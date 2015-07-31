#ifndef USERCLAIMEDTASKLATEWARNINGDEADLINEPASSEDEMAILGENERATOR_H
#define USERCLAIMEDTASKLATEWARNINGDEADLINEPASSEDEMAILGENERATOR_H

#include "../IEmailGenerator.h"
#include "Common/protobufs/emails/UserClaimedTaskLateWarningDeadlinePassed.pb.h"

class UserClaimedTaskLateWarningDeadlinePassedEmailGenerator : IEmailGenerator
{
public:
    UserClaimedTaskLateWarningDeadlinePassedEmailGenerator();
    void run();

};

#endif // USERCLAIMEDTASKLATEWARNINGDEADLINEPASSEDEMAILGENERATOR_H
