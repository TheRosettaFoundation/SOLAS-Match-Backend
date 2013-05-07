#ifndef BANNEDLOGINGENERATOR_H
#define BANNEDLOGINGENERATOR_H

#include "../IEmailGenerator.h"
#include "Common/protobufs/emails/BannedLogin.pb.h"

class BannedLoginGenerator : public IEmailGenerator
{
public:
    BannedLoginGenerator();
    void run();

};

#endif // BANNEDLOGINGENERATOR_H
