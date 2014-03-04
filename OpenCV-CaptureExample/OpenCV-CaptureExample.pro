#-------------------------------------------------
#
# Project created by QtCreator 2014-03-03T17:37:05
#
#-------------------------------------------------

QT       += core

QT       -= gui

TARGET = OpenCV-CaptureExample
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app


SOURCES += main.cpp

LIBS += -lopencv_core \
-lopencv_highgui \
-lopencv_imgproc
