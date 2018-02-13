#include "piladetalle.h"

PilaDetalle::PilaDetalle()
{
    cima = NULL;
}

PilaDetalle::~PilaDetalle()
{
    limpiar();
    cima = NULL;
}

NodoRegistro *PilaDetalle::getCima()
{
    return cima;
}

void PilaDetalle::push(TADDetalle *value)
{
    if (vacio())
    {
        cima = new NodoRegistro(value);
        return;
    }

    NodoRegistro *nuevo = new NodoRegistro(value);
    nuevo->setSiguiente(cima);
    cima = nuevo;
}

void PilaDetalle::pop()
{
    if (!vacio())
    {
        NodoRegistro *temp = cima;
        cima = temp->getSiguiente();

        delete temp;
        temp = NULL;
    }
}

TADDetalle *PilaDetalle::peek()
{
    return cima->getDetalle();
}

bool PilaDetalle::vacio()
{
    return cima == NULL;
}

void PilaDetalle::limpiar()
{
    while (!vacio())
        pop();
}
