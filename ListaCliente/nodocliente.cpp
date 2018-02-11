#include "nodocliente.h"

NodoCliente::NodoCliente()
{
    item = NULL;
    siguiente = NULL;
}

NodoCliente::NodoCliente(TADCliente *value)
{
    item = value;
    siguiente = NULL;
}

NodoCliente::~NodoCliente()
{
    delete item;
    item = NULL;
    siguiente = NULL;
}

void NodoCliente::setItem(TADCliente *value)
{
    item = value;
}

TADCliente *NodoCliente::getItem()
{
    return item;
}

void NodoCliente::setSiguiente(NodoCliente *value)
{
    siguiente = value;
}

NodoCliente *NodoCliente::getSiguiente()
{
    return siguiente;
}

QString NodoCliente::getNombreNodo()
{
    return item->getNombreNodo();
}

QString NodoCliente::toString()
{
    return item->toString();
}
