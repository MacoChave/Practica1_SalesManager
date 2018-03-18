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

    NodoFactura *getPrimero();
    NodoFactura *getUltimo();
    bool vacio();
    bool agregar(TADFactura *value);
    bool agregar(NodoFactura *actual, NodoFactura *value);
    NodoFactura *buscar(QString serie, int correlativo);
    TADFactura *obtener(QString serie, int correlativo);
    bool eliminar(QString serie, int correlativo);
    void graficar();
    bool agregarPrimero(TADFactura *value);
    bool agregarPrimero(NodoFactura *value);
    bool agregarUltimo(TADFactura *value);
    bool agregarUltimo(NodoFactura *value);
    int contar();
    void llenarLista(QListWidget *lista);
};

#endif // LISTAFACTURA_H
