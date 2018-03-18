#include "tadcliente.h"

TADCliente::TADCliente()
{
    facturas = new ListaFactura();
}

TADCliente::TADCliente(QString _nit, QString _nombre)
{
    nit = _nit;
    nombre = _nombre;
    facturas = new ListaFactura();
}

TADCliente::TADCliente(QString _nit, QString _nombre, ListaFactura *_factura)
{
    nit = _nit;
    nombre = _nombre;
    facturas = _factura;
}

TADCliente::~TADCliente()
{
    nit.clear();
    nombre.clear();
    delete facturas;
}

void TADCliente::setNit(QString value)
{
    nit = value;
}

QString TADCliente::getNit()
{
    return nit;
}

void TADCliente::setNombre(QString value)
{
    nombre = value;
}

QString TADCliente::getNombre()
{
    return nombre;
}

void TADCliente::setFactura(ListaFactura *value)
{
    facturas = value;
}

void TADCliente::addFactura(TADFactura *value)
{
    facturas->agregar(value);
}

void TADCliente::addFacturas(ListaFactura *value)
{
    delete facturas;
    facturas = value;
}

void TADCliente::agregarFacturas(ListaFactura *value)
{
    NodoFactura *factura = value->getPrimero();

    while (factura != NULL)
    {
        if (facturas->vacio())
            facturas->agregarPrimero(factura);
        else if (facturas->getPrimero()->getItem()->comparar(factura->getItem()) > 0)
            facturas->agregarPrimero(factura);
        else if (facturas->getPrimero()->getItem()->comparar(factura->getItem()) > 0)
            facturas->agregarUltimo(factura);
        else
            facturas->agregar(facturas->getPrimero()->getSiguiente(), factura);

        factura = factura->getSiguiente();
    }
}

ListaFactura *TADCliente::getFacturas()
{
    return facturas;
}

QString TADCliente::getNombreNodo()
{
    QString nodo("nodo");
    nodo.append(nit);
    nodo.replace("-", "");

    return nodo;
}

QString TADCliente::toString()
{
    QString string("NIT: ");
    string.append(nit);
    string.append("\\n");
    string.append(nombre);
    string.append("\\n");
    string.append(QString::number(facturas->contar()));
    string.append(" facturas");

    return string;
}

int TADCliente::comparar(TADCliente *value)
{
    return nit.compare(value->getNit(), Qt::CaseSensitive);
}

int TADCliente::comparar(QString value)
{
    return nit.compare(value, Qt::CaseSensitive);
}
