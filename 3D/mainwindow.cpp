#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "ekran.h"

float Tx = 0, Ty = 0, Tz = 0, Rx = 0, Ry = 0, Rz = 0, Sx = 100, Sy = 100, Sz = 100, Shx = 0, Shy = 0, Shz = 0;

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



void MainWindow::on_horizontalSlider_2_valueChanged(int value)
{
    Tx = value;
    ui->widok->transform();
}


void MainWindow::on_horizontalSlider_valueChanged(int value)
{
    Ty = value;
    ui->widok->transform();
}


void MainWindow::on_horizontalSlider_3_valueChanged(int value)
{
    Rx = value;

    ui->widok->transform();
}


void MainWindow::on_horizontalSlider_4_valueChanged(int value)
{
    Sx = value;

    ui->widok->transform();
}


void MainWindow::on_horizontalSlider_5_valueChanged(int value)
{
    Sy = value;

    ui->widok->transform();
}



void MainWindow::on_horizontalSlider_8_valueChanged(int value)
{
    Tz = value;

    ui->widok->transform();
}


void MainWindow::on_horizontalSlider_9_valueChanged(int value)
{
    Sz = value;

    ui->widok->transform();
}



void MainWindow::on_horizontalSlider_11_valueChanged(int value)
{
    Ry = value;

    ui->widok->transform();
}


void MainWindow::on_horizontalSlider_12_valueChanged(int value)
{
    Rz = value;

    ui->widok->transform();
}

