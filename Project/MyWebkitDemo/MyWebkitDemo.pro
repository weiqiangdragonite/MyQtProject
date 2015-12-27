#-------------------------------------------------
#
# Project created by QtCreator 2015-03-12T09:22:57
#
#-------------------------------------------------

QT       += core gui webkitwidgets

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = MyWebkitDemo
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    addressbar.cpp \
    htmlview.cpp

HEADERS  += mainwindow.h \
    addressbar.h \
    htmlview.h

FORMS    += mainwindow.ui
