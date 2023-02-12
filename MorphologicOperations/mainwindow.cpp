#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "ekran.h"



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


void MainWindow::on_pushButton_2_clicked()
{
    ui->widok->operacja(1);
}


void MainWindow::on_pushButton_clicked()
{
    ui->widok->operacja(0);
}


void MainWindow::on_pushButton_3_clicked()
{
    ui->widok->otwarcie();
}


void MainWindow::on_pushButton_4_clicked()
{
     ui->widok->domkniecie();
}

