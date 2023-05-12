! include( ../Common.pri ) {
    error( "Couldn't find the Common.pri file!" )
}

QT       -= gui

TARGET = PluginScheduler
TEMPLATE = lib

CONFIG += plugin

DESTDIR = ../plugins

LIBS += -L../Common -lCommon \
    -L/usr/local/lib \
    -lprotobuf

DEFINES += PLUGINSCHEDULER_LIBRARY

HEADERS += \
    PluginScheduler.h \
    TimedTask.h \

SOURCES += \
    PluginScheduler.cpp \
    TimedTask.cpp \
