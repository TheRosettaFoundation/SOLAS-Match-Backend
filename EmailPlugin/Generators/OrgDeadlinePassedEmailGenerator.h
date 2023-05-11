#ifndef ORGDEADLINEPASSEDEMAILGENERATOR_H
#define ORGDEADLINEPASSEDEMAILGENERATOR_H

#include "../IEmailGenerator.h"

class OrgDeadlinePassedMailGenerator : public IEmailGenerator
{
public:
    static void run(int user_id, int task_id);
};

#endif // ORGDEADLINEPASSEDEMAILGENERATOR_H
