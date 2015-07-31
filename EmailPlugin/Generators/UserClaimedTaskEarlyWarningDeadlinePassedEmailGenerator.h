#ifndef USERCLAIMEDTASKEARLYWARNINGDEADLINEPASSEDEMAILGENERATOR_H
#define USERCLAIMEDTASKEARLYWARNINGDEADLINEPASSEDEMAILGENERATOR_H

#include "../IEmailGenerator.h"
#include "Common/protobufs/emails/UserClaimedTaskEarlyWarningDeadlinePassed.pb.h"

class UserClaimedTaskEarlyWarningDeadlinePassedEmailGenerator : IEmailGenerator
{
public:
    UserClaimedTaskEarlyWarningDeadlinePassedEmailGenerator();
    void run();

};

#endif // USERCLAIMEDTASKEARLYWARNINGDEADLINEPASSEDEMAILGENERATOR_H
