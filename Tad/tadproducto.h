#ifndef TADPRODUCTO_H
#define TADPRODUCTO_H
#include <QString>

class TADProducto
{
    QString codigo;
    double precio;
    QString nombre;
    QString descripcion;
public:
    TADProducto();
    TADProducto(QString _codigo, double _precio, QString _nombre, QString _descripcion);
    ~TADProducto();

    QString getCodigo();
    void setCodigo(QString value);
    double getPrecio();
    void setPrecio(double value);
    QString getNombre();
    void setNombre(QString value);
    QString getDescripcion();
    void setDescripcion(QString value);

    QString getName();
    QString toString();
    int comparar(TADProducto value);
};

#endif // TADPRODUCTO_H
