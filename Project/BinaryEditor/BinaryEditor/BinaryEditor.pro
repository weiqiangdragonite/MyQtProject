#-------------------------------------------------
#
# Project created by QtCreator 2014-02-11T12:38:44
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = BinaryEditor
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    binarytab.cpp

HEADERS  += mainwindow.h \
    binarytab.h

FORMS    += mainwindow.ui

RESOURCES += \
    icon.qrc
