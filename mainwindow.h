#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QFileDialog>
#include <QMessageBox>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_actionCargar_JSON_triggered();

    void on_actionExportar_JSON_triggered();

    void on_btn_producto_agregar_clicked();

    void on_btn_producto_eliminar_clicked();

    void on_btn_producto_limpiar_clicked();

    void on_btn_producto_detalle_clicked();

    void on_btn_producto_grafico_clicked();

    void on_btn_producto_carga_clicked();

private:
    Ui::MainWindow *ui;

    abrirSelectorArchivos();
};

#endif // MAINWINDOW_H
