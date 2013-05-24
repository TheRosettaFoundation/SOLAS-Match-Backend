#ifndef ORGFEEDBACKGENERATOR_H
#define ORGFEEDBACKGENERATOR_H

#include "../IEmailGenerator.h"

class OrgFeedbackGenerator : public IEmailGenerator
{
public:
    OrgFeedbackGenerator();
    void run();

};

#endif // ORGFEEDBACKGENERATOR_H
