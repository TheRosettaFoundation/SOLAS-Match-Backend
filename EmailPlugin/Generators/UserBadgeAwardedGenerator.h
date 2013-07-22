#ifndef USERBADGEAWARDEDGENERATOR_H
#define USERBADGEAWARDEDGENERATOR_H

#include "../IEmailGenerator.h"

class UserBadgeAwardedGenerator : public IEmailGenerator
{
public:
    UserBadgeAwardedGenerator();
    void run();

};

#endif // USERBADGEAWARDEDGENERATOR_H
