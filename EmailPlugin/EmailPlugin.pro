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
    -lprotobuf -lctemplate

DEFINES += EMAILPLUGIN_LIBRARY

SOURCES += emailplugin.cpp \
    Smtp.cpp \
    Email.cpp \
    IEmailGenerator.cpp \
    Generators/OrgMembershipAcceptedGenerator.cpp \
    Generators/OrgMembershipRefusedEmailGenerator.cpp \
    Generators/TaskScoreEmailGenerator.cpp \
    Generators/PasswordResetEmailGenerator.cpp \
    Generators/TaskArchivedEmailGenerator.cpp \
    Generators/TaskClaimedEmailGenerator.cpp \
    Generators/TaskTranslationUploadedEmailGenerator.cpp \
    Generators/UserTaskClaimEmailGenerator.cpp \
    Generators/FeedbackEmailGenerator.cpp \
    Generators/OrgDeadlinePassedEmailGenerator.cpp \
    Generators/UserTaskDeadlineEmailGenerator.cpp \
    Generators/UserTaskStreamEmailGenerator.cpp \
    Generators/EmailVerificationGenerator.cpp

HEADERS += emailplugin.h\
        Smtp.h \
    Email.h \
    Generators/TaskScoreEmailGenerator.h \
    IEmailGenerator.h \
    Generators/OrgMembershipAcceptedGenerator.h \
    Generators/OrgMembershipRefusedEmailGenerator.h \
    Definitions.h \
    Generators/PasswordResetEmailGenerator.h \
    Generators/TaskArchivedEmailGenerator.h \
    Generators/TaskClaimedEmailGenerator.h \
    Generators/TaskTranslationUploadedEmailGenerator.h \
    Generators/UserTaskClaimEmailGenerator.h \
    Generators/FeedbackEmailGenerator.h \
    Generators/OrgDeadlinePassedEmailGenerator.h \
    Generators/UserTaskDeadlineEmailGenerator.h \
    Generators/UserTaskStreamEmailGenerator.h \
    Generators/EmailVerificationGenerator.h
