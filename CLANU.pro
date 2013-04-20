TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle

QT       += core gui widgets

SOURCES += main.cpp \
    haar.cpp \
    mainwindow.cpp

TARGET = haar

HEADERS += \
    haar.h \
    mainwindow.h

FORMS += \
    mainwindow.ui

