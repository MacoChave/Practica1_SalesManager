#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QFileDialog>
#include <QMessageBox>
#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonObject>
#include <QDebug>
#include <QList>
#include "ListaProducto/listaproducto.h"
#include "Tad/tadproducto.h"
#include "ListaCliente/listacliente.h"
#include "Tad/tadcliente.h"
#include "dialogeficiencia.h"

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
private:
    Ui::MainWindow *ui;
    QJsonDocument jsd;
    QString codigoSeleccionado;
    ListaProducto *listaProducto;
    ListaCliente *listaCliente;

    void cargarJSON();
    void limpiarTabla(QTableWidget *table);
};

#endif // MAINWINDOW_H
