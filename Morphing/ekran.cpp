#include "ekran.h"
#include <QMouseEvent>
#include <QPainter>
#include <QVector>
#include <algorithm>
#include <QColorSpace>
#include <QColor>

extern QVector<Point> Points;



Ekran::Ekran(QWidget *parent)
    : QWidget{parent},
      im(500, 500, QImage::Format_RGB32)
{
    im.fill(0);
    im.load(":/image/image/1.jpg");
    im = im.scaled(500, 500, Qt::KeepAspectRatio);

    im_2 = im;
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

int Ekran::findPoint(int x, int y){
    float distance;
    int index = 0;
    for(int i = 0; i < (int)Points.size(); i++){
        if(i == 0){
            distance = sqrt(pow((x - Points[i].x), 2) + pow((y - Points[i].y), 2));
        }else{
            if(distance > sqrt(pow((x - Points[i].x), 2) + pow((y - Points[i].y), 2))){
                index = i;
                distance = sqrt(pow((x - Points[i].x), 2) + pow((y - Points[i].y), 2));
            }
        }
    }

    return index;
}

void Ekran::drawPoints(){
    for(int i = 0; i < (int)Points.size() - 1; i++){
        Ekran::drawLine(Points[i].x, Points[i].y, Points[i+1].x, Points[i + 1].y);
    }
    if((int)Points.size() == 3){
        Ekran::drawLine(Points[0].x, Points[0].y, Points[2].x, Points[2].y);
    }
}

void Ekran::mousePressEvent(QMouseEvent *e){
    QPoint mouse = e->pos();
    this->x1 = mouse.x();
    this->y1 = mouse.y();

    if(e->button() == Qt::LeftButton){
        Point temp;
        temp.x = mouse.x();
        temp.y = mouse.y();
        if((int)Points.size() < 3){
            Points.push_back(temp);
            qDebug("Pkt %d do lewego ekranu zostal dodany X:%d Y:%d", (int)Points.size(), temp.x, temp.y);
        }
        Ekran::drawPoints();
    }

    if(e->button() == Qt::MiddleButton){
        im = im_2;
        int index = Ekran::findPoint(mouse.x(), mouse.y());
        Points[index].x = mouse.x();
        Points[index].y = mouse.y();
        Ekran::drawPoints();
        update();
    }
}

void Ekran::mouseMoveEvent(QMouseEvent *e){
    QPoint mouse = e->pos();
    if(Points.size()){
        if(e->buttons() == Qt::MiddleButton){
            im = im_2;
            int index = Ekran::findPoint(mouse.x(), mouse.y());
            Points[index].x = mouse.x();
            Points[index].y = mouse.y();
            Ekran::drawPoints();
            update();
        }
    }
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





