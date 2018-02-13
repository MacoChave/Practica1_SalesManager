#include "tadproducto.h"

int TADProducto::getId()
{
    return id;
}

QString TADProducto::getCodigo()
{
    return codigo;
}

void TADProducto::setCodigo(QString value)
{
    codigo = value;

    value.remove("P");
    id = value.toInt();
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

QString TADProducto::getNombreNodo()
{
    QString name;
    name.append(getCodigo());

    return name;
}

QString TADProducto::toString()
{
    QString string;
    string.append(getCodigo());
    string.append("\\n");
    string.append(getNombre());
    string.append("\\n");
    string.append(QString::number(getPrecio()));

    return string;
}

int TADProducto::comparar(TADProducto *value)
{
    if (id > value->getId())
        return 1;
    else
    {
        if (id < value->getId())
            return -1;
        else
            return 0;
    }
}

int TADProducto::comparar(QString value)
{
    value.remove("P");
    if (id > value.toInt())
        return 1;
    else
    {
        if (id < value.toInt())
            return -1;
        else
            return 0;
    }
}

TADProducto::TADProducto()
{
    id = 0;
    codigo.clear();
    precio = 0;
    nombre.clear();
    descripcion.clear();
}

TADProducto::TADProducto(QString _codigo, double _precio, QString _nombre, QString _descripcion)
{
    codigo = _codigo;
    precio = _precio;
    nombre = _nombre;
    descripcion = _descripcion;

    _codigo.remove("P");
    id = _codigo.toInt();
}

TADProducto::~TADProducto()
{
    id = 0;
    codigo.clear();
    precio = 0;
    nombre.clear();
    descripcion.clear();
}
