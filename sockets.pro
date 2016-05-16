QT += core
QT += network
QT -= gui

CONFIG += c++11

TARGET = sockets
CONFIG += console
CONFIG -= app_bundle

TEMPLATE = app

SOURCES += main.cpp \
    ami.cpp

HEADERS += \
    ami.h
