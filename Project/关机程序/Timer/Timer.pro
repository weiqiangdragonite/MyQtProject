#-------------------------------------------------
#
# Project created by QtCreator 2015-12-16T21:05:30
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Timer
TEMPLATE = app


SOURCES += main.cpp\
        widget.cpp

HEADERS  += widget.h

FORMS    += widget.ui
RC_FILE +=myapp.rc

RESOURCES += \
    rec.qrc
