#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    listaProducto = new ListaProducto();
}

MainWindow::~MainWindow()
{
    delete ui;
    delete listaProducto;
}

QString MainWindow::abrirSelectorArchivos()
{
    QString filename = QFileDialog::getOpenFileName(
                this,
                "Seleccionar fichero JSON",
                "/home/marco/Escritorio/",
                "JSON Files (*.JSON);;JSON Files (*json)"
                );
    return filename;
}

void MainWindow::on_actionCargar_JSON_triggered()
{
    QString filename = abrirSelectorArchivos();
}

void MainWindow::on_actionExportar_JSON_triggered()
{
}

void MainWindow::on_btn_producto_agregar_clicked()
{
    listaProducto->agregar(new TADProducto("P001", 50.50, "Producto A", "Breve descripcion"));
    listaProducto->agregar(new TADProducto("P002", 20.50, "Producto B", "Breve descripcion"));
    listaProducto->agregar(new TADProducto("P003", 50.50, "Producto C", "Breve descripcion"));
    listaProducto->agregar(new TADProducto("P004", 40.50, "Producto D", "Breve descripcion"));
    listaProducto->agregar(new TADProducto("P005", 30.50, "Producto E", "Breve descripcion"));
    listaProducto->agregar(new TADProducto("P006", 50.50, "Producto F", "Breve descripcion"));
    listaProducto->agregar(new TADProducto("P007", 70.50, "Producto G", "Breve descripcion"));
    listaProducto->agregar(new TADProducto("P008", 51.50, "Producto H", "Breve descripcion"));
    listaProducto->agregar(new TADProducto("P009", 80.50, "Producto I", "Breve descripcion"));
    listaProducto->agregar(new TADProducto("P010", 10.50, "Producto J", "Breve descripcion"));
    listaProducto->agregar(new TADProducto("P011", 80.50, "Producto K", "Breve descripcion"));
    listaProducto->agregar(new TADProducto("P012", 30.50, "Producto L", "Breve descripcion"));
    listaProducto->agregar(new TADProducto("P013", 90.50, "Producto M", "Breve descripcion"));
    listaProducto->agregar(new TADProducto("P014", 40.50, "Producto N", "Breve descripcion"));
    listaProducto->agregar(new TADProducto("P015", 60.50, "Producto O", "Breve descripcion"));

    listaProducto->cargarDetalle(ui->tbl_producto_registro);
}

void MainWindow::on_btn_producto_eliminar_clicked()
{
}

void MainWindow::on_btn_producto_limpiar_clicked()
{
    ui->edt_producto_codigo->clear();
    ui->edt_producto_descripcion->clear();
    ui->edt_producto_nombre->clear();
    ui->edt_producto_precio->clear();
}

void MainWindow::on_btn_producto_detalle_clicked()
{
}

void MainWindow::on_btn_producto_grafico_clicked()
{
    listaProducto->graficar();
}

void MainWindow::on_btn_producto_carga_clicked()
{
    //QString filename = abrirSelectorArchivos();
}
