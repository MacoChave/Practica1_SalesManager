#include "nodoregistro.h"

NodoRegistro::NodoRegistro()
{
    detalle = NULL;
    siguiente = NULL;
}

NodoRegistro::NodoRegistro(TADDetalle *value)
{
    detalle = value;
    siguiente = NULL;
}

NodoRegistro::~NodoRegistro()
{
    if (detalle != NULL)
        delete detalle;
    detalle = NULL;
    siguiente = NULL;
}

void NodoRegistro::setDetalle(TADDetalle *value)
{
    detalle = value;
}

TADDetalle *NodoRegistro::getDetalle()
{
    return detalle;
}

void NodoRegistro::setSiguiente(NodoRegistro *value)
{
    siguiente = value;
}

NodoRegistro *NodoRegistro::getSiguiente()
{
    return siguiente;
}

QString NodoRegistro::getNombreNodo()
{
    return detalle->getNombreNodo();
}

QString NodoRegistro::toString()
{
    return detalle->toString();
}
