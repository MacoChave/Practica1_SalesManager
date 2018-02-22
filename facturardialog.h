#ifndef FACTURARDIALOG_H
#define FACTURARDIALOG_H

#include <QDialog>
#include <QMessageBox>
#include <QList>
#include <QDebug>
#include <QInputDialog>
#include <QDate>
#include "ListaFactura/listafactura.h"
#include "ListaCliente/listacliente.h"
#include "ListaProducto/listaproducto.h"

namespace Ui {
class FacturarDialog;
}

class FacturarDialog : public QDialog
{
    Q_OBJECT

    enum
    {
        CANTIDAD, CODIGO, PRODUCTO, PRECIO_U, DESCUENTO, TOTAL
    };

public:
    explicit FacturarDialog(QWidget *parent = 0);
    ~FacturarDialog();

    void setDatos(ListaProducto *_productos, ListaCliente *_clientes, QList<QString> _series, int _correlativo);
private slots:

    void on_edt_facturar_nit_editingFinished();

    void on_btn_facturar_nuevo_clicked();

    void on_btn_facturar_graficar_clicked();

    void on_btn_facturar_quitar_producto_clicked();

    void on_btn_facturar_vaciar_compra_clicked();

    void on_btn_facturar_eliminar_factura_clicked();

    void on_btn_facturar_agregar_clicked();

private:
    Ui::FacturarDialog *ui;
    ListaCliente *clientes;
    ListaProducto *productos;
    TADCliente *cliente;
    TADFactura *factura;
    int correlativo;
    QList<QString> series;

    void llenarComboBox();
    void limpiarCampos();
    void limpiarTabla();
    void cargarDetalle();
    int getX(int i);
};

#endif // FACTURARDIALOG_H
