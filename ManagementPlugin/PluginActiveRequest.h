#ifndef PLUGINACTIVEREQUEST_H
#define PLUGINACTIVEREQUEST_H

#include "IRequestInterface.h"

class PluginActiveRequest : public IRequestInterface
{
public:
    PluginActiveRequest();
    virtual ~PluginActiveRequest();

    virtual void run();
};

#endif // PLUGINACTIVEREQUEST_H
