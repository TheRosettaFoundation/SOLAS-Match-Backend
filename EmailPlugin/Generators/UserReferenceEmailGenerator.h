#ifndef USERREFERENCEEMAILGENERATOR_H
#define USERREFERENCEEMAILGENERATOR_H

#include "../IEmailGenerator.h"

class UserReferenceEmailGenerator : public IEmailGenerator
{
public:
    void run(int user_id);
};

#endif // USERREFERENCEEMAILGENERATOR_H
