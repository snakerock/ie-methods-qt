#-------------------------------------------------
#
# Project created by QtCreator 2015-04-07T11:03:24
#
#-------------------------------------------------

QT       += core gui

CONFIG += c++11

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = ie-methods-qt
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    iterationmethodpositive.cpp \
    iterationmethoddirichletkernel.cpp \
    iterationmethodcommon.cpp \
    mathextensions.cpp

HEADERS  += mainwindow.h \
    approximation.h \
    iterationmethodpositive.h \
    ietypes.h \
    iterationmethoddirichletkernel.h \
    mathextensions.h \
    iterationmethodcommon.h

FORMS    += mainwindow.ui
