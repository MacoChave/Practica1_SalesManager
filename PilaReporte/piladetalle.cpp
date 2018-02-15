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

double PilaDetalle::cargarDetalle(QTableWidget *table)
{
    double total = 0;
    if (!vacio())
    {
        NodoRegistro *temp = cima;
        int y = table->rowCount();

        while (temp != NULL)
        {
            TADDetalle *detalle = NULL;
            detalle = temp->getDetalle();
            double n1 = detalle->getCantidad();
            double n2 = detalle->getProducto()->getPrecio();
            double subtotal = n1 * n2;
            subtotal = subtotal - (subtotal * detalle->getDescuento());
            total += subtotal;

            table->insertRow(y);
            table->setItem(y, CANTIDAD, new QTableWidgetItem(QString::number(detalle->getCantidad())));
            table->setItem(y, CODIGO, new QTableWidgetItem(detalle->getProducto()->getCodigo()));
            table->setItem(y, PRODUCTO, new QTableWidgetItem(detalle->getProducto()->getNombre()));
            table->setItem(y, PRECIO_U, new QTableWidgetItem(QString::number(detalle->getProducto()->getPrecio())));
            table->setItem(y, DESCUENTO, new QTableWidgetItem(QString::number(detalle->getDescuento())));
            table->setItem(y, TOTAL, new QTableWidgetItem(QString::number(subtotal)));

            temp = temp->getSiguiente();
        }

    }
    return total;
}

