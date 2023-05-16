#ifndef TASKARCHIVEDEMAILGENERATOR_H
#define TASKARCHIVEDEMAILGENERATOR_H

#include "../IEmailGenerator.h"

class TaskArchivedEmailGenerator
{
public:
    static void run(int user_id, int task_id);
};

#endif // TASKARCHIVEDEMAILGENERATOR_H
