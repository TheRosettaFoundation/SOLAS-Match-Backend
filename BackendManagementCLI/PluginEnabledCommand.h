#ifndef PLUGINENABLEDCOMMAND_H
#define PLUGINENABLEDCOMMAND_H

#include "ICommand.h"

class PluginEnabledCommand : public ICommand
{
    Q_OBJECT

public:
    PluginEnabledCommand();
    ~PluginEnabledCommand();

    void printHelp(QString appName);
    bool isRequested(QStringList args);

public slots:
    void execute();

signals:
    void finished(QString response);

private:
    QString pluginName;

};

#endif // PLUGINENABLEDCOMMAND_H
