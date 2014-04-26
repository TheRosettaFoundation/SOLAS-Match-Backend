#include "PluginEnabledCommand.h"

#include <QDebug>

PluginEnabledCommand::PluginEnabledCommand() :
    pluginName("")
{
}

PluginEnabledCommand::~PluginEnabledCommand()
{
}

void PluginEnabledCommand::printHelp(QString appName)
{
    qDebug("%s --plugin-enabled <plugin-name>", appName.toStdString().c_str());
    qDebug("    This command determines if the specified plugin has been enabled");
    qDebug("    <plugin-name> is the name of the plugin being checked\n");
}

bool PluginEnabledCommand::isRequested(QStringList args)
{
    bool requested = false;
    if (args.length() == 3 && args.at(1) == "--plugin-enabled")
    {
        pluginName = args.at(2);
        requested = true;
    }
    return requested;
}

void PluginEnabledCommand::execute()
{
    emit finished("Executed Command");
}
