#-------------------------------------------------
#
# Project created by QtCreator 2014-10-02T09:27:18
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = d2h
TEMPLATE = app


SOURCES += main.cpp\
        client.cpp \
        d2h.cpp \
    worker.cpp

HEADERS  += client.h \
    d2h.h \
    common.h \
    worker.h

FORMS    += d2h.ui

LIBS += -lws2_32

QMAKE_CXXFLAGS += -m32
