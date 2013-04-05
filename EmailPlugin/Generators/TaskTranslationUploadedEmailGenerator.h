#ifndef TASKTRANSLATIONUPLOADEDEMAILGENERATOR_H
#define TASKTRANSLATIONUPLOADEDEMAILGENERATOR_H

#include "../IEmailGenerator.h"

class TaskTranslationUploadedEmailGenerator : public IEmailGenerator
{
public:
    TaskTranslationUploadedEmailGenerator();
    void run();

};

#endif // TASKTRANSLATIONUPLOADEDEMAILGENERATOR_H
