#ifndef TASKTRANSLATIONUPLOADEDEMAILGENERATOR_H
#define TASKTRANSLATIONUPLOADEDEMAILGENERATOR_H

#include "../IEmailGenerator.h"

class TrackedTaskUploadedEmailGenerator
{
public:
    static void run(int user_id, int task_id, int translator_id, int revision_task_id);
};

#endif // TASKTRANSLATIONUPLOADEDEMAILGENERATOR_H
