#ifndef TADDETALLE_H
#define TADDETALLE_H
#include "tadproducto.h"

class TADDetalle
{
    TADProducto *producto;
    int cantidad;
    double descuento;
public:
    TADDetalle();
    ~TADDetalle();

    void setProducto(TADProducto *value);
    TADProducto *getProducto();
    void setCantidad(int value);
    int getCantidad();
    void setDescuento(double value);
    double getDescuento();

    QString getNombreNodo();
    QString toString();
};

#endif // TADDETALLE_H
