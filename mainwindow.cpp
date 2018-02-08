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

void MainWindow::on_actionCargar_JSON_triggered()
{
    QString filename = QFileDialog::getOpenFileName(
                this,
                "Seleccionar archivo",
                "/home/marco/Escritorio/",
                "JSON files(*.JSON);;JSON files(*.json)"
                );
    QMessageBox::information(this, "File name", filename);
}

void MainWindow::on_actionExportar_JSON_triggered()
{

}
