#ifndef USERCLAIMEDTASKLATEWARNINGDEADLINEPASSEDEMAILGENERATOR_H
#define USERCLAIMEDTASKLATEWARNINGDEADLINEPASSEDEMAILGENERATOR_H

#include "../IEmailGenerator.h"

class UserClaimedTaskLateWarningDeadlinePassedEmailGenerator : IEmailGenerator
{
public:
    static void run(int task_id, int translator_id);
};

#endif // USERCLAIMEDTASKLATEWARNINGDEADLINEPASSEDEMAILGENERATOR_H
