QT += core
QT -= gui

CONFIG += c++11

TARGET = Qprocesstest
CONFIG += console
CONFIG -= app_bundle

TEMPLATE = app

SOURCES += main.cpp \
    dlmanager.cpp \
    manifestcontrol.cpp \
    dlcontrol.cpp \
    manifestData.cpp \
    updatemanagement.cpp

HEADERS += \
    dlmanager.h \
    manifestcontrol.h \
    manifestData.h \
    dlcontrol.h \
    updatemanagement.h
