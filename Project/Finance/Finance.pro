#-------------------------------------------------
#
# Project created by QtCreator 2013-12-02T14:26:34
#
#-------------------------------------------------

QT       += core gui sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Finance
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    adddialog.cpp \
    inoutdialog.cpp \
    moneydialog.cpp \
    consumedialog.cpp

HEADERS  += mainwindow.h \
    adddialog.h \
    inoutdialog.h \
    moneydialog.h \
    consumedialog.h \
    mystruct.h

FORMS    += mainwindow.ui \
    adddialog.ui \
    inoutdialog.ui \
    moneydialog.ui \
    consumedialog.ui
