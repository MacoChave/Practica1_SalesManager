#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QFileDialog>
#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonObject>
#include <QList>
#include <QDebug>
#include "ListaProducto/listaproducto.h"
#include "ListaCliente/listacliente.h"
#include "PilaReporte/piladetalle.h"
#include "dialogeficiencia.h"
#include "detalledialog.h"
#include "facturardialog.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:

    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_actionSalir_triggered();

    void on_actionEficiencia_triggered();

    void on_btn_producto_aceptar_clicked();

    void on_btn_producto_eliminar_clicked();

    void on_btn_producto_limpiar_clicked();

    void on_btn_producto_detalle_clicked();

    void on_btn_producto_grafico_clicked();

    void on_btn_producto_carga_clicked();

    void on_btn_cliente_aceptar_clicked();

    void on_btn_cliente_eliminar_clicked();

    void on_btn_cliente_limpiar_clicked();

    void on_btn_cliente_detalle_clicked();

    void on_btn_cliente_grafico_clicked();

    void on_btn_cliente_carga_clicked();

    void on_btn_detalle_buscar_clicked();

    void on_btn_detalle_ver_clicked();

    void on_btn_producto_buscar_clicked();

    void on_actionFacturar_triggered();

private:
    Ui::MainWindow *ui;
    QList<QString> series;
    int contador_correlativo;
    QJsonDocument jsd;
    QString codigoSeleccionado;
    ListaProducto *productos;
    ListaCliente *clientes;

    void cargarJSON();
    void limpiarTabla(QTableWidget *table);
    void limpiarLista(QListWidget *list);
};

#endif // MAINWINDOW_H
