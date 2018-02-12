#ifndef PILADETALLE_H
#define PILADETALLE_H
#include "nodoregistro.h"

class PilaDetalle
{
    NodoRegistro *cima;
public:
    PilaDetalle();
    ~PilaDetalle();

    void push(TADDetalle *value);
    void pop();
    TADDetalle *peek();
    bool vacio();
    void limpiar();
};

#endif // PILADETALLE_H
