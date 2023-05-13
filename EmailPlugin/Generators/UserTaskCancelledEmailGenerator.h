#ifndef USERTASKCANCELLEDEMAILGENERATOR_H
#define USERTASKCANCELLEDEMAILGENERATOR_H

#include "../IEmailGenerator.h"

class UserTaskCancelledEmailGenerator : public IEmailGenerator
{
public:
    static void run(int user_id, int task_id);
};

#endif // USERTASKCANCELLEDEMAILGENERATOR_H
