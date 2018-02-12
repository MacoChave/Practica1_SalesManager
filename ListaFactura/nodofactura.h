#ifndef NODOFACTURA_H
#define NODOFACTURA_H
#include <QString>
#include "Tad/tadfactura.h"

class NodoFactura
{
    TADFactura *item;
    NodoFactura *anterior;
    NodoFactura *siguiente;
public:
    NodoFactura();
    NodoFactura(TADFactura *value);
    ~NodoFactura();

    void setItem(TADFactura *value);
    TADFactura *getItem();
    void setAnterior(NodoFactura *value);
    NodoFactura *getAnterior();
    void setSiguiente(NodoFactura *value);
    NodoFactura *getSiguiente();

    QString getNombreNodo();
    QString toString();
};

#endif // NODOFACTURA_H
