QT       += core

QT       -= gui

TARGET = SolasManagementCLI
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app

LIBS += -L../Common -lCommon -L/usr/local/lib \
        -lamqpcpp -lrabbitmq -lprotobuf

INCLUDEPATH += /usr/local/include . ..

SOURCES += \
    Main.cpp \
    ManagementApp.cpp \
    PluginEnabledCommand.cpp \
    PluginListCommand.cpp \
    EmailCountCommand.cpp

HEADERS += \
    ManagementApp.h \
    ICommand.h \
    PluginEnabledCommand.h \
    PluginListCommand.h \
    EmailCountCommand.h
