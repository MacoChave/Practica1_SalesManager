#ifndef LISTACLIENTE_H
#define LISTACLIENTE_H
#include <QString>
#include <QFile>
#include <QTableWidget>
#include <QTextStream>
#include <iostream>
#include "nodocliente.h"
#include "Tad/tadcliente.h"

class ListaCliente
{
    NodoCliente *primero;
    NodoCliente *ultimo;

    enum
    {
        NIT, NOMBRE
    };

    bool agregar(NodoCliente *anterior, NodoCliente *actual, NodoCliente *nuevo);
    NodoCliente *buscar(NodoCliente *actual, QString value);
    NodoCliente *buscarAnterior(NodoCliente *actual, QString value);
public:
    ListaCliente();
    ~ListaCliente();

    void setPrimero(NodoCliente *value);
    NodoCliente *getPrimero();
    void setUltimo(NodoCliente *value);
    NodoCliente *getUltimo();

    bool vacio();
    bool agregar(TADCliente *cliente);
    NodoCliente *buscar(QString value);
    TADCliente *obtener(QString value);
    bool eliminar(QString value);
    void graficar();
    bool agregarPrimero(TADCliente *cliente);
    bool agregarUltimo(TADCliente *cliente);
    void cargarDetalle(QTableWidget *table);
};

#endif // LISTACLIENTE_H
