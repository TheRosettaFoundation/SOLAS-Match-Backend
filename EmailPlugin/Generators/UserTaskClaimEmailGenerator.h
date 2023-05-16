#ifndef USERTASKCLAIMEMAILGENERATOR_H
#define USERTASKCLAIMEMAILGENERATOR_H

#include "../IEmailGenerator.h"

class UserTaskClaimEmailGenerator
{
public:
    static void run(int user_id, int task_id);
};

#endif // USERTASKCLAIMEMAILGENERATOR_H
