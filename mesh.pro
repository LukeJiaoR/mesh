#-------------------------------------------------
#
# Project created by QtCreator 2015-03-05T13:26:00
#
#-------------------------------------------------

QT       += core gui  \
            opengl widgets


TARGET = mesh
TEMPLATE = app


SOURCES += main.cpp\
           glwidget.cpp \
           objloader.cpp \
           mainwindow.cpp

HEADERS  +=  mainwindow.h \
             objloader.h \
             glwidget.h


FORMS    +=  mainwindow.ui

