#ifndef ICOMMAND_H
#define ICOMMAND_H

#include <QObject>
#include <QStringList>

class ICommand : public QObject
{
public:
    virtual ~ICommand() {}
    virtual void printHelp(QString appName) = 0;
    virtual bool isRequested(QStringList args) = 0;

public slots:
    virtual void execute() = 0;

signals:
    virtual void finished(QString response) = 0;

};

#endif // ICOMMAND_H
