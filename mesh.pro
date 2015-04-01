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
           mainwindow.cpp \
    loadforobj.cpp \
    objloader.cpp \
    loadfilefor.cpp

HEADERS  +=  mainwindow.h \
             glwidget.h \
    loadforobj.h \
    objloader.h \
    loadfilefor.h


FORMS    +=  mainwindow.ui

