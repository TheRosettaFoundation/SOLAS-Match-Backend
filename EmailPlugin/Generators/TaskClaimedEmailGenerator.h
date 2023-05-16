#ifndef TASKCLAIMEDEMAILGENERATOR_H
#define TASKCLAIMEDEMAILGENERATOR_H

#include "../IEmailGenerator.h"

class TaskClaimedEmailGenerator
{
public:
    static void run(int user_id, int task_id, int claimant_id);
};

#endif // TASKCLAIMEDEMAILGENERATOR_H
