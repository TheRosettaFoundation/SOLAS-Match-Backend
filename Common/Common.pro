#-------------------------------------------------
#
# Project created by QtCreator 2012-09-26T12:46:40
#
#-------------------------------------------------

! include( ../Common.pri ) {
    error( Couldn't find the Common.pri file! )
}

QT       += network sql

QT       -= gui

TARGET = Common

DEFINES += COMMON_LIBRARY

SOURCES += \
    ConfigParser.cpp \
    MySQLHandler.cpp \
    MessagingClient.cpp \
    Models/User.cpp \
    Models/Task.cpp \
    Models/Tag.cpp

HEADERS +=\
    MySQLHandler.h \
    ConfigParser.h \
    MessagingClient.h \
    Models/User.h \
    Models/Task.h \
    Models/Tag.h

symbian {
    MMP_RULES += EXPORTUNFROZEN
    TARGET.UID3 = 0xE198F06F
    TARGET.CAPABILITY = 
    TARGET.EPOCALLOWDLLDATA = 1
    addFiles.sources = Common.dll
    addFiles.path = !:/sys/bin
    DEPLOYMENT += addFiles
}

unix:!symbian {
    maemo5 {
        target.path = /opt/usr/lib
    } else {
        target.path = /usr/lib
    }
    INSTALLS += target
}
