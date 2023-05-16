#ifndef USERTASKREVOKEDGENERATOR_H
#define USERTASKREVOKEDGENERATOR_H

#include "../IEmailGenerator.h"

class UserTaskRevokedGenerator
{
public:
    static void run(int task_id, int claimant_id);
};

#endif // USERTASKREVOKEDGENERATOR_H
