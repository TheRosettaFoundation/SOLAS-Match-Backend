#ifndef TASKSCOREEMAILGENERATOR_H
#define TASKSCOREEMAILGENERATOR_H

#include "../IEmailGenerator.h"

class TaskScoreEmailGenerator : public IEmailGenerator
{
public:
    TaskScoreEmailGenerator() {}
    void run();

};

#endif
