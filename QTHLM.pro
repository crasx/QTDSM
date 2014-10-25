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
    QHLPing.cpp \
    QBasePing.cpp \
    mainwindow.cpp

HEADERS += \
    QHLPingStructs.h \
    QHLPing.h \
    QBasePing.h \
    mainwindow.h

OTHER_FILES += \
    ui.qml

FORMS += \
    mainwindow.ui
