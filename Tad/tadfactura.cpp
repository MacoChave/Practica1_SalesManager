#include "tadfactura.h"

TADFactura::TADFactura()
{
    detalle = new PilaDetalle();
}

TADFactura::~TADFactura()
{
    if (detalle != NULL)
        delete detalle;
    serie.clear();
    fechaEmision.clear();
    correlativo = 0;
    detalle = NULL;
}

void TADFactura::setSerie(QString value)
{
    serie = value;
}

QString TADFactura::getSerie()
{
    return serie;
}

void TADFactura::setCorrelativo(int value)
{
    correlativo = value;
}

int TADFactura::getCorrelativo()
{
    return correlativo;
}

void TADFactura::setFechaEmision(QString value)
{
    fechaEmision = value;
}

QString TADFactura::getFechaEmision()
{
    return fechaEmision;
}

void TADFactura::setDetalle(TADDetalle *value)
{
    detalle->push(value);
}

PilaDetalle *TADFactura::getDetalles()
{
    return detalle;
}

void TADFactura::exportar()
{
}

QString TADFactura::getNombreNodo()
{
    QString nodo("nodo");
    nodo.append(serie);
    nodo.append(QString::number(correlativo));
    nodo.replace("-", "");

    return nodo;
}

QString TADFactura::toString()
{
    QString string("FE-");
    string.append(serie);
    string.append("-");
    string.append(correlativo);

    return string;
}

int TADFactura::comparar(TADFactura *value)
{
    int comparar = serie.compare(value->getSerie());

    if (comparar == 0)
    {
        if (correlativo > value->getCorrelativo())
            return 1;
        if (correlativo < value->getCorrelativo())
            return -1;
        else
            return 0;
    }

    return comparar;
}

int TADFactura::comparar(QString _serie, int _correlativo)
{
    int comparar = serie.compare(_serie);

    if (comparar == 0)
    {
        if (correlativo > _correlativo)
            return 1;
        if (correlativo < _correlativo)
            return -1;
        else
            return 0;
    }

    return comparar;
}
