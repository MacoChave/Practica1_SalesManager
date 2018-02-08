#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

MainWindow::abrirSelectorArchivos()
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
}

void MainWindow::on_btn_producto_eliminar_clicked()
{
}

void MainWindow::on_btn_producto_limpiar_clicked()
{
}

void MainWindow::on_btn_producto_detalle_clicked()
{
}

void MainWindow::on_btn_producto_grafico_clicked()
{
}

void MainWindow::on_btn_producto_carga_clicked()
{
    QString filename = abrirSelectorArchivos();
}
