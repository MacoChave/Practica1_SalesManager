#include "facturardialog.h"
#include "ui_facturardialog.h"

FacturarDialog::FacturarDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::FacturarDialog)
{
    ui->setupUi(this);
    productos = NULL;
    clientes = NULL;
    cliente = NULL;
    factura = NULL;
    correlativo = 0;
}

FacturarDialog::~FacturarDialog()
{
    delete ui;
}

void FacturarDialog::setDatos(ListaProducto *_productos, ListaCliente *_clientes, QList<QString> _series, int _correlativo)
{
    productos = _productos;
    clientes = _clientes;
    series = _series;
    correlativo = _correlativo;

    llenarComboBox();
}

void FacturarDialog::llenarComboBox()
{
    foreach (QString item, series) {
        ui->cmb_facturar_serie->addItem(item);
    }

    ui->edt_facturar_correlativo->setText(QString::number(correlativo));
    QDate currentDate = QDate::currentDate();
    ui->edt_facturar_fecha->setText(currentDate.toString("dd/MM/yy"));
    correlativo++;
}

void FacturarDialog::limpiarCampos()
{
    ui->edt_facturar_producto->clear();
    ui->edt_facturar_cantidad->clear();
    ui->edt_facturar_descuento->clear();
    ui->edt_facturar_fecha->clear();
    ui->edt_facturar_total->clear();
}

void FacturarDialog::limpiarTabla()
{
    ui->tbl_facturar_detalle->clear();
    ui->tbl_facturar_detalle->setRowCount(0);
}

/**
 * @brief DetalleDialog::getX
 * @param i Numero de columna [0-6]
 * @return
 */
int FacturarDialog::getX(int i)
{
    return 100 * i;
}

void FacturarDialog::cargarDetalle()
{
    if (factura != NULL)
    {
        PilaDetalle *pila = factura->getDetalles();
        double total;
        total = pila->cargarDetalle(ui->tbl_facturar_detalle);
        ui->edt_facturar_total->setText(QString::number(total));
        qDebug() << "Se ha cargado el detalle de factura" << endl;
    }
}

void FacturarDialog::on_edt_facturar_nit_editingFinished()
{
    QString nit;
    nit = ui->edt_facturar_nit->text();

    if (!nit.isEmpty())
    {
        cliente = clientes->obtener(nit);
        if (cliente == NULL)
        {
            if (nit.compare("0") == 0)
            {
                if (clientes->agregar(new TADCliente("0", "CF")))
                {
                    QMessageBox mensaje(this);
                    mensaje.setWindowTitle("Nuevo cliente");
                    mensaje.setText("Se agregó cliente CF");
                    mensaje.exec();

                    cliente = clientes->obtener(nit);
                }
            }
            else
            {
                QString nombre = QInputDialog::getText(
                            this,
                            "Nuevo cliente",
                            "Ingresar nombre de cliente "
                            );
                clientes->agregar(new TADCliente(nit, nombre));
                cliente = clientes->obtener(nit);
            }
        }

        ui->edt_facturar_nombre->setText(cliente->getNombre());
        if (factura != NULL)
            delete factura;
        factura = NULL;
        factura = new TADFactura();
    }
}

void FacturarDialog::on_btn_facturar_nuevo_clicked()
{
    if (factura != NULL)
    {
        if (!factura->getDetalles()->vacio())
        {
            factura->setSerie(ui->cmb_facturar_serie->currentText());
            factura->setCorrelativo(ui->edt_facturar_correlativo->text().toInt());
            cliente->getFacturas()->agregar(factura);
        }
        else
            delete factura;
    }
    factura = NULL;
    factura = new TADFactura();
    limpiarCampos();
    limpiarTabla();
    ui->edt_facturar_nit->clear();
    ui->edt_facturar_nombre->clear();
    ui->cmb_facturar_serie->setCurrentIndex(0);
    ui->edt_facturar_correlativo->setText(QString::number(correlativo));
    correlativo++;
}

