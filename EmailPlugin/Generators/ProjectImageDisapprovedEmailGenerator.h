#ifndef PROJECTIMAGEDISAPPROVEDEMAILGENERATOR_H
#define PROJECTIMAGEDISAPPROVEDEMAILGENERATOR_H

#include "../IEmailGenerator.h"

class ProjectImageDisapprovedEmailGenerator  : public IEmailGenerator
{
public:
    static void run(int user_id, int project_id);
};

#endif // PROJECTIMAGEDISAPPROVEDEMAILGENERATOR_H
