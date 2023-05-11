#ifndef USERTASKDEADLINEEMAILGENERATOR_H
#define USERTASKDEADLINEEMAILGENERATOR_H

#include "../IEmailGenerator.h"

class UserTaskDeadlineEmailGenerator : IEmailGenerator
{
public:
    static void run(int task_id, int translator_id);
};

#endif // USERTASKDEADLINEEMAILGENERATOR_H
