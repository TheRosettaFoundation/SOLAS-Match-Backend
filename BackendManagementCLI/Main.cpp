#include <QtCore/QCoreApplication>

#include "ManagementApp.h"

#include <QTimer>
#include <QDebug>

int main(int argc, char* argv[])
{
    QCoreApplication app(argc, argv);

    ManagementApp mainApp(&app);
    QObject::connect(&mainApp, SIGNAL(finished()), &app, SLOT(quit()));
    QTimer::singleShot(0, &mainApp, SLOT(run()));

    return app.exec();
}
