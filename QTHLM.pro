#-------------------------------------------------
#
# Project created by QtCreator 2014-10-08T22:30:39
#
#-------------------------------------------------

QT       += core

QT       += network

QT       -= gui

QT += qml quick widgets



TARGET = QTHLM
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app


SOURCES += main.cpp \
    mainwindow.cpp \
    ServerDisplay.cpp \
    tablemodel.cpp\
    pingers/QBasePing.cpp \
    pingers/QHLPing.cpp

HEADERS += \
    QBasePing.h \
    mainwindow.h \
    ServerDisplay.h \
    tablemodel.h \
    pingers/QBasePing.h \
    pingers/QHLPing.h \
    pingers/QHLPingStructs.h \
    pingers/includeAll.h

OTHER_FILES += \
    ui.qml

FORMS += \
    mainwindow.ui \
    ServerDisplay.ui
