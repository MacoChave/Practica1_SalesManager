#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    productos = new ListaProducto();
    clientes = new ListaCliente();
    contador_correlativo = 0;
}

MainWindow::~MainWindow()
{
    delete productos;
    delete clientes;
    series.clear();
    delete ui;
    qDebug() <<  "Se ha liberado memoria :D" << endl;
}

void MainWindow::on_actionSalir_triggered()
{
    this->close();
}

void MainWindow::on_actionEficiencia_triggered()
{
    DialogEficiencia dialog(this);
    dialog.setWindowTitle("Eficiencia de algoritmo");
    dialog.exec();
}

void MainWindow::on_actionFacturar_triggered()
{
    FacturarDialog dialog(this);
    dialog.setWindowTitle("Facturar");
    dialog.setDatos(productos, clientes, series, contador_correlativo);
    dialog.exec();
    limpiarTabla(ui->tbl_cliente_registro);
    clientes->cargarDetalle(ui->tbl_cliente_registro);
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

void MainWindow::limpiarLista(QListWidget *list)
{
    list->clear();
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
        if (productos->agregar(producto))
            qDebug() << "Se agregó con éxito el registro" << endl;
        else
        {
            QMessageBox mensaje(this);
            mensaje.setWindowTitle("Lista Producto");
            mensaje.setText("Registro existente con el mismo código");
            mensaje.exec();
        }
    }
    else
    {
        TADProducto *busqueda = productos->obtener(codigoSeleccionado);
        busqueda->setNombre(nombre);
        busqueda->setDescripcion(descripcion);
        busqueda->setPrecio(precio);

        if (productos->actualizar(codigo, busqueda))
            qDebug() << "Producto actualizado con éxito" << endl;
        else
        {
            QMessageBox mensaje(this);
            mensaje.setWindowTitle("Lista Producto");
            mensaje.setText("No se pudo cambiar el codigo. Pues ya existe registrado");
            mensaje.exec();
        }
    }

    on_btn_producto_limpiar_clicked();
    limpiarTabla(ui->tbl_producto_registro);
    productos->cargarDetalle(ui->tbl_producto_registro);
}

void MainWindow::on_btn_producto_eliminar_clicked()
{
    if (productos->eliminar(ui->edt_producto_codigo->text()))
        qDebug() << "Se eliminó con exito el registro" <<  endl;
    else
    {
        QMessageBox mensaje(this);
        mensaje.setText("No es posible eliminar el producto. Es posible que esté en uso");
        mensaje.setWindowTitle("Error al eliminar el producto");
        mensaje.exec();
    }

    on_btn_producto_limpiar_clicked();
    limpiarTabla(ui->tbl_producto_registro);
    productos->cargarDetalle(ui->tbl_producto_registro);
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
    if (ui->tbl_producto_registro->rowCount() > 0)
    {
        QTableWidgetItem *twi = ui->tbl_producto_registro->currentItem();
        TADProducto *producto = productos->busquedaBinaria(twi->text());

        if (producto != NULL)
        {
            ui->edt_producto_codigo->setText(producto->getCodigo());
            ui->edt_producto_nombre->setText(producto->getNombre());
            ui->edt_producto_precio->setText(QString::number(producto->getPrecio()));
            ui->edt_producto_descripcion->setText(producto->getDescripcion());

            codigoSeleccionado = producto->getCodigo();
        }
    }
}


void MainWindow::on_btn_producto_buscar_clicked()
{
    QString filter = ui->edt_producto_buscar->text();
    for(int i = 0; i < ui->tbl_producto_registro->rowCount(); i++)
    {
        bool match = false;
        for(int j = 0; j < ui->tbl_producto_registro->columnCount(); j++)
        {
            QTableWidgetItem *item = ui->tbl_producto_registro->item(i, j);
            if(item->text().contains(filter))
            {
                match = true;
                break;
            }
        }
        ui->tbl_producto_registro->setRowHidden(i, !match);
    }
}

void MainWindow::on_btn_producto_grafico_clicked()
{
    productos->graficar();
}

