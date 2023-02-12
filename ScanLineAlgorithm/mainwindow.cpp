#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "ekran.h"


extern int action;
extern int slider;
extern int sliderB;


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


void MainWindow::on_clear_clicked()
{
    ui->widok->clear();
    qDebug("Cleared");
}











