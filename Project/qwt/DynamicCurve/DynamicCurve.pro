#-------------------------------------------------
#
# Project created by QtCreator 2015-03-05T14:26:03
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = DynamicCurve
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    timescaledraw.cpp

HEADERS  += mainwindow.h \
    timescaledraw.h

FORMS    += mainwindow.ui


LIBS += -L"D:/QtInstall/Qt5.4.0/5.4/mingw491_32/lib" -lqwt
INCLUDEPATH += D:/QtInstall/Qt5.4.0/5.4/mingw491_32/include/Qwt
include (D:/QtInstall/Qt5.4.0/5.4/mingw491_32/include/Qwt/features/qwt.prf)

