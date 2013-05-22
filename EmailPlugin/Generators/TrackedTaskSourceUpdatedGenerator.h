#ifndef TRACKEDTASKSOURCEUPDATEDGENERATOR_H
#define TRACKEDTASKSOURCEUPDATEDGENERATOR_H

#include "../IEmailGenerator.h"

class TrackedTaskSourceUpdatedGenerator : public IEmailGenerator
{
public:
    TrackedTaskSourceUpdatedGenerator();
    void run();

};

#endif // TRACKEDTASKSOURCEUPDATEDGENERATOR_H
