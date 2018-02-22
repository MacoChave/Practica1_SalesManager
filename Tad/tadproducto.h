#ifndef TADPRODUCTO_H
#define TADPRODUCTO_H
#include <QString>
#include <QRegExp>

class TADProducto
{
    int id;
    QString codigo;
    double precio;
    QString nombre;
    QString descripcion;
    int ocupado;
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
    int isOcupado();
    void setOcupado();
    void setDesocupado();
};

#endif // TADPRODUCTO_H
