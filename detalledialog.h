#ifndef DETALLEDIALOG_H
#define DETALLEDIALOG_H

#include <QDialog>
#include <QPrinter>
#include <QPainter>
#include <QDebug>
#include "Tad/tadcliente.h"

namespace Ui {
class DetalleDialog;
}

class DetalleDialog : public QDialog
{
    Q_OBJECT

public:
    explicit DetalleDialog(QWidget *parent = 0);
    ~DetalleDialog();

    void setFactura(TADCliente *_cliente, TADFactura *_factura);
private slots:
    void on_btn_factura_eliminar_clicked();

    void on_btn_factura_exportar_clicked();

private:
    Ui::DetalleDialog *ui;
    TADFactura *factura;
    TADCliente *cliente;

    enum
    {
        CANTIDAD, CODIGO, PRODUCTO, PRECIO_U, DESCUENTO, TOTAL
    };

    void cargarDetalle();
    int getX(int i);
};

#endif // DETALLEDIALOG_H
