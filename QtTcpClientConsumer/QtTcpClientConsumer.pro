#-------------------------------------------------
#
# Project created by QtCreator 2017-06-30T02:09:12
#
#-------------------------------------------------

QT       += core gui
QT       += network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = QtTcpClientConsumer
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    plotter.cpp

HEADERS  += mainwindow.h \
    plotter.h

FORMS    += mainwindow.ui
