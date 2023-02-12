#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "ekran.h"
#include "ekran_2.h"
#include <QColor>
#include <QMouseEvent>
#include <QPainter>
#include <QVector>
#include <QImage>
#include <algorithm>
QVector<Point> Widok;
QVector<Point> Points;
int MaxY;
int MinY;
int MaxX;
int MinX;
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


void MainWindow::rysuj(){

    double u,v,w, x_t, y_t;

    uchar *pix, *sourcepix;

    double Wyz = ((Widok[1].x - Widok[0].x) * (Widok[2].y - Widok[0].y)) - ((Widok[1].y - Widok[0].y) * (Widok[2].x - Widok[0].x));
    for(int y = 0; y < 600; y++){
        for(int x = 0; x < 600; x++){
            v = (double)((((x - Widok[0].x) * (Widok[2].y - Widok[0].y)) - ((y - Widok[0].y) * (Widok[2].x - Widok[0].x))) / Wyz);
            w = (double)((((Widok[1].x - Widok[0].x) * (y - Widok[0].y)) - ((Widok[1].y - Widok[0].y) * (x - Widok[0].x))) / Wyz);
            u = (double)1-v-w;

            if((u > 0 && u < 1) && (v > 0 && v < 1) && (w > 0 && w < 1))
            {
                x_t = floor(u * (double)Points[0].x + v * (double)Points[1].x + w * (double)Points[2].x);
                y_t = floor(u * (double)Points[0].y + v * (double)Points[1].y + w * (double)Points[2].y);

                pix = ui->widok_2->im.scanLine(y);
                sourcepix = ui->widok->im.scanLine(y_t);

                pix[4 * x] = sourcepix[4 * (int)x_t];
                pix[4 * x + 1] = sourcepix[4 * (int)x_t + 1];
                pix[4 * x + 2] = sourcepix[4 * (int)x_t + 2];
                update();
            }
        }
    }
    update();
}


void MainWindow::on_pushButton_clicked()
{
    if((int)Widok.size() == 3 && (int)Points.size() == 3){
        ui->widok_2->im.fill(0);
        ui->widok->im = ui->widok->im_2;
        rysuj();
        ui->widok->drawPoints();
    }
}

