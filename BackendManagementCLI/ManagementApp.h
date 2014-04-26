#ifndef MANAGEMENTAPP_H
#define MANAGEMENTAPP_H

#include <QtCore/QCoreApplication>

#include "ICommand.h"

class ManagementApp : public QObject
{
    Q_OBJECT

public:
    ManagementApp(QCoreApplication* parent);
    ~ManagementApp();

public slots:
    void run();
    void commandFinished(QString response);

signals:
    void finished();

private:
    void printHelp();
    void registerCommands();

    QCoreApplication *parent;

    QList<ICommand*> commandList;

};

#endif // MANAGEMENTAPP_H
