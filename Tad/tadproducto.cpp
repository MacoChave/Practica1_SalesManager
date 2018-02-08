#include "tadproducto.h"

QString TADProducto::getCodigo()
{
    return codigo;
}

void TADProducto::setCodigo(QString value)
{
    codigo = value;
}

double TADProducto::getPrecio()
{
    return precio;
}

void TADProducto::setPrecio(double value)
{
    precio = value;
}

QString TADProducto::getNombre()
{
    return nombre;
}

void TADProducto::setNombre(QString value)
{
    nombre = value;
}

QString TADProducto::getDescripcion()
{
    return descripcion;
}

void TADProducto::setDescripcion(QString value)
{
    descripcion = value;
}

QString TADProducto::getName()
{
    QString name;
    name.append(codigo);

    return name;
}

QString TADProducto::toString()
{
    QString string;
    string.append(codigo);
    string.append(nombre);
    string.append(QString::number(precio));

    return string;
}

int TADProducto::comparar(TADProducto value)
{
    return codigo.compare(value.getCodigo(), Qt::CaseSensitive);
}

TADProducto::TADProducto()
{
    codigo.clear();
    precio = 0;
    nombre.clear();
    descripcion.clear();
}

TADProducto::TADProducto(QString _codigo, double _precio, QString _nombre, QString _descripcion)
{
    codigo = _codigo;
    precio = _nombre;
    nombre = _precio;
    descripcion = _descripcion;
}

TADProducto::~TADProducto()
{
    codigo.clear();
    precio = 0;
    nombre.clear();
    descripcion.clear();
}
