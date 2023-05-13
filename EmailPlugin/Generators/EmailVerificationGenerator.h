#ifndef EMAILVERIFICATIONGENERATOR_H
#define EMAILVERIFICATIONGENERATOR_H

#include "../IEmailGenerator.h"

class EmailVerificationGenerator : public IEmailGenerator
{
public:
    static void run(int user_id);
};

#endif // EMAILVERIFICATIONGENERATOR_H
