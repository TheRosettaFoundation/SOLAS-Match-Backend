#ifndef FEEDBACKEMAILGENERATOR_H
#define FEEDBACKEMAILGENERATOR_H

#include "../IEmailGenerator.h"
#include "Common/protobufs/emails/FeedbackEmail.pb.h"

class FeedbackEmailGenerator : public IEmailGenerator
{
public:
    FeedbackEmailGenerator();
    void run();

};

#endif // FEEDBACKEMAILGENERATOR_H
