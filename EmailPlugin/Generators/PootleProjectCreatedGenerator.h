#ifndef POOTLEPROJECTCREATEDGENERATOR_H
#define POOTLEPROJECTCREATEDGENERATOR_H

#include "../IEmailGenerator.h"

class PootleProjectCreatedGenerator : public IEmailGenerator
{
public:
    PootleProjectCreatedGenerator();
    void run();

};

#endif // POOTLEPROJECTCREATEDGENERATOR_H
