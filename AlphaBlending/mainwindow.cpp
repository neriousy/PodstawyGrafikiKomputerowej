#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "ekran.h"


int options[3] = {0, 0, 0};
float sliders[3] = {1, 1, 1};


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



void MainWindow::on_comboBox_currentIndexChanged(int index)
{
    options[0] = index;
    qDebug("%d", index);
    ui->widok->alphaBlend();
}


void MainWindow::on_comboBox_2_currentIndexChanged(int index)
{
    options[1] = index;
    qDebug("%d", index);
    ui->widok->alphaBlend();
}


void MainWindow::on_comboBox_3_currentIndexChanged(int index)
{
    options[2] = index;
    qDebug("%d", index);
    ui->widok->alphaBlend();
}


void MainWindow::on_horizontalSlider_valueChanged(int value)
{
    sliders[0] = value / 100.;
    qDebug("%d", value);
    ui->widok->alphaBlend();
}


void MainWindow::on_horizontalSlider_2_valueChanged(int value)
{
    sliders[1] = value / 100.;
    qDebug("%d", value);
    ui->widok->alphaBlend();
}


void MainWindow::on_horizontalSlider_3_valueChanged(int value)
{
    sliders[2] = value / 100.;
    qDebug("%d", value);
    ui->widok->alphaBlend();
}

