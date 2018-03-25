#include "nodoproducto.h"

NodoProducto::NodoProducto()
{
    item = NULL;
    anterior = NULL;
    siguiente = NULL;
}

NodoProducto::NodoProducto(TADProducto *value)
{
    item = value;
    anterior = NULL;
    siguiente = NULL;
}

NodoProducto::~NodoProducto()
{
    delete item;
    anterior = NULL;
    siguiente = NULL;
}

void NodoProducto::setItem(TADProducto *value)
{
    item = value;
}

TADProducto *NodoProducto::getItem()
{
    return item;
}

void NodoProducto::setAnterior(NodoProducto *value)
{
    anterior = value;
}

NodoProducto *NodoProducto::getAnterior()
{
    return anterior;
}

void NodoProducto::setSiguiente(NodoProducto *value)
{
    siguiente = value;
}

NodoProducto *NodoProducto::getSiguiente()
{
    return siguiente;
}


QString NodoProducto::toString()
{
    return item->toString();
}

QString NodoProducto::getNombreNodo()
{
    return item->getNombreNodo();
}
