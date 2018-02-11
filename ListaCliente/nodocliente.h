#ifndef NODOCLIENTE_H
#define NODOCLIENTE_H
#include <QString>
#include "Tad/tadcliente.h"

class NodoCliente
{
    TADCliente *item;
    NodoCliente *siguiente;
public:
    NodoCliente();
    NodoCliente(TADCliente *value);
    ~NodoCliente();

    void setItem(TADCliente *value);
    TADCliente *getItem();
    void setSiguiente(NodoCliente *value);
    NodoCliente *getSiguiente();

    QString getNombreNodo();
    QString toString();
};

#endif // NODOCLIENTE_H
