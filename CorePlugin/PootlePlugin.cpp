#include "PootlePlugin.h"

#include "Common/ConfigParser.h"

#include <QDebug>

PootlePlugin::PootlePlugin()
{
    // Default ctor
}

void PootlePlugin::run()
{
    qDebug() << "Running PootlePlugin";
    fsWatcher = QSharedPointer<QFileSystemWatcher>(new QFileSystemWatcher());

    ConfigParser settings;
    fsWatcher->addPath(settings.get("PootlePlugin.interface_directory"));

    connect(fsWatcher.data(), SIGNAL(directoryChanged(const QString&)), this, SLOT(directoryChanged(QString)));
}

void PootlePlugin::directoryChanged(QString location)
{
    qDebug() << "PootlePlugin: Witnessed change at " << location;
    qDebug() << "Handle all response data and delete processed data";
}

void PootlePlugin::setThreadPool(QThreadPool *tp)
{
    this->mThreadPool = tp;
}

bool PootlePlugin::isEnabled()
{
    return true;
}
