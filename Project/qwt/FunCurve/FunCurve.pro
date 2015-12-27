#-------------------------------------------------
#
# Project created by QtCreator 2015-03-04T17:03:59
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = FunCurve
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp

HEADERS  += mainwindow.h

FORMS    += mainwindow.ui


LIBS += -L"D:/Qt/Qt5.4.0/5.4/mingw491_32/lib" -lqwtd
INCLUDEPATH += D:/Qt/Qt5.4.0/5.4/mingw491_32/include/Qwt
include (D:/Qt/Qt5.4.0/5.4/mingw491_32/include/Qwt/features/qwt.prf)
