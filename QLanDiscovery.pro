#-------------------------------------------------
#
# Project created by QtCreator 2012-06-29T11:01:08
#
#-------------------------------------------------

QT       += core gui network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += debug

LIBS += -lpam -lpam_misc

TARGET = QLanDiscovery
TEMPLATE = app


SOURCES += main.cpp\
           dialog.cpp \
           hostqueue.cpp \
           pingprocess.cpp \
           listview.cpp \
           nmapprocess.cpp \
           qlandiscoverysettings.cpp

HEADERS  += dialog.h \
            hostqueue.h \
            pingprocess.h \
            listview.h \
            nmapprocess.h \
            qlandiscoverysettings.h
