#-------------------------------------------------
#
# Project created by QtCreator 2016-01-13T08:10:42
#
#-------------------------------------------------

QT       += core gui network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = TCPSerialTool
TEMPLATE = app


SOURCES += main.cpp\
        widget.cpp \
    dialog.cpp

HEADERS  += widget.h \
    dialog.h

FORMS    += widget.ui \
    dialog.ui
