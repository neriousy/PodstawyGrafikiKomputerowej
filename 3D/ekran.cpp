#include "ekran.h"
#include <QMouseEvent>
#include <QPainter>
#include <QVector>
#include <algorithm>
#include <armadillo>

QVector<Point3D> Points3D;
QVector<Point3D> endPoint;
QVector<Point> Points2D;

extern float Tx, Ty, Tz, Rx, Ry, Rz, Sx, Sy, Sz, Shx, Shy, Shz;


Ekran::Ekran(QWidget *parent)
    : QWidget{parent},
      im(800, 600, QImage::Format_RGB32)
{
    im.fill(0);
    Point3D temp;

    temp.x = -100;
    temp.y = -100;
    temp.z = 150;

    Points3D.push_back(temp);

    temp.x = -100;
    temp.y = 100;
    temp.z = 150;

    Points3D.push_back(temp);

    temp.x = 100;
    temp.y = 100;
    temp.z = 150;

    Points3D.push_back(temp);

    temp.x = 100;
    temp.y = -100;
    temp.z = 150;

    Points3D.push_back(temp);

    temp.x = -100;
    temp.y = -100;
    temp.z = 300;

    Points3D.push_back(temp);

    temp.x = -100;
    temp.y = 100;
    temp.z = 300;

    Points3D.push_back(temp);

    temp.x = 100;
    temp.y = 100;
    temp.z = 300;

    Points3D.push_back(temp);

    temp.x = 100;
    temp.y = -100;
    temp.z = 300;

    Points3D.push_back(temp);

    transform();


}

void Ekran::paintEvent(QPaintEvent *){
    QPainter p(this);
    p.fillRect(0, 0, width(), height(), Qt::green);
    p.drawImage(0, 0, im);
}

bool Ekran::isInside(int x, int y){
    if(x > 0 && y > 0 && x < 600 && y < 600){
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
    drawLine(VPoints[0].x, VPoints[0].y, VPoints[1].x, VPoints[1].y);
    drawLine(VPoints[0].x, VPoints[0].y, VPoints[3].x, VPoints[3].y);
    drawLine(VPoints[1].x, VPoints[1].y, VPoints[2].x, VPoints[2].y);
    drawLine(VPoints[2].x, VPoints[2].y, VPoints[3].x, VPoints[3].y);
    drawLine(VPoints[0].x, VPoints[0].y, VPoints[4].x, VPoints[4].y);
    drawLine(VPoints[1].x, VPoints[1].y, VPoints[5].x, VPoints[5].y);
    drawLine(VPoints[2].x, VPoints[2].y, VPoints[6].x, VPoints[6].y);
    drawLine(VPoints[3].x, VPoints[3].y, VPoints[7].x, VPoints[7].y);
    drawLine(VPoints[4].x, VPoints[4].y, VPoints[5].x, VPoints[5].y);
    drawLine(VPoints[4].x, VPoints[4].y, VPoints[7].x, VPoints[7].y);
    drawLine(VPoints[5].x, VPoints[5].y, VPoints[6].x, VPoints[6].y);
    drawLine(VPoints[6].x, VPoints[6].y, VPoints[7].x, VPoints[7].y);

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

    QVector<Point3D> temp = Points3D;
    arma::mat XYZ(4,1); arma::mat output;
    arma::mat T(4,4, arma::fill::eye);
    arma::mat Scal(4,4, arma::fill::eye);
    arma::mat Rotx(4,4, arma::fill::eye);
    arma::mat Rotz(4,4, arma::fill::eye);
    arma::mat Roty(4,4, arma::fill::eye);
    arma::mat A(4,4, arma::fill::eye);
    arma::mat Lean(4,4, arma::fill::eye);
    arma::mat MinusA(4,4, arma::fill::eye);
    arma::mat Trans;


    int d = 1000;
    T(0,3) = Tx; T(1,3) = Ty; T(2,3) = Tz;

    Rotx(1,1) = cos(Rx * M_PI / 180.); Rotx(1,2) = -sin(Rx * M_PI / 180.); Rotx(2,1) = sin(Rx * M_PI / 180.); Rotx(2,2) = cos(Rx * M_PI / 180.);
    Rotz(0,0) = cos(Rz * M_PI / 180.); Rotz(0,1) = -sin(Rz * M_PI / 180.); Rotz(1,0) = sin(Rz * M_PI / 180.); Rotz(1,1) = cos(Rz * M_PI / 180.);
    Roty(0,0) = cos(Ry * M_PI / 180.); Roty(2,0) = -sin(Ry * M_PI / 180.); Roty(0,2) = sin(Ry * M_PI / 180.); Roty(2,2) = cos(Ry * M_PI / 180.);

    A(0,3) = 0;
    A(1,3) = 0;
    A(2,3) = 225;

    MinusA(0,3) = -0;
    MinusA(1,3) = -0;
    MinusA(2,3) = -225;

    //Rotx = A * Rotx * MinusA;
    //Rotz = A * Rotz * MinusA;
    //Roty = A * Roty * MinusA;

    Scal(0,0) = Sx/100.;
    Scal(1,1) = Sy/100.;
    Scal(2,2) = Sz/100.;
    Scal(3,3) = 1;

    Lean(0,1) = Shx / 100.;
    Lean(1,0) = Shy / 100.;



    XYZ(3,0) = 1;
    Trans = T * A *  Rotz * Roty * Rotx * Scal * MinusA;

    for(int i = 0; i < (int)temp.size(); i++){
        XYZ(0,0) = temp[i].x;
        XYZ(1,0) = temp[i].y;
        XYZ(2,0) = temp[i].z;
        output = Trans * XYZ;
        Point3D temp3D;
        temp3D.x = (int)output(0,0);
        temp3D.y = (int)output(1,0);
        temp3D.z = (int)output(2,0);
        endPoint.push_back(temp3D);

        Point temp2D;
        temp2D.x = (((endPoint[i].x) * d) / (endPoint[i].z + d)) + 300;
        temp2D.y = (((endPoint[i].y) * d) / (endPoint[i].z + d)) + 300;

        Points2D.push_back(temp2D);

       // qDebug("I: %d, X: %d, Y:%d", i, temp[i].x, temp[i].y);
    }

    drawPoints(Points2D);
    Points2D.clear();
    endPoint.clear();
//    std::cout<<std::endl;
//    for(int i = 0; i < (int)Points.size(); i++){
//        qDebug("X:%d Y:%d", temp[i].x, temp[i].y);
//       // qDebug("I: %d, X: %d, Y:%d", i, temp[i].x, temp[i].y);
//    }

}




