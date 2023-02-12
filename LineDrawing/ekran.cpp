#include "ekran.h"
#include <QMouseEvent>
#include <QPainter>

Ekran::Ekran(QWidget *parent)
    : QWidget{parent},
      im(600, 600, QImage::Format_RGB32)
{
    im.fill(0);
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

void Ekran::putPixel(int x, int y){
    if(Ekran::isInside(x, y)){
        uchar *pix = im.scanLine(y);
        pix[4*x] = 255;
        pix[4*x + 1] = 255;
        pix[4*x + 2] = 255;
        update();
    }

}

void Ekran::mouseMoveEvent(QMouseEvent *e){
    QPoint mouse = e->pos();
    this->x2 = mouse.x();
    this->y2 = mouse.y();
    this->im = im_2;
    Ekran::drawLine(this->x1, this->y1, this->x2, this->y2);
}

void Ekran::mousePressEvent(QMouseEvent *e){
    QPoint mouse = e->pos();
    this->x1 = mouse.x();
    this->y1 = mouse.y();
    this->x2 = mouse.x();
    this->y2 = mouse.y();
    Ekran::putPixel(mouse.x(), mouse.y());
    this->im_2 = im;

}

void Ekran::drawLine(int x1, int y1, int x2, int y2)
{
    double m, y, x;
    int dx, dy;

    dx = std::abs(x2 - x1);
    dy = std::abs(y2 - y1);


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


