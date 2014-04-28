#ifndef LISTPLUGINSREQUEST_H
#define LISTPLUGINSREQUEST_H

#include "IRequestInterface.h"

class ListPluginsHandler : public IRequestInterface
{
public:
    ListPluginsHandler();
    virtual ~ListPluginsHandler();

    virtual void run();

};

#endif // LISTPLUGINSREQUEST_H
