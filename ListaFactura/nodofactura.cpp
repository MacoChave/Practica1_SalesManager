#include "nodofactura.h"

NodoFactura::NodoFactura()
{
    item = NULL;
    anterior = NULL;
    siguiente = NULL;
}

NodoFactura::NodoFactura(TADFactura *value)
{
    item = value;
    anterior = NULL;
    siguiente = NULL;
}

NodoFactura::~NodoFactura()
{
    if (item != NULL)
        delete item;
    item = NULL;
    anterior = NULL;
    siguiente = NULL;
}

void NodoFactura::setItem(TADFactura *value)
{
    item = value;
}

TADFactura *NodoFactura::getItem()
{
    return item;
}

void NodoFactura::setAnterior(NodoFactura *value)
{
    anterior = value;
}

NodoFactura *NodoFactura::getAnterior()
{
    return anterior;
}

void NodoFactura::setSiguiente(NodoFactura *value)
{
    siguiente = value;
}

NodoFactura *NodoFactura::getSiguiente()
{
    return siguiente;
}

QString NodoFactura::getNombreNodo()
{
    return item->getNombreNodo();
}

QString NodoFactura::toString()
{
    return item->toString();
}
