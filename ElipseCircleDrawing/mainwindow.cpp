#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "ekran.h"

extern int action;
extern int slider;
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

void MainWindow::on_line_clicked()
{
    action = 0;
    qDebug("action: %d", action);
}


void MainWindow::on_circle_clicked()
{
    action = 1;
    qDebug("action: %d", action);
}


void MainWindow::on_elipse_clicked()
{
    action = 2;
    qDebug("action: %d", action);
}

void MainWindow::on_shape_clicked()
{
    action = 3;
    qDebug("action: %d", action);
}


void MainWindow::on_spinBox_valueChanged(int arg1)
{
    slider = arg1;
    qDebug("slider: %d", slider);
}


void MainWindow::on_clear_clicked()
{
    ui->widok->clear();
}

