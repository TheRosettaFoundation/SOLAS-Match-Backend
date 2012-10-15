#-------------------------------------------------
#
# Project created by QtCreator 2012-09-26T12:44:14
#
#-------------------------------------------------

QT       += core

QT       -= gui

TARGET = PluginHandler
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app

LIBS += -L../Common \
    -L/usr/local/lib -lamqpcpp

INCLUDEPATH += /usr/local/include

SOURCES += main.cpp \
    PluginLoader.cpp

HEADERS += \
    WorkerInterface.h \
    PluginLoader.h \
    JobInterface.h
