#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "ekran.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
private slots:
    void on_line_clicked();
    void on_elipse_clicked();
    void on_circle_clicked();
    void on_shape_clicked();
    void on_spinBox_valueChanged(int arg1);
    void on_clear_clicked();

    void on_bezier_clicked();

    void on_horizontalSlider_2_valueChanged(int value);

    void on_pushButton_2_clicked();


private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
