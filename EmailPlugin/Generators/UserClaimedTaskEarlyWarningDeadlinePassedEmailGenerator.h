#ifndef USERCLAIMEDTASKEARLYWARNINGDEADLINEPASSEDEMAILGENERATOR_H
#define USERCLAIMEDTASKEARLYWARNINGDEADLINEPASSEDEMAILGENERATOR_H

#include "../IEmailGenerator.h"

class UserClaimedTaskEarlyWarningDeadlinePassedEmailGenerator : IEmailGenerator
{
public:
    static void run(int task_id, int translator_id);
};

#endif // USERCLAIMEDTASKEARLYWARNINGDEADLINEPASSEDEMAILGENERATOR_H
