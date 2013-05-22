#ifndef CLAIMEDTASKSOURCEUPDATEDGENERATOR_H
#define CLAIMEDTASKSOURCEUPDATEDGENERATOR_H

#include "../IEmailGenerator.h"

class ClaimedTaskSourceUpdatedGenerator : public IEmailGenerator
{
public:
    ClaimedTaskSourceUpdatedGenerator();
    void run();

};

#endif // CLAIMEDTASKSOURCEUPDATEDGENERATOR_H
