#-------------------------------------------------
#
# Project created by @spaceindaver
#
#-------------------------------------------------

! include( ../Common.pri ) {
    error( Couldn't find the Common.pri file! )
}

QT       -= gui

TARGET = CorePlugin

CONFIG += plugin

DESTDIR = ../plugins

LIBS += -L../Common -lCommon \
    -L/usr/local/lib -lamqpcpp -lrabbitmq

DEFINES += COREPLUGIN_LIBRARY

SOURCES += CorePlugin.cpp

HEADERS += CorePlugin.h
