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
    approximation.cpp \
    iterationmethodnegative.cpp \
    iterationmethodpositive.cpp \
    complex.cpp

HEADERS  += mainwindow.h \
    approximation.h \
    iterationmethodnegative.h \
    iterationmethodpositive.h \
    complex.h \
    ietypes.h

FORMS    += mainwindow.ui
