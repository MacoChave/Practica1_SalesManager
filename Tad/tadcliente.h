#ifndef TADCLIENTE_H
#define TADCLIENTE_H
#include <QString>

class TADCliente
{
    QString nit;
    QString nombre;
public:
    TADCliente();
    TADCliente(QString _nit, QString _nombre);
    ~TADCliente();

    void setNit(QString value);
    QString getNit();
    void setNombre(QString value);
    QString getNombre();

    QString getNombreNodo();
    QString toString();
    int comparar(TADCliente *value);
    int comparar(QString value);
};

#endif // TADCLIENTE_H
