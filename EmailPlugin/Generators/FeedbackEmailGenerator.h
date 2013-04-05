#ifndef FEEDBACKEMAILGENERATOR_H
#define FEEDBACKEMAILGENERATOR_H

#include "../IEmailGenerator.h"

class FeedbackEmailGenerator : public IEmailGenerator
{
public:
    FeedbackEmailGenerator();
    void run();

};

#endif // FEEDBACKEMAILGENERATOR_H
