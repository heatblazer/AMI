QT += core
QT += network
QT += gui
QT += widgets

CONFIG += c++11

TARGET = sockets
CONFIG += console
CONFIG -= app_bundle

TEMPLATE = app

SOURCES += main.cpp \
    ami.cpp \
    ptt.cpp \
    amiinterface.cpp

HEADERS += \
    ami.h \
    ptt.h \
    amimsg.h \
    amiinterface.h
