#include "ekran.h"
#include <QMouseEvent>
#include <QPainter>
#include <QVector>
#include <algorithm>
#include <armadillo>

QVector<Point> Points;
extern float Tx, Ty, Rx, Sx , Sy, Shx, Shy;


Ekran::Ekran(QWidget *parent)
    : QWidget{parent},
      im(800, 600, QImage::Format_RGB32)
{
    im.fill(0);
    Point temp;
    temp.x= 399 ; temp.y = 50;
    Points.push_back(temp);

    temp.x= 266 ; temp.y = 150;
    Points.push_back(temp);

    temp.x= 532 ; temp.y = 150;
    Points.push_back(temp);

    temp.x= 266 ; temp.y = 400;
    Points.push_back(temp);

    temp.x= 532 ; temp.y = 400;
    Points.push_back(temp);

    drawPoints(Points);

}

void Ekran::paintEvent(QPaintEvent *){
    QPainter p(this);
    p.fillRect(0, 0, width(), height(), Qt::green);
    p.drawImage(0, 0, im);
}

bool Ekran::isInside(int x, int y){
    if(x > 0 && y > 0 && x < 800 && y < 600){
        return true;
    }
    return false;
}


void Ekran::putPixel(int x, int y, int r, int g, int b){
    if(Ekran::isInside(x, y)){
        uchar *pix = im.scanLine(y);
        pix[4*x] = b;
        pix[4*x + 1] = g;
        pix[4*x + 2] = r;
        update();
    }
}

void Ekran::drawPoints(QVector<Point> VPoints){

    im.fill(0);
    Ekran::drawLine(VPoints[0].x, VPoints[0].y, VPoints[1].x, VPoints[1].y);
    Ekran::drawLine(VPoints[0].x, VPoints[0].y, VPoints[2].x, VPoints[2].y);
    Ekran::drawLine(VPoints[1].x, VPoints[1].y, VPoints[2].x, VPoints[2].y);
    Ekran::drawLine(VPoints[1].x, VPoints[1].y, VPoints[3].x, VPoints[3].y);
    Ekran::drawLine(VPoints[2].x, VPoints[2].y, VPoints[4].x, VPoints[4].y);
    Ekran::drawLine(VPoints[3].x, VPoints[3].y, VPoints[4].x, VPoints[4].y);

}


void Ekran::drawLine(int x1, int y1, int x2, int y2){
    double m, y, x;
    int dx, dy;

    dx = std::abs(x2 - x1);
    dy = std::abs(y2 - y1);
    if(x1 == x2 && y1 == y2){
        Ekran::putPixel(x1, y1);
    }else{
        if(dx > dy){
            if(x1 > x2){
                std::swap(x1, x2);
                std::swap(y1, y2);
            }
             m = (double)(y2-y1)/(x2-x1);
            for(int x = x1; x <= x2; x++){
                y = m * (x - x1) + y1;
                Ekran::putPixel(x, (int)y);
            }
        } else{
            if(y1 > y2){
                std::swap(x1, x2);
                std::swap(y1, y2);
            }

            m = (double)(x2-x1)/(y2-y1);
            for(int y = y1; y <= y2; y++){
                x = m * (y - y1) + x1;
                Ekran::putPixel((int)x, y);
            }
        }
    }
}

void Ekran::transform(){

    QVector<Point> temp = Points;
    arma::mat XY(3,1); arma::mat output;
    arma::mat T(3,3, arma::fill::eye);
    arma::mat Scal(3,3, arma::fill::eye);
    arma::mat Rot(3,3, arma::fill::eye);
    arma::mat A(3,3, arma::fill::eye);
    arma::mat Lean(3,3, arma::fill::eye);
    arma::mat MinusA(3,3, arma::fill::eye);
    arma::mat Trans;
    int X0 = 400;
    int Y0 = 300;

    T(0,2) = Tx; T(1,2) = Ty;

    Rot(0,0) = cos(Rx * M_PI / 180.); Rot(0,1) = -sin(Rx * M_PI / 180.); Rot(1,0) = sin(Rx * M_PI / 180.); Rot(1,1) = cos(Rx * M_PI / 180.);

    Scal(0,0) = Sx/100.;
    Scal(1,1) = Sy/100.;

    Lean(0,1) = Shx / 100.;
    Lean(1,0) = Shy / 100.;

    A(0,2) = X0;
    A(1,2) = Y0;

    MinusA(0,2) = -X0;
    MinusA(1,2) = -Y0;


    XY(2,0) = 1;
    Trans = T * A * Rot * Scal * MinusA * Lean;

    for(int i = 0; i < (int)Points.size(); i++){
        XY(0,0) = Points[i].x;
        XY(1,0) = Points[i].y;
        output = Trans * XY;
        temp[i].x = (int)output(0,0);
        temp[i].y = (int)output(1,0);
       // qDebug("I: %d, X: %d, Y:%d", i, temp[i].x, temp[i].y);
    }

    drawPoints(temp);
//    std::cout<<std::endl;
//    for(int i = 0; i < (int)Points.size(); i++){
//        qDebug("X:%d Y:%d", temp[i].x, temp[i].y);
//       // qDebug("I: %d, X: %d, Y:%d", i, temp[i].x, temp[i].y);
//    }

}




