#include "ekran_2.h"
#include "ekran.h"
#include <QMouseEvent>
#include <QPainter>
#include <QVector>
#include <algorithm>
#include "mainwindow.h"
#include <QColor>

extern QVector<Point> Widok;

ekran_2::ekran_2(QWidget *parent)
    : QWidget{parent},
      im(500, 500, QImage::Format_RGB32)
{

    im.fill(0);
    im.load(":/image/image/2.jpg");
    im = im.scaled(500, 500, Qt::KeepAspectRatio);
    im_2 = im;

}

void ekran_2::paintEvent(QPaintEvent *){
    QPainter p(this);
    p.fillRect(0, 0, width(), height(), Qt::green);
    p.drawImage(0, 0, im);
}

bool ekran_2::isInside(int x, int y){
    if(x > 0 && y > 0 && x < 500 && y < 500){
        return true;
    }
    return false;
}


void ekran_2::putPixel(int x, int y, int r, int g, int b){
    if(ekran_2::isInside(x, y)){
        uchar *pix = im.scanLine(y);
        pix[4*x] = b;
        pix[4*x + 1] = g;
        pix[4*x + 2] = r;
        update();
    }

}


void ekran_2::drawPoints(){
    for(int i = 0; i < (int)Widok.size() - 1; i++){
        ekran_2::drawLine(Widok[i].x, Widok[i].y, Widok[i+1].x, Widok[i + 1].y);
    }
    if((int)Widok.size() == 3){
        ekran_2::drawLine(Widok[0].x, Widok[0].y, Widok[2].x, Widok[2].y);
    }
}

int ekran_2::findPoint(int x, int y){
    float distance;
    int index = 0;
    for(int i = 0; i < (int)Widok.size(); i++){
        if(i == 0){
            distance = sqrt(pow((x - Widok[i].x), 2) + pow((y - Widok[i].y), 2));
        }else{
            if(distance > sqrt(pow((x - Widok[i].x), 2) + pow((y - Widok[i].y), 2))){
                index = i;
                distance = sqrt(pow((x - Widok[i].x), 2) + pow((y - Widok[i].y), 2));
            }
        }
    }

    return index;
}
void ekran_2::mousePressEvent(QMouseEvent *e){
    QPoint mouse = e->pos();
    this->x1 = mouse.x();
    this->y1 = mouse.y();

    if(e->button() == Qt::LeftButton){
        Point temp;
        temp.x = mouse.x();
        temp.y = mouse.y();
        ekran_2::putPixel(temp.x, temp.y, 255, 0 ,0);
        if((int)Widok.size() < 3){
            Widok.push_back(temp);
            qDebug("Pkt %d do prawego ekranu zostal dodany X:%d Y:%d", (int)Widok.size(), temp.x, temp.y);
        }
        ekran_2::drawPoints();
    }

    if(e->button() == Qt::MiddleButton){
        im = im_2;
        int index = ekran_2::findPoint(mouse.x(), mouse.y());
        Widok[index].x = mouse.x();
        Widok[index].y = mouse.y();
        ekran_2::drawPoints();
        update();
    }
}

void ekran_2::mouseMoveEvent(QMouseEvent *e){
    QPoint mouse = e->pos();
    if(Widok.size()){
        if(e->buttons() == Qt::MiddleButton){
            im = im_2;
            int index = ekran_2::findPoint(mouse.x(), mouse.y());
            Widok[index].x = mouse.x();
            Widok[index].y = mouse.y();
            ekran_2::drawPoints();
            update();
        }
    }

}


void ekran_2::drawLine(int x1, int y1, int x2, int y2){
    double m, y, x;
    int dx, dy;

    dx = std::abs(x2 - x1);
    dy = std::abs(y2 - y1);
    if(x1 == x2 && y1 == y2){
        ekran_2::putPixel(x1, y1);
    }else{
        if(dx > dy){
            if(x1 > x2){
                std::swap(x1, x2);
                std::swap(y1, y2);
            }
             m = (double)(y2-y1)/(x2-x1);
            for(int x = x1; x <= x2; x++){
                y = m * (x - x1) + y1;
                ekran_2::putPixel(x, (int)y);
            }
        } else{
            if(y1 > y2){
                std::swap(x1, x2);
                std::swap(y1, y2);
            }

            m = (double)(x2-x1)/(y2-y1);
            for(int y = y1; y <= y2; y++){
                x = m * (y - y1) + x1;
                ekran_2::putPixel((int)x, y);
            }
        }
    }
}





