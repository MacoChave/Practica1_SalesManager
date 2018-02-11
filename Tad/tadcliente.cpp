#include "tadcliente.h"

TADCliente::TADCliente()
{
}

TADCliente::TADCliente(QString _nit, QString _nombre)
{
    nit = _nit;
    nombre = _nombre;
}

TADCliente::~TADCliente()
{
    nit.clear();
    nombre.clear();
}

void TADCliente::setNit(QString value)
{
    nit = value;
}

QString TADCliente::getNit()
{
    return nit;
}

void TADCliente::setNombre(QString value)
{
    nombre = value;
}

QString TADCliente::getNombre()
{
    return nombre;
}

QString TADCliente::getNombreNodo()
{
    return nit;
}

QString TADCliente::toString()
{
    QString string("NIT: ");
    string.append(nit);
    string.append("\\n");
    string.append(nombre);

    return string;
}

int TADCliente::comparar(TADCliente *value)
{
    return nit.compare(value->getNit(), Qt::CaseSensitive);
}

int TADCliente::comparar(QString value)
{
    return nit.compare(value, Qt::CaseSensitive);
}
