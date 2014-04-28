#include "ManagementApp.h"

#include "PluginEnabledCommand.h"
#include "PluginListCommand.h"

#include <QTimer>
#include <QDebug>

ManagementApp::ManagementApp(QCoreApplication *parent) :
    QObject(),
    parent(parent)
{
}

ManagementApp::~ManagementApp()
{
    foreach (ICommand* command, commandList)
    {
        delete command;
    }
}

void ManagementApp::run()
{
    QStringList args = parent->arguments();

    registerCommands();

    if (args.length() == 1 || args.at(1) == "-h" || args.at(1) == "--help")
    {
        printHelp();
        emit finished();
    }
    else
    {
        ICommand* requestedCommand = NULL;

        for (int i = 0; i < commandList.length() && requestedCommand == NULL; i++)
        {
            if (commandList.at(i)->isRequested(args))
            {
                requestedCommand = commandList.at(i);
            }
        }

        if (requestedCommand)
        {
            connect(requestedCommand, SIGNAL(finished(QString)), this, SLOT(commandFinished(QString)));
            QTimer::singleShot(0, requestedCommand, SLOT(execute()));
        }
        else
        {
            qDebug() << "Error: No matching commands found\n";
            printHelp();
            emit finished();
        }
    }
}

void ManagementApp::commandFinished(QString response)
{
    qDebug("%s", response.toStdString().c_str());
    emit finished();
}

void ManagementApp::registerCommands()
{
    // Order is important
    commandList.append(new PluginEnabledCommand());
    commandList.append(new PluginListCommand());
}

void ManagementApp::printHelp()
{
    QString appName = parent->arguments().at(0);
    appName = appName.mid(appName.lastIndexOf("/") + 1);

    qDebug("************************************************************************************");
    qDebug("* Welcome to the SOLAS Match Management Interface.                                 *");
    qDebug("* This tool is used to manage the SOLAS Match back end and query the service       *");
    qDebug("* The following is a list of commands currently supported by the management tool.  *");
    qDebug("************************************************************************************\n");

    foreach (ICommand* command, commandList) {
        command->printHelp(appName);
    }

    qDebug("--help | -h can be used to display this help text");
}
