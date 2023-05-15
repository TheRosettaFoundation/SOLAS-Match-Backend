#ifndef USERTASKSTREAMEMAILGENERATOR_H
#define USERTASKSTREAMEMAILGENERATOR_H

#include "../IEmailGenerator.h"

class UserTaskStreamEmailGenerator : public IEmailGenerator
{
public:
    static void run(int user_id);
};

#endif // USERTASKSTREAMEMAILGENERATOR_H
