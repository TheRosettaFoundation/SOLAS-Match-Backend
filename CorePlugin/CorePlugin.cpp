#include "CorePlugin.h"

#include <QThread>
#include <QDebug>

#include "Common/ConfigParser.h"

Q_EXPORT_PLUGIN2(CorePlugin, CorePlugin)

CorePlugin::CorePlugin()
{
    ConfigParser settings;
    enabled = (QString::compare("y", settings.get("CorePlugin.enabled")) == 0);
}

void CorePlugin::run()
{
    qDebug() << "CorePlugin::Starting new Thread " << this->thread()->currentThreadId();
    qDebug() << "CorePlugin: Start core listeners here";
}

void CorePlugin::setThreadPool(QThreadPool *tp)
{
    this->mThreadPool = tp;
}

bool CorePlugin::isEnabled()
{
    return this->enabled;
}
