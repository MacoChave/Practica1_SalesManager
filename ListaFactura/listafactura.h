#ifndef LISTAFACTURA_H
#define LISTAFACTURA_H
#include <QListWidget>
#include "ListaFactura/nodofactura.h"

class ListaFactura
{
    NodoFactura *primero;
    NodoFactura *ultimo;

    bool agregar(NodoFactura *actual, TADFactura *value);
    NodoFactura *buscar(NodoFactura *actual, QString serie, int correlativo);
public:
    ListaFactura();
    ~ListaFactura();

    bool vacio();
    bool agregar(TADFactura *value);
    NodoFactura *buscar(QString serie, int correlativo);
    TADFactura *obtener(QString serie, int correlativo);
    bool eliminar(QString serie, int correlativo);
    void graficar();
    bool agregarPrimero(TADFactura *value);
    bool agregarUltimo(TADFactura *value);
    int contar();
    void llenarLista(QListWidget *lista);
};

#endif // LISTAFACTURA_H
