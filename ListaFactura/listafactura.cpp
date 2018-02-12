#include "listafactura.h"

bool ListaFactura::agregar(NodoFactura *actual, TADFactura *value)
{
    if (actual != NULL)
    {
        if (actual->getItem()->comparar(value) > 0)
        {
            NodoFactura *nuevo = new NodoFactura(value);
            nuevo->setSiguiente(actual);
            actual->getAnterior()->setSiguiente(nuevo);
            nuevo->setAnterior(actual->getAnterior());
            actual->setAnterior(nuevo);

            return true;
        }

        if (actual->getItem()->comparar(value) == 0
                || actual->getAnterior()->getItem()->comparar(value) == 0)
            return false;

        return agregar(actual->getSiguiente(), value);
    }

    return false;
}

NodoFactura *ListaFactura::buscar(NodoFactura *actual, QString serie, int correlativo)
{
    if (actual != NULL)
    {
        if (actual->getItem()->comparar(serie, correlativo) == 0)
            return actual;

        if (actual->getItem()->comparar(serie, correlativo) < 0)
            return buscar(actual->getSiguiente(), serie, correlativo);
    }

    return NULL;
}

ListaFactura::ListaFactura()
{
    primero = NULL;
    ultimo = NULL;
}

ListaFactura::~ListaFactura()
{
    NodoFactura *temp = primero;

    while (temp != NULL)
    {
        primero = temp->getSiguiente();
        delete temp;
        temp = primero;
    }

    ultimo = NULL;
}

bool ListaFactura::vacio()
{
    return primero == NULL && ultimo == NULL;
}

bool ListaFactura::agregar(TADFactura *value)
{

    if (vacio())
    {
        NodoFactura *nuevo = new NodoFactura(value);
        primero = ultimo = nuevo;

        return true;
    }

    if (primero->getItem()->comparar(value) > 0)
        return agregarPrimero(value);

    if (ultimo->getItem()->comparar(value) < 0)
        return agregarUltimo(value);


    return agregar(primero->getSiguiente(), value);
}

bool ListaFactura::agregarPrimero(TADFactura *value)
{
    NodoFactura *nuevo = new NodoFactura(value);

    if (vacio())
    {
        primero = ultimo = nuevo;

        return true;
    }

    nuevo->setSiguiente(primero);
    primero->setAnterior(nuevo);
    primero = nuevo;

    return true;
}

bool ListaFactura::agregarUltimo(TADFactura *value)
{
    NodoFactura *nuevo = new NodoFactura(value);

    if (vacio())
    {
        primero = ultimo = nuevo;

        return true;
    }

    nuevo->setAnterior(ultimo);
    ultimo->setSiguiente(nuevo);
    ultimo = nuevo;

    return true;
}

NodoFactura *ListaFactura::buscar(QString serie, int correlativo)
{
    if (!vacio())
    {
        if (primero->getItem()->comparar(serie, correlativo) < 0
                && ultimo->getItem()->comparar(serie, correlativo) > 0)
            return buscar(primero, serie, correlativo);

        if (primero->getItem()->comparar(serie, correlativo) == 0)
            return primero;

        if (ultimo->getItem()->comparar(serie, correlativo) == 0)
            return ultimo;
    }

    return NULL;
}

TADFactura *ListaFactura::obtener(QString serie, int correlativo)
{
    NodoFactura *nodo = buscar(serie, correlativo);

    if (nodo != NULL)
        return nodo->getItem();

    return NULL;
}

bool ListaFactura::eliminar(QString serie, int correlativo)
{
    NodoFactura *nodo = buscar(serie, correlativo);

    if (nodo != NULL)
    {
        if (primero == nodo)
        {
            primero = primero->getSiguiente();
            primero->setAnterior(NULL);

            delete nodo;
            return true;
        }
        else
        {
            NodoFactura *anterior = nodo->getAnterior();
            anterior->setSiguiente(nodo->getSiguiente());

            if (ultimo == nodo)
                ultimo = anterior;
            else
                nodo->getSiguiente()->setAnterior(anterior);

            delete nodo;
            return true;
        }
    }

    return NULL;
}

void ListaFactura::graficar()
{
}


int ListaFactura::contar()
{
    int i = 0;

    NodoFactura *nodo = primero;
    while (nodo != NULL)
    {
        i++;
        nodo = nodo->getSiguiente();
    }

    return i;
}
