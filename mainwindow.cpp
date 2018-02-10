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
                "JSON Files (*.json);;JSON Files (*JSON)"
                );
    return filename.toLatin1().data();
}

void MainWindow::on_actionCargar_JSON_triggered()
{
}

void MainWindow::on_actionExportar_JSON_triggered()
{
}

void MainWindow::on_actionSalir_triggered()
{
    this->close();
}

void MainWindow::on_btn_producto_agregar_clicked()
{
    ui->tbl_producto_registro->clear();
    listaProducto->cargarDetalle(ui->tbl_producto_registro);
}

void MainWindow::on_btn_producto_eliminar_clicked()
{
    ui->tbl_producto_registro->clear();
    listaProducto->cargarDetalle(ui->tbl_producto_registro);
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
    QString filename = abrirSelectorArchivos();
    QFile file(filename);

    if (!file.open(QFile::ReadOnly))
        return;

    jsd = QJsonDocument::fromJson(file.readAll());
    file.close();

    cargarProductos(jsd);
}


void MainWindow::cargarProductos(QJsonDocument jsd)
{
    QJsonArray jsa = jsd.array();

    for (int i = 0; i < jsa.count(); i++)
    {
        QJsonValue jsv = jsa.at(i);
        QJsonObject jso = jsv.toObject();

        TADProducto *producto = new TADProducto();
        producto->setCodigo(jso["codigo"].toString());
        producto->setNombre(jso["nombre"].toString());
        producto->setPrecio(jso["precio"].toString().toDouble());
        producto->setDescripcion(jso["descripcion"].toString());

        listaProducto->agregar(producto);
    }

    ui->tbl_producto_registro->clear();
    listaProducto->cargarDetalle(ui->tbl_producto_registro);
}
