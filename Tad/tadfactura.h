#ifndef TADFACTURA_H
#define TADFACTURA_H
#include <QString>
#include <QPrinter>
#include <QPainter>
#include <iostream>
#include "PilaReporte/piladetalle.h"

class TADFactura
{
    QString serie;
    int correlativo;
    QString fechaEmision;
    PilaDetalle *detalle;
public:
    TADFactura();
    ~TADFactura();

    void setSerie(QString value);
    QString getSerie();
    void setCorrelativo(int value);
    int getCorrelativo();
    void setFechaEmision(QString value);
    QString getFechaEmision();
    void setDetalle(TADDetalle *value);
    PilaDetalle *getDetalles();

    void exportar();
    QString getNombreNodo();
    QString toString();
    int comparar(TADFactura *value);
    int comparar(QString _serie, int _correlativo);
};

#endif // TADFACTURA_H
