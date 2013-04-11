#ifndef TASKSCOREEMAILGENERATOR_H
#define TASKSCOREEMAILGENERATOR_H

#include "../IEmailGenerator.h"
#include "Common/protobufs/emails/TaskScoreEmail.pb.h"

class TaskScoreEmailGenerator : public IEmailGenerator
{
public:
    TaskScoreEmailGenerator() {}
    void run();

};

#endif
