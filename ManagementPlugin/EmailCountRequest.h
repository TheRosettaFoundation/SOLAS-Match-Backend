#ifndef EMAILCOUNTREQUEST_H
#define EMAILCOUNTREQUEST_H

#include "IRequestInterface.h"

class EmailCountRequest : public IRequestInterface
{
public:
    EmailCountRequest();
    virtual ~EmailCountRequest();

    void run();

};

#endif // EMAILCOUNTREQUEST_H
