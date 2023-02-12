#include "mainwindow.h"
#include "ui_mainwindow.h"


extern float R, G, B, H, S, V;
float sliderH = 0, sliderS = 0, sliderV = 0;
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}


//void MainWindow::on_Green_valueChanged(int value)
//{
//    //G = value;
//    //qDebug("Green: %d", G);
//    ui->widget->paintRGB(value, 1);
//}


//void MainWindow::on_Red_valueChanged(int value)
//{
//    //R = value;
//    //qDebug("Red: %d", R);

//    ui->widget->paintRGB(value, 0);

//}


//void MainWindow::on_Blue_valueChanged(int value)
//{
//    //B = value;
//    //qDebug("Blue %d", B);

//    ui->widget->paintRGB(value, 2);
//}


void MainWindow::SlidersRGB(){
    ui->h->setSliderPosition(H);
    ui->s->setSliderPosition(S);
    ui->v->setSliderPosition(V);
}

void MainWindow::SlidersHSV(){
    ui->Red->setSliderPosition(R);
    ui->Green->setSliderPosition(G);
    ui->Blue->setSliderPosition(B);
    //qDebug("R: %f, G: %f, B: %f", R, G, B);
}

void MainWindow::on_Red_sliderMoved(int position)
{
     ui->widget->paintRGB(position, 0);
     R = position;
     ui->widget->RBGtoHSV(R, G, B);
     SlidersRGB();

}


void MainWindow::on_Green_sliderMoved(int position)
{
     ui->widget->paintRGB(position, 1);
     G = position;
     ui->widget->RBGtoHSV(R, G, B);
     SlidersRGB();
}


void MainWindow::on_Blue_sliderMoved(int position)
{
    ui->widget->paintRGB(position, 2);
    B = position;
    ui->widget->RBGtoHSV(R, G, B);
    SlidersRGB();
}


void MainWindow::on_h_sliderMoved(int position)
{
    ui->widget->paintHSV(position, 3);
    H = position;
    ui->widget->HSVtoRGB(H, S / 100., V / 100.);

    SlidersHSV();

}


void MainWindow::on_s_sliderMoved(int position)
{
    ui->widget->paintHSV(position, 4);
    S = position;
    ui->widget->HSVtoRGB(H, S / 100., V / 100.);

    SlidersHSV();
}


void MainWindow::on_v_sliderMoved(int position)
{
    ui->widget->paintHSV(position, 5);
    V = position;
    ui->widget->HSVtoRGB(H , S / 100., V / 100.);

    SlidersHSV();
}

