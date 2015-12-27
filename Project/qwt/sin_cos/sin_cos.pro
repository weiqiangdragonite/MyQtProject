#-------------------------------------------------
#
# Project created by QtCreator 2015-03-06T17:09:03
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = sin_cos
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    plot.cpp

HEADERS  += mainwindow.h \
    plot.h

FORMS    += mainwindow.ui


LIBS += -L"C:/Qt/Qt5.4.0/5.4/mingw491_32/lib" -lqwtd
INCLUDEPATH += C:/Qt/Qt5.4.0/5.4/mingw491_32/include/Qwt
include (C:/Qt/Qt5.4.0/5.4/mingw491_32/include/Qwt/features/qwt.prf)
