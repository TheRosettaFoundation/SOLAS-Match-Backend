#-------------------------------------------------
#
# Project created by QtCreator 2012-09-27T15:08:16
#
#-------------------------------------------------

! include( ../Common.pri ) {
    error( Couldn't find the Common.pri file! )
}

QT       -= gui

TARGET = UserTaskScoreCalculator

CONFIG += plugin

DEFINES += USERTASKSCORECALCULATOR_LIBRARY

LIBS += -L../Common -lCommon \
    -L/usr/local/lib -lamqpcpp -lrabbitmq \
    -lqctemplate

DESTDIR = ../plugins

SOURCES += usertaskscorecalculator.cpp \
    CalculateTaskScoreJob.cpp

HEADERS += usertaskscorecalculator.h \
    CalculateTaskScoreJob.h

symbian {
    MMP_RULES += EXPORTUNFROZEN
    TARGET.UID3 = 0xEB429BE2
    TARGET.CAPABILITY = 
    TARGET.EPOCALLOWDLLDATA = 1
    addFiles.sources = UserTaskScoreCalculator.dll
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