void FacturarDialog::on_btn_facturar_graficar_clicked()
{
    if (factura != NULL && !factura->getDetalles()->vacio())
    {
            QString archivo("FE-");
            archivo.append(ui->cmb_facturar_serie->currentText());
            archivo.append("-");
            archivo.append(ui->edt_facturar_correlativo->text());
            archivo.append(".pdf");

            int y = 20;

            QPrinter printer;
            printer.setOutputFormat(QPrinter::PdfFormat);
            printer.setOutputFileName(archivo);
            QPainter painter;
            if (! painter.begin(&printer)) { // failed to open file
              qWarning("failed to open file, is it writable?");
              return;
            }
            painter.drawText(getX(0), y, "SERIE:");
            painter.drawText(getX(0), y + 20, ui->cmb_facturar_serie->currentText());
            painter.drawText(getX(1), y, "CORRELATIVO:");
            painter.drawText(getX(1), y + 20, ui->edt_facturar_correlativo->text());
            painter.drawText(getX(4), y, "NIT:");
            painter.drawText(getX(4), y + 20, ui->edt_facturar_nit->text());
            painter.drawText(getX(5), y, "Cliente:");
            painter.drawText(getX(5), y + 20, ui->edt_facturar_nombre->text());
            y += 80;

            painter.drawText(getX(0), y, "Cantidad");
            painter.drawText(getX(1), y, "Código");
            painter.drawText(getX(2), y, "Nombre");
            painter.drawText(getX(3), y, "Precio Unitario");
            painter.drawText(getX(5), y, "Descuento");
            painter.drawText(getX(6), y, "Valor Total");
            y += 20;

            painter.drawLine(getX(0), y, getX(6) + 100, y);
            painter.drawLine(getX(0), y + 5, getX(6) + 100, y + 5);
            y += 20;

        for (int i = 0; i < ui->tbl_facturar_detalle->rowCount(); i++)
        {
            painter.drawText(getX(0), y, ui->tbl_facturar_detalle->item(i, CANTIDAD)->text());
            painter.drawText(getX(1), y, ui->tbl_facturar_detalle->item(i, CODIGO)->text());
            painter.drawText(getX(2), y, ui->tbl_facturar_detalle->item(i, PRODUCTO)->text());
            painter.drawText(getX(4), y, ui->tbl_facturar_detalle->item(i, PRECIO_U)->text());
            painter.drawText(getX(5), y, ui->tbl_facturar_detalle->item(i, DESCUENTO)->text());
            painter.drawText(getX(6), y, ui->tbl_facturar_detalle->item(i, TOTAL)->text());
            y += 20;
        }

        painter.drawLine(getX(0), y, getX(6) + 100, y);
        painter.drawText(getX(6), y + 20, ui->edt_facturar_total->text());
        painter.end();
        std::cout << "Creación de pdf completo" << std::endl;
        QString cmd("xdg-open ");
        cmd.append(archivo);
        qDebug() << cmd;
        system(cmd.toLatin1().data());
    }
}

void FacturarDialog::on_btn_facturar_quitar_producto_clicked()
{
    factura->getDetalles()->pop();
    limpiarTabla();
}

void FacturarDialog::on_btn_facturar_vaciar_compra_clicked()
{
    factura->getDetalles()->limpiar();
    limpiarTabla();
}

void FacturarDialog::on_btn_facturar_eliminar_factura_clicked()
{
    delete factura;
    factura = NULL;
    limpiarTabla();
}

void FacturarDialog::on_btn_facturar_agregar_clicked()
{
    QString _codigo_prod, _cantidad, _descuento;
    _codigo_prod = ui->edt_facturar_producto->text();
    _cantidad = ui->edt_facturar_cantidad->text();
    _descuento = ui->edt_facturar_descuento->text();

    TADProducto *producto = productos->obtener(_codigo_prod);
    if (producto != NULL)
    {
        TADDetalle *detalle = new TADDetalle();
        detalle->setProducto(producto);
        detalle->setCantidad(_cantidad.toInt());
        detalle->setDescuento(_descuento.toDouble());

        factura->setDetalle(detalle);
        limpiarCampos();
        limpiarTabla();
        cargarDetalle();
    }
    else
    {
        QMessageBox mensaje(this);
        mensaje.setText("No se encontró el producto");
        mensaje.setWindowTitle("Error al buscar producto");
        mensaje.exec();
    }
}
