#-------------------------------------------------
#
# Project created by QtCreator 2018-02-08T07:47:43
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Practica1_SalesManager
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    Parser/json.c

HEADERS  += mainwindow.h \
    Parser/json.h

FORMS    += mainwindow.ui
