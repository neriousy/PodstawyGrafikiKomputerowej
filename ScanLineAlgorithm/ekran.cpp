#include "ekran.h"
#include <QMouseEvent>
#include <QPainter>
#include <QVector>
#include <algorithm>


QVector<Point> Points;



Ekran::Ekran(QWidget *parent)
    : QWidget{parent},
      im(800, 600, QImage::Format_RGB32)
{
    im.fill(0);
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

void Ekran::drawPoints(){

    for(int i = 0; i < (int)Points.size(); i++){
        Ekran::putPixel(Points[i].x, Points[i].y, 255, 0, 0);
        Ekran::putPixel(Points[i].x+1, Points[i].y, 255, 0, 0);
        Ekran::putPixel(Points[i].x, Points[i].y+1, 255, 0, 0);
        Ekran::putPixel(Points[i].x+1, Points[i].y+1, 255, 0, 0);
    }
    update();

    if((int)Points.size() > 1){
        for(int i = 0; i < (int)Points.size() - 1; i++){
            Ekran::drawLine(Points[i].x, Points[i].y, Points[i + 1].x, Points[i + 1].y);
        }
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
        Points.push_back(temp);
        qDebug("Added point x: %d y: %d", this->x1, this->y1);
        Ekran::drawPoints();
    }
    if(e->button() == Qt::RightButton){
        drawLine(Points[0].x, Points[0].y, Points[(int)Points.size() - 1].x, Points[(int)Points.size() - 1].y);
        Ekran::scanLine();
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


void Ekran::clear(){
    im.fill(0);
    Points.clear();
    update();
}

bool isIntersection(int p1, int p2, int y){
    if((p1 > y && p2 < y) || (p1 < y && p2 > y)){
        return true;
    } else if((p1 < p2 && p1 == y) || (p2 < p1 && p2 == y)){
        return true;
    }
    return false;
}

void Ekran::scanLine(){
    int maxY, minY;
    std::vector<int> intersections;
    int x;

    if((int)Points.size() > 2){
        maxY = Points[0].y;
        minY = Points[0].y;
        for(int i = 0; i < (int)Points.size(); i++){
            if(Points[i].y > maxY){
                maxY = Points[i].y;
            }
            if(Points[i].y < minY){
                minY = Points[i].y;
            }
        }
    }else{
        return;
    }

    qDebug("MinY : %d, MaxY: %d", minY, maxY);
    for(int y = minY + 1; y < maxY; y++){
        for(int i = 0; i < (int)Points.size(); i++){

            if(isIntersection(Points[i].y, Points[(i + 1) % (Points.size())].y, y)){
                if(Points[i].y == Points[(i+1) % Points.size()].y){
                    x = 0;
                }else{
                    x = Points[i].x + (y - Points[i].y) * (Points[(i + 1) % Points.size()].x - Points[i].x) / (Points[(i + 1) % Points.size()].y - Points[i].y);
                }
                intersections.push_back(x);
            }
        }
        std::sort(intersections.begin(), intersections.end());

        for(int i = 0; i < (int)intersections.size(); i += 2){
            for(int X = intersections[i] + 1; X < intersections[i + 1] - 1; X++){
                Ekran::putPixel(X, y, 255, 0, 0);
            }
        }

        intersections.clear();
    }
}
