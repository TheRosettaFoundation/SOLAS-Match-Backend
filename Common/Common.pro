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
    protobufs/emails/EmailMessage.pb.cc \
    protobufs/emails/TaskScoreEmail.pb.cc \
    protobufs/emails/OrgMembershipAccepted.pb.cc \
    protobufs/emails/OrgMembershipRefused.pb.cc \
    protobufs/emails/PasswordResetEmail.pb.cc \
    protobufs/emails/TaskArchived.pb.cc \
    protobufs/emails/TaskClaimed.pb.cc \
    protobufs/emails/TaskTranslationUploaded.pb.cc \
    protobufs/emails/UserTaskClaim.pb.cc \
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
    protobufs/requests/UserTaskScoreRequest.pb.cc \
    protobufs/requests/DeadlineCheckRequest.pb.cc \
    protobufs/emails/OrgTaskDeadlinePassed.pb.cc \
    protobufs/emails/UserClaimedTaskDeadlinePassed.pb.cc \
    protobufs/models/ArchivedProject.pb.cc \
    protobufs/models/Project.pb.cc

HEADERS +=\
    MySQLHandler.h \
    ConfigParser.h \
    MessagingClient.h \
    protobufs/emails/EmailMessage.pb.h \
    protobufs/emails/TaskScoreEmail.pb.h \
    protobufs/emails/OrgMembershipAccepted.pb.h \
    protobufs/emails/OrgMembershipRefused.pb.h \
    protobufs/emails/PasswordResetEmail.pb.h \
    protobufs/emails/TaskArchived.pb.h \
    protobufs/emails/TaskClaimed.pb.h \
    protobufs/emails/TaskTranslationUploaded.pb.h \
    protobufs/emails/UserTaskClaim.pb.h \
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
    protobufs/requests/UserTaskScoreRequest.pb.h \
    protobufs/requests/DeadlineCheckRequest.pb.h \
    protobufs/emails/OrgTaskDeadlinePassed.pb.h \
    protobufs/emails/UserClaimedTaskDeadlinePassed.pb.h \
    protobufs/models/ArchivedProject.pb.h \
    protobufs/models/Project.pb.h

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
