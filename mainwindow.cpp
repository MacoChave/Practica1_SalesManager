#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    listaProducto = new ListaProducto();
    listaCliente = new ListaCliente();
}

MainWindow::~MainWindow()
{
    delete listaProducto;
    delete listaCliente;
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

    clock_t t1, t2;
    double secs;
    t1 = clock();

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

            listaProducto->agregarUltimo(producto);
        }

        limpiarTabla(ui->tbl_producto_registro);
        listaProducto->cargarDetalle(ui->tbl_producto_registro);
    }
    else
        qDebug() << "El fichero JSON está vacio" << endl;

    t2 = clock();
    secs = (double)(t2 - t1) / CLOCKS_PER_SEC;
    qDebug() << "Mi estructura " << QString::number(secs) + " ms";

    jsd = QJsonDocument::fromRawData("", 0);
}

void MainWindow::on_btn_cliente_aceptar_clicked()
{
    QString nit = ui->edt_cliente_nit->text();
    QString nombre = ui->edt_cliente_nombre->text();

    if (codigoSeleccionado.isEmpty())
    {
        TADCliente *cliente = new TADCliente(nit, nombre);
        if (listaCliente->agregar(cliente))
            qDebug() << "Se agregó con exito el registro" << endl;
        else
            qDebug() << "No agregó el registro" << endl;
    }
    else
    {
        TADCliente *busqueda = listaCliente->obtener(nit);

        if (busqueda == NULL || busqueda->comparar(codigoSeleccionado) == 0)
        {
            TADCliente *cliente = listaCliente->obtener(codigoSeleccionado);
            cliente->setNit(nit);
            cliente->setNombre(nombre);
        }
        else
            qDebug() << "Ya hay un registro con ese código" << endl;
    }

    on_btn_cliente_limpiar_clicked();
    limpiarTabla(ui->tbl_cliente_registro);
    listaCliente->cargarDetalle(ui->tbl_cliente_registro);
}

void MainWindow::on_btn_cliente_eliminar_clicked()
{
    if (listaCliente->eliminar(ui->edt_cliente_nit->text()))
        qDebug() << "Se eliminó con exito el registro" <<  endl;
    else
        qDebug() << "No se eliminó el registro" <<  endl;

    on_btn_cliente_limpiar_clicked();
    limpiarTabla(ui->tbl_cliente_registro);
    listaCliente->cargarDetalle(ui->tbl_cliente_registro);
}

void MainWindow::on_btn_cliente_limpiar_clicked()
{
    codigoSeleccionado.clear();
    ui->edt_cliente_nit->clear();
    ui->edt_cliente_nombre->clear();
    ui->edt_cliente_no_facturas->clear();
}

void MainWindow::on_btn_cliente_detalle_clicked()
{
    QTableWidgetItem *twi = ui->tbl_cliente_registro->currentItem();
    TADCliente *cliente = listaCliente->obtener(twi->text());

    if (cliente != NULL)
    {
        ui->edt_cliente_nit->setText(cliente->getNit());
        ui->edt_cliente_nombre->setText(cliente->getNombre());

        codigoSeleccionado = cliente->getNit();
    }
}

void MainWindow::on_btn_cliente_grafico_clicked()
{
    listaCliente->graficar();
}

void MainWindow::on_btn_cliente_carga_clicked()
{
    cargarJSON();

    if (!jsd.isEmpty())
    {
        QJsonArray jsa = jsd.array();

        for (int i = 0; i < jsa.count(); i++)
        {
            QJsonValue jsv = jsa.at(i);
            QJsonObject jso = jsv.toObject();

            TADCliente *cliente = new TADCliente();
            cliente->setNit(jso["NIT"].toString());
            cliente->setNombre(jso["nombre"].toString());

            listaCliente->agregar(cliente);
        }

        limpiarTabla(ui->tbl_cliente_registro);
        listaCliente->cargarDetalle(ui->tbl_cliente_registro);
    }
    else
        qDebug() << "El fichero JSON está vacio" << endl;

    jsd = QJsonDocument::fromRawData("", 0);
}
