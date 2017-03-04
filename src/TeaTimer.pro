#-------------------------------------------------
#
# Project created by QtCreator 2017-03-04T12:55:49
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = TeaTimer
TEMPLATE = app


SOURCES += main.cpp\
        gui/mainwindow.cpp \
    settings.cpp

HEADERS  += gui/mainwindow.h \
    settings.h

FORMS    += gui/mainwindow.ui
