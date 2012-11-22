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

LIBS += -lprotobuf

DEFINES += COMMON_LIBRARY

SOURCES += \
    ConfigParser.cpp \
    MySQLHandler.cpp \
    MessagingClient.cpp \
    Models/User.cpp \
    Models/Task.cpp \
    Models/Tag.cpp \
    protobufs/emails/EmailMessage.pb.cc \
    protobufs/emails/TaskScoreEmail.pb.cc \
    protobufs/emails/OrgMembershipAccepted.pb.cc \
    protobufs/emails/OrgMembershipRefused.pb.cc \
    protobufs/emails/PasswordResetEmail.pb.cc \
    protobufs/emails/TaskArchived.pb.cc \
    protobufs/emails/TaskClaimed.pb.cc \
    protobufs/emails/TaskTranslationUploaded.pb.cc \
    protobufs/emails/UserTaskClaim.pb.cc \
    Models/Org.cpp \
    Models/ArchivedTask.cpp

HEADERS +=\
    MySQLHandler.h \
    ConfigParser.h \
    MessagingClient.h \
    Models/User.h \
    Models/Task.h \
    Models/Tag.h \
    protobufs/emails/EmailMessage.pb.h \
    protobufs/emails/TaskScoreEmail.pb.h \
    protobufs/emails/OrgMembershipAccepted.pb.h \
    protobufs/emails/OrgMembershipRefused.pb.h \
    protobufs/emails/PasswordResetEmail.pb.h \
    protobufs/emails/TaskArchived.pb.h \
    protobufs/emails/TaskClaimed.pb.h \
    protobufs/emails/TaskTranslationUploaded.pb.h \
    protobufs/emails/UserTaskClaim.pb.h \
    Models/Org.h \
    Models/ArchivedTask.h

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
