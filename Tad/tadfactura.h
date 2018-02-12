#ifndef TADFACTURA_H
#define TADFACTURA_H
#include <QString>

class TADFactura
{
    QString serie;
    int correlativo;
    QString fechaEmision;
public:
    TADFactura();
    ~TADFactura();

    void setSerie(QString value);
    QString getSerie();
    void setCorrelativo(int value);
    int getCorrelativo();
    void setFechaEmision(QString value);
    QString getFechaEmision();

    QString getNombreNodo();
    QString toString();
    int comparar(TADFactura *value);
    int comparar(QString serie, int correlativo);
};

#endif // TADFACTURA_H
