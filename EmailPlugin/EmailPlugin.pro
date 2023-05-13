#-------------------------------------------------
#
# Project created by QtCreator 2012-10-31T09:53:35
#
#-------------------------------------------------

! include( ../Common.pri ) {
    error( "Couldn't find the Common.pri file!" )
}

QT       += core
QT       += network
QT       += core5compat

QT       -= gui

TARGET = EmailPlugin
TEMPLATE = lib

CONFIG += plugin

DESTDIR = ../plugins

LIBS += -L../Common -lCommon \
    -L/usr/local/lib \
    -L/usr/lib

DEFINES += EMAILPLUGIN_LIBRARY

SOURCES += emailplugin.cpp \
    Smtp.cpp \
    Email.cpp \
    qxtglobal.cpp \
    qxtsmtp.cpp \
    qxtmailmessage.cpp \
    qxtmailattachment.cpp \
    qxthmac.cpp

HEADERS += emailplugin.h \
    Smtp.h \
    Email.h \
    qxtglobal.h \
    qxtsmtp.h \
    qxtsmtp_p.h \
    qxtmail_p.h \
    qxtmailmessage.h \
    qxtmailattachment.h \
    qxthmac.h
