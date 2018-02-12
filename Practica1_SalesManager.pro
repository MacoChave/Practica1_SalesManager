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
    ListaProducto/nodoproducto.cpp \
    ListaCliente/nodocliente.cpp \
    Tad/tadcliente.cpp \
    ListaCliente/listacliente.cpp \
    dialogeficiencia.cpp \
    ListaFactura/nodofactura.cpp \
    Tad/tadfactura.cpp \
    ListaFactura/listafactura.cpp \
    Tad/taddetalle.cpp \
    PilaReporte/nodoregistro.cpp \
    PilaReporte/piladetalle.cpp

HEADERS  += mainwindow.h \
    Tad/tadproducto.h \
    nodoproducto.h \
    listaproducto.h \
    ListaProducto/listaproducto.h \
    ListaProducto/nodoproducto.h \
    ListaCliente/nodocliente.h \
    Tad/tadcliente.h \
    ListaCliente/listacliente.h \
    dialogeficiencia.h \
    ListaFactura/nodofactura.h \
    Tad/tadfactura.h \
    listafactura.h \
    ListaFactura/listafactura.h \
    Tad/taddetalle.h \
    PilaReporte/nodoregistro.h \
    PilaReporte/piladetalle.h

FORMS    += mainwindow.ui \
    dialogeficiencia.ui
