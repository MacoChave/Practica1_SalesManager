#ifndef PILADETALLE_H
#define PILADETALLE_H
#include <QPrinter>
#include <QPainter>
#include <QTableWidget>
#include <QDebug>
#include "nodoregistro.h"

class PilaDetalle
{
    NodoRegistro *cima;

    enum
    {
        CANTIDAD, CODIGO, PRODUCTO, PRECIO_U, DESCUENTO, TOTAL
    };
public:
    PilaDetalle();
    ~PilaDetalle();
    NodoRegistro *getCima();

    void push(TADDetalle *value);
    void pop();
    TADDetalle *peek();
    bool vacio();
    void limpiar();
    double cargarDetalle(QTableWidget *table);
    void exportar();
};

#endif // PILADETALLE_H
