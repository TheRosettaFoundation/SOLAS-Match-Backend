#ifndef PASSWORDRESETEMAILGENERATOR_H
#define PASSWORDRESETEMAILGENERATOR_H

#include "../IEmailGenerator.h"

class PasswordResetEmailGenerator : public IEmailGenerator
{
public:
    void run(int user_id);
};


#endif // PASSWORDRESETEMAILGENERATOR_H
