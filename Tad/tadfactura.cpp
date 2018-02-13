#include "tadfactura.h"

TADFactura::TADFactura()
{
    detalle = new PilaDetalle();
}

TADFactura::~TADFactura()
{
    serie.clear();
    correlativo = 0;
    delete detalle;
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
    NodoRegistro *temp = detalle->getCima();

    if (temp->getDetalle() != NULL)
    {
        QString archivo("FE-");
        archivo.append(serie);
        archivo.append("-");
        archivo.append(QString::number(correlativo));
        archivo.append(".pdf");
        int linea = 20;

        QPrinter printer;
        printer.setOutputFormat(QPrinter::PdfFormat);
        printer.setOutputFileName(archivo);
        QPainter painter;
        if (! painter.begin(&printer)) { // failed to open file
          qWarning("failed to open file, is it writable?");
          return;
        }

        painter.drawText(10, 25, "Cantidad");
        painter.drawText(100, 25, "Código");
        painter.drawText(200, 25, "Nombre");
        painter.drawText(300, 25, "Precio Unitario");
        painter.drawText(500, 25, "Descuento");
        painter.drawText(600, 25, "Valor Total");

        painter.drawLine(10, 34, 800, 34);
        painter.drawLine(10, 36, 800, 36);

        while (temp != NULL)
        {
            TADDetalle *detalle = temp->getDetalle();
            if (detalle->getProducto() != NULL)
            {
                painter.drawText(10, 50 + linea, QString::number(detalle->getCantidad()));
                painter.drawText(100, 50 + linea, detalle->getProducto()->getCodigo());
                painter.drawText(200, 50 + linea, detalle->getProducto()->getNombre());
                painter.drawText(300, 50 + linea, QString::number(detalle->getProducto()->getPrecio()));
                painter.drawText(500, 50 + linea, QString::number(detalle->getDescuento()));
                painter.drawText(600, 50 + linea, "000.00");
            }

            linea += 25;
            temp = temp->getSiguiente();
        }


        painter.end();
    }

    std::cout << "Creación de pdf completo" << std::endl;
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

int TADFactura::comparar(QString serie, int correlativo)
{
    int comparar = serie.compare(serie);

    if (comparar == 0)
    {
        if (correlativo > correlativo)
            return 1;
        if (correlativo < correlativo)
            return -1;
        else
            return 0;
    }

    return comparar;
}
