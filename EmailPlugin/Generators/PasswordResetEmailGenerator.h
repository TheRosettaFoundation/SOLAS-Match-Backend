#ifndef PASSWORDRESETEMAILGENERATOR_H
#define PASSWORDRESETEMAILGENERATOR_H

#include "../IEmailGenerator.h"

class PasswordResetEmailGenerator
{
public:
    static void run(int user_id);
};


#endif // PASSWORDRESETEMAILGENERATOR_H
