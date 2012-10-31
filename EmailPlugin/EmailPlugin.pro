#-------------------------------------------------
#
# Project created by QtCreator 2012-10-31T09:53:35
#
#-------------------------------------------------

! include( ../Common.pri ) {
    error( Couldn't find the Common.pri file! )
}

QT       += network

QT       -= gui

TARGET = EmailPlugin
TEMPLATE = lib

CONFIG += plugin

DESTDIR = ../plugins

LIBS += -L../Common -lCommon \
    -L/usr/local/lib -lamqpcpp -lrabbitmq \
    -lqctemplate

DEFINES += EMAILPLUGIN_LIBRARY

SOURCES += emailplugin.cpp \
    Smtp.cpp

HEADERS += emailplugin.h\
        EmailPlugin_global.h \
    Smtp.h