void MainWindow::on_btn_producto_carga_clicked()
{
    cargarJSON();

    if (!jsd.isEmpty())
    {
        QJsonArray jsa_cliente = jsd.array();

        for (int i = 0; i < jsa_cliente.count(); i++)
        {
            QJsonObject jso_cliente = jsa_cliente.at(i).toObject();

            TADProducto *producto = new TADProducto();
            producto->setCodigo(jso_cliente["codigo"].toString());
            producto->setNombre(jso_cliente["nombre"].toString());
            producto->setPrecio(jso_cliente["precio"].toString().toDouble());
            producto->setDescripcion(jso_cliente["descripcion"].toString());

            productos->agregar(producto);
        }

        limpiarTabla(ui->tbl_producto_registro);
        productos->cargarDetalle(ui->tbl_producto_registro);
    }
    else
        qDebug() << "El fichero JSON está vacio" << endl;

    jsd = QJsonDocument::fromRawData("", 0);
    std::cout << "Carga de JSON completado" << std::endl;
}

void MainWindow::on_btn_cliente_aceptar_clicked()
{
    QString nit = ui->edt_cliente_nit->text();
    QString nombre = ui->edt_cliente_nombre->text();

    if (codigoSeleccionado.isEmpty())
    {
        TADCliente *cliente = new TADCliente(nit, nombre);
        if (clientes->agregar(cliente))
            qDebug() << "Se agregó con exito el registro" << endl;
        else
        {
            QMessageBox mensaje(this);
            mensaje.setWindowTitle("Lista Cliente");
            mensaje.setText("No se puede agregar el registro");
            mensaje.exec();
        }
    }
    else
    {
        TADCliente *busqueda = clientes->obtener(codigoSeleccionado);
        busqueda->setNombre(nombre);

        if (clientes->actualizar(nit, busqueda))
            qDebug() << "Cliente actualizado con éxito" << endl;
        else
        {
            QMessageBox mensaje(this);
            mensaje.setWindowTitle("Lista Cliente");
            mensaje.setText("No se pudo actualizar el nit. Pues ya existe registrado");
            mensaje.exec();
        }
    }

    on_btn_cliente_limpiar_clicked();
    limpiarTabla(ui->tbl_cliente_registro);
    clientes->cargarDetalle(ui->tbl_cliente_registro);
}

void MainWindow::on_btn_cliente_eliminar_clicked()
{
    if (clientes->eliminar(ui->edt_cliente_nit->text()))
        qDebug() << "Se eliminó con exito el registro" <<  endl;
    else
    {
        QMessageBox mensaje(this);
        mensaje.setText("No es posible eliminar el cliente.");
        mensaje.setWindowTitle("Error al eliminar el cliente");
        mensaje.exec();
    }

    on_btn_cliente_limpiar_clicked();
    limpiarTabla(ui->tbl_cliente_registro);
    clientes->cargarDetalle(ui->tbl_cliente_registro);
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
    if (ui->tbl_cliente_registro->rowCount() > 0)
    {
        QTableWidgetItem *twi = ui->tbl_cliente_registro->currentItem();
        TADCliente *cliente = clientes->obtener(twi->text());

        if (cliente != NULL)
        {
            int count = cliente->getFacturas()->contar();

            ui->edt_cliente_nit->setText(cliente->getNit());
            ui->edt_cliente_nombre->setText(cliente->getNombre());
            ui->edt_cliente_no_facturas->setText(QString::number(count));

            codigoSeleccionado = cliente->getNit();
        }
    }
}

void MainWindow::on_btn_cliente_grafico_clicked()
{
    clientes->graficar();
}

