#-------------------------------------------------
#
# Project created by QtCreator 2014-03-04T11:43:57
#
#-------------------------------------------------

QT       += core

QT       -= gui

TARGET = OpenCV-GeometricTransformationExample
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app


SOURCES += main.cpp

LIBS += -lopencv_core -lopencv_highgui -lopencv_imgproc
