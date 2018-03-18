#include "dialogeficiencia.h"
#include "ui_dialogeficiencia.h"

DialogEficiencia::DialogEficiencia(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogEficiencia)
{
    ui->setupUi(this);
    nombre = "Producto";
    descripcion = "Descripcion del producto";
    precio = 0;
}

DialogEficiencia::~DialogEficiencia()
{
    delete ui;
}

double DialogEficiencia::cargarEstructura(int count)
{
    ListaProducto *lista = new ListaProducto();

    clock_t t1, t2;
    double secs;
    t1 = clock();

    for (int i = 0; i <= count; i++)
    {
        TADProducto *producto = new TADProducto();
        producto->setCodigo(QString::number(i));
        producto->setNombre(nombre);
        producto->setDescripcion(descripcion);
        producto->setPrecio(precio);

        lista->agregar(producto);
    }

    t2 = clock();
    secs = (double)(t2 - t1) / CLOCKS_PER_SEC;
    delete lista;

    return secs;
}

double DialogEficiencia::cargarQList(int count)
{
    QList<TADProducto *> *lista = new QList<TADProducto *>();

    clock_t t1, t2;
    double secs;
    t1 = clock();

    for (int i = 0; i <= count; i++)
    {
        TADProducto *producto = new TADProducto();
        producto->setCodigo(QString::number(i));
        producto->setNombre(nombre);
        producto->setDescripcion(descripcion);
        producto->setPrecio(precio);

        lista->push_back(producto);
    }

    t2 = clock();
    secs = (double)(t2 - t1) / CLOCKS_PER_SEC;
    lista->clear();

    return secs;
}

void DialogEficiencia::cargarQTable(int count)
{
    double tiempoEstructura, tiempoQList;
    tiempoEstructura = cargarEstructura(count);
    tiempoQList = cargarQList(count);

    ui->tbl_eficiencia->insertRow(ui->tbl_eficiencia->rowCount());
    ui->tbl_eficiencia->setItem(ui->tbl_eficiencia->rowCount() - 1, NUMERO_REGISTRO, new QTableWidgetItem(QString::number(count)));
    ui->tbl_eficiencia->setItem(ui->tbl_eficiencia->rowCount() - 1, ESTRUCTURA, new QTableWidgetItem(QString::number(tiempoEstructura)));
    ui->tbl_eficiencia->setItem(ui->tbl_eficiencia->rowCount() - 1, QLIST, new QTableWidgetItem(QString::number(tiempoQList)));
}

void DialogEficiencia::on_btn_eficiencia_short_clicked()
{
    cargarQTable(100);
}

void DialogEficiencia::on_btn_eficiencia_medium_clicked()
{
    cargarQTable(1000);
}

void DialogEficiencia::on_bnt_eficiencia_long_clicked()
{
    cargarQTable(10000);
}

void DialogEficiencia::on_btn_eficiencia_verylong_clicked()
{
    cargarQTable(100000);
}

void DialogEficiencia::on_btn_eficiencia_salir_clicked()
{
    reject();
}
