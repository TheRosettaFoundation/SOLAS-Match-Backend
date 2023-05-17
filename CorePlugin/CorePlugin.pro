#-------------------------------------------------
#
# Project created by @spaceindaver
#
#-------------------------------------------------

! include( ../Common.pri ) {
    error( "Couldn't find the Common.pri file!" )
}

QT       -= gui

TARGET = CorePlugin

TEMPLATE = lib

CONFIG += plugin

DESTDIR = ../plugins

LIBS += -L../Common -lCommon \
    -L/usr/local/lib -lprotobuf -lctemplate \
    -L/usr/lib

DEFINES += COREPLUGIN_LIBRARY

SOURCES += CorePlugin.cpp \
    UserQueueHandler.cpp

HEADERS += CorePlugin.h \
    UserQueueHandler.h
