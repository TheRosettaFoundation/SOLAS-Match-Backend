#ifndef PASSWORDRESETEMAILGENERATOR_H
#define PASSWORDRESETEMAILGENERATOR_H

#include "../IEmailGenerator.h"
#include "Common/protobufs/emails/PasswordResetEmail.pb.h"

class PasswordResetEmailGenerator : public IEmailGenerator
{
public:
    PasswordResetEmailGenerator();
    void run();

};


#endif // PASSWORDRESETEMAILGENERATOR_H
