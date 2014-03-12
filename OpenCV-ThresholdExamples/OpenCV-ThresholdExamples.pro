#-------------------------------------------------
#
# Project created by QtCreator 2014-03-12T09:52:03
#
#-------------------------------------------------

QT       += core

QT       -= gui

TARGET = OpenCV-ThresholdExamples
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app


SOURCES += main.cpp

LIBS += -lopencv_core \
-lopencv_highgui \
-lopencv_imgproc