void MainWindow::on_btn_cliente_carga_clicked()
{
    cargarJSON();

    if (!jsd.isEmpty())
    {
        /* ARRAY CLIENTES */
        QJsonArray jsa = jsd.array();

        for (int i = 0; i < jsa.count(); i++)
        {
            /* OBJETO CLIENTE */
            QJsonObject jso = jsa.at(i).toObject();

            TADCliente *cliente = new TADCliente();
            cliente->setNit(jso["NIT"].toString());
            cliente->setNombre(jso["nombre"].toString());

            /* ARRAY FACTURAS */
            QJsonArray jsa_facturas = jso["facturas"].toArray();

            for (int j = 0; j < jsa_facturas.count(); j++)
            {
                /* OBJETO FACTURA */
                QJsonObject jso_facturas = jsa_facturas.at(j).toObject();

                TADFactura *factura = new TADFactura();
                factura->setSerie(jso_facturas["serie"].toString());
                factura->setCorrelativo(jso_facturas["correlativo"].toString().toInt());
                factura->setFechaEmision(jso_facturas["fecha"].toString());

                if (!series.contains(factura->getSerie()))
                    series << factura->getSerie();
                if (factura->getCorrelativo() > contador_correlativo)
                    contador_correlativo = factura->getCorrelativo();

                qDebug() << series << " " << contador_correlativo << endl;

                /* ARRAY PRODUCTOS */
                QJsonArray jsa_productos = jso_facturas["productos"].toArray();

                for (int z = 0; z < jsa_productos.count(); z++)
                {
                    /* OBJETO PRODUCTO */
                    QJsonObject jso_productos = jsa_productos.at(z).toObject();

                    TADProducto *producto = productos->obtener(jso_productos["codigo"].toString());
                    if (producto == NULL)
                        continue;

                    producto->setOcupado();
                    TADDetalle *detalle = new TADDetalle();
                    detalle->setProducto(producto);
                    detalle->setCantidad(jso_productos["cantidad"].toInt());
                    detalle->setDescuento(jso_productos["descuento"].toDouble());

                    factura->setDetalle(detalle);
                }
                if (factura->getDetalles()->vacio())
                {
                    delete factura;
                    factura = NULL;
                    continue;
                }

                cliente->addFactura(factura);
            }
            if (cliente->getFacturas()->contar() < 1)
            {
                delete cliente->getFacturas();
                cliente->addFactura(NULL);
            }

            clientes->agregar(cliente);
        }

        limpiarTabla(ui->tbl_cliente_registro);
        clientes->cargarDetalle(ui->tbl_cliente_registro);
    }
    else
        qDebug() << "El fichero JSON está vacio" << endl;

    jsd = QJsonDocument::fromRawData("", 0);
    std::cout << "Carga de JSON completado" << std::endl;
}

void MainWindow::on_btn_detalle_buscar_clicked()
{
    limpiarLista(ui->lst_detalle_facturas);

    TADCliente *cliente = NULL;
    cliente = clientes->obtener(ui->edt_detalle_buscar->text());

    if (cliente != NULL)
    {
        ui->edt_detalle_nit->setText(cliente->getNit());
        ui->edt_detalle_nombre->setText(cliente->getNombre());
        ui->edt_detalle_no_facturas->setText(QString::number(cliente->getFacturas()->contar()));

        cliente->getFacturas()->llenarLista(ui->lst_detalle_facturas);
    }
}

void MainWindow::on_btn_detalle_ver_clicked()
{
    TADCliente *cliente = NULL;
    TADFactura *factura = NULL;

    cliente = clientes->obtener(ui->edt_detalle_buscar->text());

    QString item = ui->lst_detalle_facturas->currentItem()->text();
    QString serie = item.split("-").at(0);
    int correlativo = item.split("-").at(1).toInt();

    factura = cliente->getFacturas()->obtener(serie, correlativo);

    DetalleDialog dialog(this);
    dialog.setWindowTitle("Detalle factura");
    dialog.setFactura(cliente, factura);
    if (dialog.exec() == QDialog::Rejected)
        cliente->getFacturas()->eliminar(factura->getSerie(), factura->getCorrelativo());

    limpiarLista(ui->lst_detalle_facturas);
    ui->edt_detalle_no_facturas->setText(QString::number(cliente->getFacturas()->contar()));
    cliente->getFacturas()->llenarLista(ui->lst_detalle_facturas);
}
