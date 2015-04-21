#-------------------------------------------------
#
# Project created by QtCreator 2015-04-07T11:03:24
#
#-------------------------------------------------

QT += core gui
QT += xml

CONFIG += c++11

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = ie-methods-qt
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    iterationmethodpositive.cpp \
    qcustomplot.cpp \
    qwt_mml_document.cpp \
    qwt_mml_entity_table.cpp \
    formulaview.cpp \
    iterationmethodcommon.cpp \
    iterationmethoddirichletkernel.cpp \
    mathextensions.cpp \
    mathfunctions.cpp

HEADERS  += mainwindow.h \
    approximation.h \
    iterationmethodpositive.h \
    ietypes.h \
    qcustomplot.h \
    qwt_mml_document.h \
    qwt_mml_entity_table.h \
    formulaview.h \
    iterationmethodcommon.h \
    iterationmethoddirichletkernel.h \
    mathextensions.h \
    mathfunctions.h

FORMS    += mainwindow.ui
