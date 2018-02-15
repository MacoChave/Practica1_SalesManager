#include "taddetalle.h"

TADDetalle::TADDetalle()
{
    producto = NULL;
    cantidad = 0;
    descuento = 0;
}

TADDetalle::~TADDetalle()
{
    producto = NULL;
    cantidad = 0;
    descuento = 0;
}

void TADDetalle::setProducto(TADProducto *value)
{
    producto = value;
}

TADProducto *TADDetalle::getProducto()
{
    return producto;
}

void TADDetalle::setCantidad(int value)
{
    cantidad = value;
}

int TADDetalle::getCantidad()
{
    return cantidad;
}

void TADDetalle::setDescuento(double value)
{
    descuento = value;
}

double TADDetalle::getDescuento()
{
    return descuento;
}

QString TADDetalle::getNombreNodo()
{
    QString nodo("nodo");
    nodo.append(producto->getCodigo());

    return nodo;
}

QString TADDetalle::toString()
{
    QString nodo(QString::number(cantidad));
    nodo.append(" ");
    nodo.append(producto->getNombre());

    return nodo;
}
