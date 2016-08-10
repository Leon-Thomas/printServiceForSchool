#-------------------------------------------------
#
# Project created by QtCreator 2016-07-15T11:35:46
#
#-------------------------------------------------

QT       += core gui sql printsupport


greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = sias
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    query.cpp \
    printworker.cpp \
    mdisubwindow.cpp \
    previewwindow.cpp

HEADERS  += mainwindow.h \
    query.h \
    printworker.h \
    infodata.h \
    location.h \
    mdisubwindow.h \
    previewwindow.h

FORMS    += mainwindow.ui

QMAKE_CXXFLAGS += -std=c++11
