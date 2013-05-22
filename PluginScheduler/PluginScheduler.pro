! include( ../Common.pri ) {
    error( "Couldn't find the Common.pri file!" )
}

QT       -= gui

TARGET = PluginScheduler
TEMPLATE = lib

CONFIG += plugin

DESTDIR = ../plugins

LIBS += -L../Common -lCommon
LIBS += -lprotobuf -L../lib/ -lamqpcpp -lrabbitmq
INCLUDEPATH += ../include . ..
DEFINES += PLUGINSCHEDULER_LIBRARY

HEADERS += \
    PluginScheduler.h \
    TimedTask.h \
    RequestGenerator.h

SOURCES += \
    PluginScheduler.cpp \
    TimedTask.cpp \
    RequestGenerator.cpp
