#include "detalledialog.h"
#include "ui_detalledialog.h"

DetalleDialog::DetalleDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DetalleDialog)
{
    ui->setupUi(this);
    cliente = NULL;
    factura = NULL;
}

DetalleDialog::~DetalleDialog()
{
    delete ui;
}

void DetalleDialog::on_btn_factura_eliminar_clicked()
{
    reject();
}

void DetalleDialog::on_btn_factura_exportar_clicked()
{
    if (factura != NULL && !factura->getDetalles()->vacio())
    {
            QString archivo("FE-");
            archivo.append(ui->edt_factura_serie->text());
            archivo.append("-");
            archivo.append(ui->edt_factura_correlativo->text());
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
            painter.drawText(getX(0), y + 20, ui->edt_factura_serie->text());
            painter.drawText(getX(1), y, "CORRELATIVO:");
            painter.drawText(getX(1), y + 20, ui->edt_factura_correlativo->text());
            painter.drawText(getX(4), y, "NIT:");
            painter.drawText(getX(4), y + 20, ui->edt_factura_nit->text());
            painter.drawText(getX(5), y, "Cliente:");
            painter.drawText(getX(5), y + 20, ui->edt_factura_nombre->text());
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

        for (int i = 0; i < ui->tbl_factura->rowCount(); i++)
        {
            painter.drawText(getX(0), y, ui->tbl_factura->item(i, CANTIDAD)->text());
            painter.drawText(getX(1), y, ui->tbl_factura->item(i, CODIGO)->text());
            painter.drawText(getX(2), y, ui->tbl_factura->item(i, PRODUCTO)->text());
            painter.drawText(getX(4), y, ui->tbl_factura->item(i, PRECIO_U)->text());
            painter.drawText(getX(5), y, ui->tbl_factura->item(i, DESCUENTO)->text());
            painter.drawText(getX(6), y, ui->tbl_factura->item(i, TOTAL)->text());
            y += 20;
        }

        painter.drawLine(getX(0), y, getX(6) + 100, y);
        painter.drawText(getX(6), y + 20, ui->edt_factura_total->text());
        painter.end();
        std::cout << "Creación de pdf completo" << std::endl;
        QString cmd("xdg-open ");
        cmd.append(archivo);
        qDebug() << cmd;
        system(cmd.toLatin1().data());
    }

    accept();
}

void DetalleDialog::setFactura(TADCliente *_cliente, TADFactura *_factura)
{
    cliente = _cliente;
    factura = _factura;

    cargarDetalle();
}

void DetalleDialog::cargarDetalle()
{
    ui->edt_factura_nit->setText(cliente->getNit());
    ui->edt_factura_nombre->setText(cliente->getNombre());
    ui->edt_factura_serie->setText(factura->getSerie());
    ui->edt_factura_correlativo->setText(QString::number(factura->getCorrelativo()));

    PilaDetalle *pila = factura->getDetalles();
    double total;
    total = pila->cargarDetalle(ui->tbl_factura);
    ui->edt_factura_total->setText(QString::number(total));
    qDebug() << "Se ha cargado el detalle de factura" << endl;
}

/**
 * @brief DetalleDialog::getX
 * @param i Numero de columna [0-6]
 * @return
 */
int DetalleDialog::getX(int i)
{
    return 100 * i;
}
