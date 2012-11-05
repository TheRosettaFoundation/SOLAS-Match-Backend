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

CONFIG += plugin qxt

QXT    += network

DESTDIR = ../plugins

LIBS += -L../Common -lCommon \
    -L/usr/local/lib -lamqpcpp -lrabbitmq \
    -lqctemplate -lprotobuf

DEFINES += EMAILPLUGIN_LIBRARY

SOURCES += emailplugin.cpp \
    Smtp.cpp \
    EmailGenerator.cpp \
    Email.cpp

HEADERS += emailplugin.h\
        Smtp.h \
    EmailGenerator.h \
    Email.h
