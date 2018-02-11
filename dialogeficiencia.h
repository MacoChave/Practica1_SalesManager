#ifndef DIALOGEFICIENCIA_H
#define DIALOGEFICIENCIA_H

#include <QDialog>
#include <QString>
#include <QList>
#include <time.h>
#include "ListaProducto/listaproducto.h"
#include "Tad/tadproducto.h"

namespace Ui {
class DialogEficiencia;
}

class DialogEficiencia : public QDialog
{
    Q_OBJECT

public:
    explicit DialogEficiencia(QWidget *parent = 0);
    ~DialogEficiencia();

    double cargarEstructura(int count);
    double cargarQList(int count);
    void cargarQTable(int count);

private slots:
    void on_btn_eficiencia_short_clicked();

    void on_btn_eficiencia_medium_clicked();

    void on_bnt_eficiencia_long_clicked();

    void on_btn_eficiencia_verylong_clicked();

    void on_btn_eficiencia_salir_clicked();

private:
    Ui::DialogEficiencia *ui;
    QString nombre, descripcion;
    double precio;

    enum
    {
        NUMERO_REGISTRO, ESTRUCTURA, QLIST
    };

    void limpiarTable();
};

#endif // DIALOGEFICIENCIA_H
