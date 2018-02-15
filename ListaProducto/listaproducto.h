#ifndef LISTAPRODUCTO_H
#define LISTAPRODUCTO_H
#include <QString>
#include <QFile>
#include <QTableWidget>
#include <QTextStream>
#include <iostream>
#include "nodoproducto.h"
#include "Tad/tadproducto.h"

class ListaProducto
{
    NodoProducto *primero;
    NodoProducto *ultimo;

    enum
    {
        CODIGO, NOMBRE, PRECIO, DESCRIPCION
    };

    bool agregar(NodoProducto *actual, NodoProducto *nuevo);
    NodoProducto *buscar(NodoProducto *actual, QString value);
public:
    ListaProducto();
    ~ListaProducto();

    void setPrimero(NodoProducto *value);
    NodoProducto *getPrimero();
    void setUltimo(NodoProducto *value);
    NodoProducto *getUltimo();

    bool vacio();
    bool agregar(TADProducto *producto);
    NodoProducto *buscar(QString value);
    TADProducto *obtener(QString value);
    bool eliminar(QString value);
    void graficar();
    void cargarDetalle(QTableWidget *table);
    bool agregarPrimero(TADProducto *producto);
    bool agregarUltimo(TADProducto *producto);
    int contar();
};

#endif // LISTAPRODUCTO_H
