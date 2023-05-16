#ifndef USERBADGEAWARDEDGENERATOR_H
#define USERBADGEAWARDEDGENERATOR_H

#include "../IEmailGenerator.h"

class UserBadgeAwardedGenerator
{
public:
    static void run(int user_id, int badge_id);
};

#endif // USERBADGEAWARDEDGENERATOR_H
