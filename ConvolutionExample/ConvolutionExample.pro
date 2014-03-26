#-------------------------------------------------
#
# Project created by QtCreator 2014-03-16T15:47:04
#
#-------------------------------------------------

QT       += core

QT       -= gui

TARGET = ConvolutionExample
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app


SOURCES += main.cpp

LIBS += -lopencv_highgui -lopencv_imgproc -lopencv_core
