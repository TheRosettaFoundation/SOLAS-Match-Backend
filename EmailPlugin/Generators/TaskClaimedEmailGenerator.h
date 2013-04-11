#ifndef TASKCLAIMEDEMAILGENERATOR_H
#define TASKCLAIMEDEMAILGENERATOR_H

#include "../IEmailGenerator.h"
#include "Common/protobufs/emails/TaskClaimed.pb.h"

class TaskClaimedEmailGenerator : public IEmailGenerator
{
public:
    TaskClaimedEmailGenerator();
    void run();

};

#endif // TASKCLAIMEDEMAILGENERATOR_H
