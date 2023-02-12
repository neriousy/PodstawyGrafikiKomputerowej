#include "ekran.h"
#include <QMouseEvent>
#include <QPainter>

extern int action;
extern int slider;
Ekran::Ekran(QWidget *parent)
    : QWidget{parent},
      im(771, 491, QImage::Format_RGB32)
{
    im.fill(0);
}

void Ekran::paintEvent(QPaintEvent *){
    QPainter p(this);
    p.fillRect(0, 0, width(), height(), Qt::green);
    p.drawImage(0, 0, im);
}

bool Ekran::isInside(int x, int y){
    if(x > 0 && y > 0 && x < 771 && y < 491){
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
    this->im = im_2;
    this->x2 = mouse.x();
    this->y2 = mouse.y();
    if(action == 0){
        Ekran::drawLine(this->x1, this->y1, this->x2, this->y2);
    }else if(action == 1){
        r1 = sqrt(pow((x2 - x1),2) + pow((y2 - y1),2));
        Ekran::drawCircle(x1, y1, r1);
    }else if(action == 2){
        r1 = abs(x1 - x2) / 2;
        r2 = abs(y1 - y2) / 2;
        Ekran::drawElipse(x1, y1, r1, r2);
    }else if(action == 3){
        r1 = abs(x1 - x2) / 2;
        r2 = abs(y1 - y2) / 2;
        Ekran::drawShape((x1 + x2)/2, (y1 + y2)/2, slider, r1, r2);
    }

}

void Ekran::mousePressEvent(QMouseEvent *e){
    QPoint mouse = e->pos();
    this->x1 = mouse.x();
    this->y1 = mouse.y();
    this->im_2 = im;
    if(action == 0){
        this->x2 = mouse.x();
        this->y2 = mouse.y();
        Ekran::putPixel(mouse.x(), mouse.y());
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

void Ekran::drawCircle(int x1, int y1, double r1){
    int x;
    double y;

    for(x = 0; x <= sqrt(2)/2 * r1; x++){
        y = sqrt(pow(r1,2) - pow(x, 2));

        Ekran::putPixel(x1 + x, (int)(y1 + y));
        Ekran::putPixel(x1 - x, (int)(y1 + y));
        Ekran::putPixel(x1 + x, (int)(y1 - y));
        Ekran::putPixel(x1 - x, (int)(y1 - y));

        Ekran::putPixel((int)(x1 + y), (int)(y1 + x));
        Ekran::putPixel((int)(x1 + y), (int)(y1 - x));
        Ekran::putPixel((int)(x1 - y), (int)(y1 + x));
        Ekran::putPixel((int)(x1 - y), (int)(y1 - x));
    }
}


void Ekran::drawElipse(int x1, int y1, double r1, double r2){
    double x, y;

    for(float i = 0.0; i <= (M_PI/2); i += 0.0001){
        x = r1 * cos(i);
        y = r2 * sin(i);

        Ekran::putPixel((int)(x1 + x), (int)(y1 + y));
        Ekran::putPixel((int)(x1 - x), (int)(y1 + y));
        Ekran::putPixel((int)(x1 + x), (int)(y1 - y));
        Ekran::putPixel((int)(x1 - x), (int)(y1 - y));
    }
}

void Ekran::drawShape(int x1, int y1, int slider, int r1, int r2){
    double x, y, xPrev, yPrev, degree;

    for(int i = 0; i <= slider; i++){
        degree = (2 * M_PI / slider) * i;
        x = r1 * cos(degree);
        y = r2 * sin(degree);
        if(!i){
           xPrev = x;
           yPrev = y;
        }

        drawLine(x + x1, y + y1, xPrev + x1, yPrev + y1);

        xPrev = x;
        yPrev = y;

    }
}

void Ekran::clear(){
    im.fill(0);
    update();
}
