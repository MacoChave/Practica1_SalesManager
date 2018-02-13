#ifndef PILADETALLE_H
#define PILADETALLE_H
#include <QPrinter>
#include <QPainter>
#include "nodoregistro.h"

class PilaDetalle
{
    NodoRegistro *cima;
public:
    PilaDetalle();
    ~PilaDetalle();
    NodoRegistro *getCima();

    void push(TADDetalle *value);
    void pop();
    TADDetalle *peek();
    bool vacio();
    void limpiar();
};

#endif // PILADETALLE_H
