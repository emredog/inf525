#-------------------------------------------------
#
# Project created by QtCreator 2014-03-19T09:35:16
#
#-------------------------------------------------

QT       += core

QT       -= gui

TARGET = PlotHistogram
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app


SOURCES += main.cpp

LIBS += -lopencv_core -lopencv_highgui -lopencv_imgproc
