#ifndef NODOPRODUCTO_H
#define NODOPRODUCTO_H
#include "Tad/tadproducto.h"
#include <QString>

class NodoProducto
{
    TADProducto *item;
    NodoProducto *anterior;
    NodoProducto *siguiente;
public:
    NodoProducto();
    NodoProducto(TADProducto *value);
    ~NodoProducto();

    void setItem(TADProducto *value);
    TADProducto *getItem();
    void setAnterior(NodoProducto *value);
    NodoProducto *getAnterior();
    void setSiguiente(NodoProducto *value);
    NodoProducto *getSiguiente();

    QString toString();
    QString getNombreNodo();
};

#endif // NODOPRODUCTO_H
