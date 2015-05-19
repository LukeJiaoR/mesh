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
    loadfilefor.cpp \
    bspline.cpp

HEADERS  +=  mainwindow.h \
             glwidget.h \
             loadfilefor.h \
             bspline.h


FORMS    +=  mainwindow.ui

