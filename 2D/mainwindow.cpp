#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "ekran.h"

float Tx = 0, Ty = 0, Rx = 0, Sx = 100, Sy = 100, Shx = 0, Shy = 0;

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


void MainWindow::on_horizontalSlider_6_valueChanged(int value)
{
    Shx = value;

    ui->widok->transform();
}


void MainWindow::on_horizontalSlider_7_valueChanged(int value)
{
    Shy = value;

    ui->widok->transform();
}

