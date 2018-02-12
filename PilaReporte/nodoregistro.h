#ifndef NODOREGISTRO_H
#define NODOREGISTRO_H
#include <QString>
#include "Tad/taddetalle.h"

class NodoRegistro
{
    TADDetalle *detalle;
    NodoRegistro *siguiente;
public:
    NodoRegistro();
    NodoRegistro(TADDetalle *value);
    ~NodoRegistro();

    void setDetalle(TADDetalle *value);
    TADDetalle *getDetalle();
    void setSiguiente(NodoRegistro *value);
    NodoRegistro *getSiguiente();

    QString getNombreNodo();
    QString toString();
};

#endif // NODOREGISTRO_H
