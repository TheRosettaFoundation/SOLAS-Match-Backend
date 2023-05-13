#-------------------------------------------------
#
# Project created by QtCreator 2012-09-26T12:46:40
#
#-------------------------------------------------

! include( ../Common.pri ) {
    error( "Couldn't find the Common.pri file!" )
}

QT       += network sql

QT       -= gui

TARGET = Common

LIBS += -lprotobuf \
        -L/usr/local/lib

DEFINES += COMMON_LIBRARY

SOURCES += \
    ConfigParser.cpp \
    MySQLHandler.cpp \
    ModelGenerator.cpp \
    protobufs/models/User.pb.cc \
    DataAccessObjects/UserDao.cpp \
    DataAccessObjects/TagDao.cpp \
    protobufs/models/Tag.pb.cc \
    protobufs/models/Organisation.pb.cc \
    DataAccessObjects/OrganisationDao.cpp \
    protobufs/models/ArchivedTask.pb.cc \
    DataAccessObjects/TaskDao.cpp \
    protobufs/models/Task.pb.cc \
    protobufs/models/ArchivedProject.pb.cc \
    protobufs/models/Project.pb.cc \
    DataAccessObjects/ProjectDao.cpp \
    protobufs/models/Statistic.pb.cc \
    protobufs/models/Language.pb.cc \
    DataAccessObjects/LanguageDao.cpp \
    protobufs/models/Locale.pb.cc \
    protobufs/models/BannedUser.pb.cc \
    DataAccessObjects/AdminDao.cpp \
    protobufs/models/UserTaskStreamNotification.pb.cc \
    protobufs/models/Badge.pb.cc \
    DataAccessObjects/BadgeDao.cpp \

HEADERS +=\
    MySQLHandler.h \
    ConfigParser.h \
    ModelGenerator.h \
    protobufs/models/User.pb.h \
    DataAccessObjects/UserDao.h \
    DataAccessObjects/TagDao.h \
    protobufs/models/Tag.pb.h \
    protobufs/models/Organisation.pb.h \
    DataAccessObjects/OrganisationDao.h \
    protobufs/models/ArchivedTask.pb.h \
    DataAccessObjects/TaskDao.h \
    protobufs/models/Task.pb.h \
    protobufs/models/ArchivedProject.pb.h \
    protobufs/models/Project.pb.h \
    DataAccessObjects/ProjectDao.h \
    protobufs/models/Statistic.pb.h \
    DataAccessObjects/LanguageDao.h \
    protobufs/models/Language.pb.h \
    protobufs/models/Locale.pb.h \
    protobufs/models/BannedUser.pb.h \
    Definitions.h \
    DataAccessObjects/AdminDao.h \
    protobufs/models/UserTaskStreamNotification.pb.h \
    DataAccessObjects/BadgeDao.h \
    protobufs/models/Badge.pb.h \

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
