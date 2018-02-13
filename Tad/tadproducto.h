#ifndef TADPRODUCTO_H
#define TADPRODUCTO_H
#include <QString>

class TADProducto
{
    int id;
    QString codigo;
    double precio;
    QString nombre;
    QString descripcion;
public:
    TADProducto();
    TADProducto(QString _codigo, double _precio, QString _nombre, QString _descripcion);
    ~TADProducto();

    int getId();
    QString getCodigo();
    void setCodigo(QString value);
    double getPrecio();
    void setPrecio(double value);
    QString getNombre();
    void setNombre(QString value);
    QString getDescripcion();
    void setDescripcion(QString value);

    QString getNombreNodo();
    QString toString();
    int comparar(TADProducto *value);
    int comparar(QString value);
};

#endif // TADPRODUCTO_H
