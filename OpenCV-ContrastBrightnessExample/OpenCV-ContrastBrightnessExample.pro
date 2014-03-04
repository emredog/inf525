#-------------------------------------------------
#
# Project created by QtCreator 2014-03-04T10:27:17
#
#-------------------------------------------------

QT       += core

QT       -= gui

TARGET = OpenCV-ContrastBrightnessExample
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app


SOURCES += main.cpp

LIBS += -lopencv_core \
-lopencv_highgui
