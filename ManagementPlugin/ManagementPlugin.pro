! include( ../Common.pri ) {
    error( Couldn't find the Common.pri file! )
}

QT       -= gui

TARGET = ManagementPlugin

TEMPLATE = lib

CONFIG += plugin

LIBS += -lprotobuf -L../Common -lCommon \
        -L/usr/local/lib -lamqpcpp -lrabbitmq \
        -lprotobuf

DESTDIR = ../plugins

DEFINES += MANAGEMENTPLUGIN_LIBRARY

HEADERS += \
    ManagementPlugin.h \
    IRequestInterface.h \
    PluginActiveRequest.h \
    ListPluginsHandler.h \
    EmailCountRequest.h

SOURCES += \
    ManagementPlugin.cpp \
    IRequestInterface.cpp \
    PluginActiveRequest.cpp \
    ListPluginsHandler.cpp \
    EmailCountRequest.cpp
