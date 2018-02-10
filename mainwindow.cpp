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
    delete listaProducto;
    delete ui;
    qDebug() <<  "Se ha liberado memoria :D" << endl;
}

void MainWindow::on_actionSalir_triggered()
{
    this->close();
}

void MainWindow::cargarJSON()
{
    QString filename = QFileDialog::getOpenFileName(
                this,
                "Seleccionar fichero JSON",
                "/home/marco/Escritorio/",
                "JSON Files (*.json);;JSON Files (*JSON)"
                );

    QFile file(filename);

    if (!file.open(QFile::ReadOnly))
        return;

    jsd = QJsonDocument::fromJson(file.readAll());
    file.close();
}

void MainWindow::limpiarTabla(QTableWidget *table)
{
    table->clear();
    table->setRowCount(0);
}

void MainWindow::on_btn_producto_aceptar_clicked()
{
    QString codigo = ui->edt_producto_codigo->text();
    QString nombre = ui->edt_producto_nombre->text();
    double precio = ui->edt_producto_precio->text().toDouble();
    QString descripcion = ui->edt_producto_descripcion->text();

    if (codigoSeleccionado.isEmpty())
    {
        TADProducto *producto = new TADProducto(codigo, precio, nombre, descripcion);
        if (listaProducto->agregar(producto))
            qDebug() << "Se agregó con exito el registro" << endl;
        else
            qDebug() << "No agregó el registro" << endl;
    }
    else
    {
        TADProducto *busqueda = listaProducto->obtener(codigo);

        if (busqueda == NULL || busqueda->comparar(codigoSeleccionado) == 0)
        {
            TADProducto *producto = listaProducto->obtener(codigoSeleccionado);
            producto->setCodigo(codigo);
            producto->setNombre(nombre);
            producto->setPrecio(precio);
            producto->setDescripcion(descripcion);
        }
        else
            qDebug() << "Ya hay un registro con ese código" << endl;
    }

    on_btn_producto_limpiar_clicked();
    limpiarTabla(ui->tbl_producto_registro);
    listaProducto->cargarDetalle(ui->tbl_producto_registro);
}

void MainWindow::on_btn_producto_eliminar_clicked()
{
    if (listaProducto->eliminar(ui->edt_producto_codigo->text()))
        qDebug() << "Se eliminó con exito el registro" <<  endl;
    else
        qDebug() << "No se eliminó el registro" <<  endl;

    on_btn_producto_limpiar_clicked();
    limpiarTabla(ui->tbl_producto_registro);
    listaProducto->cargarDetalle(ui->tbl_producto_registro);
}

void MainWindow::on_btn_producto_limpiar_clicked()
{
    codigoSeleccionado.clear();
    ui->edt_producto_codigo->clear();
    ui->edt_producto_descripcion->clear();
    ui->edt_producto_nombre->clear();
    ui->edt_producto_precio->clear();
}

void MainWindow::on_btn_producto_detalle_clicked()
{
    QTableWidgetItem *twi = ui->tbl_producto_registro->currentItem();
    TADProducto *producto = listaProducto->obtener(twi->text());

    if (producto != NULL)
    {
        ui->edt_producto_codigo->setText(producto->getCodigo());
        ui->edt_producto_nombre->setText(producto->getNombre());
        ui->edt_producto_precio->setText(QString::number(producto->getPrecio()));
        ui->edt_producto_descripcion->setText(producto->getDescripcion());

        codigoSeleccionado = producto->getCodigo();
    }
}

void MainWindow::on_btn_producto_grafico_clicked()
{
    listaProducto->graficar();
}

void MainWindow::on_btn_producto_carga_clicked()
{
    cargarJSON();

    if (!jsd.isEmpty())
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

        limpiarTabla(ui->tbl_producto_registro);
        listaProducto->cargarDetalle(ui->tbl_producto_registro);
        jsd = QJsonDocument::fromRawData("", 0);
    }
    else
        qDebug() << "El fichero JSON está vacio" << endl;
}
