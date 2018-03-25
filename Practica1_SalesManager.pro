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
    Tad/tadproducto.cpp \
    ListaProducto/listaproducto.cpp \
    ListaProducto/nodoproducto.cpp

HEADERS  += mainwindow.h \
    Tad/tadproducto.h \
    nodoproducto.h \
    listaproducto.h \
    ListaProducto/listaproducto.h \
    ListaProducto/nodoproducto.h

FORMS    += mainwindow.ui
