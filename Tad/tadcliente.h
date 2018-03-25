#ifndef TADCLIENTE_H
#define TADCLIENTE_H
#include <QString>
#include "ListaFactura/listafactura.h"

class TADCliente
{
    QString nit;
    QString nombre;
    ListaFactura *facturas;
public:
    TADCliente();
    TADCliente(QString _nit, QString _nombre);
    TADCliente(QString _nit, QString _nombre, ListaFactura *_facturas);
    ~TADCliente();

    void setNit(QString value);
    QString getNit();
    void setNombre(QString value);
    QString getNombre();
    void setFactura(ListaFactura *value);
    void addFactura(TADFactura *value);
    void addFacturas(ListaFactura *value);
    void agregarFacturas(ListaFactura *value);
    ListaFactura *getFacturas();

    QString getNombreNodo();
    QString toString();
    int comparar(TADCliente *value);
    int comparar(QString value);
};

#endif // TADCLIENTE_H
