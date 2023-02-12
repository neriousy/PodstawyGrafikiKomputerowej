#include "ekran.h"
#include <QMouseEvent>
#include <QPainter>
#include <QVector>
#include <algorithm>
#include <QFile>
#include <QMessageBox>
#include <QString>


int action = 0;

Ekran::func Ekran::m_func[2] = {
    &Ekran::erozja,
    &Ekran::dylatacja,
};

Ekran::Ekran(QWidget *parent)
    : QWidget{parent},
      im(800, 600, QImage::Format_RGB32)
{
    im.fill(255);
    im_temp = new QImage(":/images/images/1.jpg");
    *im_temp = im_temp->scaled(800, 600, Qt::KeepAspectRatio);
    im = *(im_temp);
    toMonochrome();
    update();
}

Ekran::~Ekran(){
    delete im_temp;
}
void Ekran::paintEvent(QPaintEvent *){
    QPainter p(this);
    p.fillRect(0, 0, 800, 600, Qt::white);
    p.drawImage(0, 0, im);
}

bool Ekran::isInside(int x, int y){
    if(x >= 0 && y >= 0 && x < 800 && y < 600){
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


void Ekran::toMonochrome(){
    for(int y = 0; y < 600; y++){
        uchar *pix = im.scanLine(y);
        for(int x = 0; x < 800; x++){
            if(pix[4 * x + 2] + pix[4 * x + 1 ] + pix[4 * x] < 382){
                putPixel(x, y, 255, 255, 255);
            }else{
                putPixel(x, y, 0 ,0 ,0);
            }
        }
    }
}

void Ekran::operacja(int a){
    im_2 = im;
    for(int y = 0; y < 600; y++){
        for(int x = 0; x < 800; x++){
            (this->*m_func[a])(x, y);
        }
    }
}

void Ekran::dylatacja(int x, int y){

    if(isInside(x, y - 1)){
        uchar *pix = im_2.scanLine(y - 1);
        if(pix[4 * x] == 255){
            putPixel(x, y, 255, 255, 255);
            return;
        }
    }

    if(isInside(x - 1, y)){
        uchar *pix = im_2.scanLine(y);
        if(pix[4 * (x - 1)] == 255){
            putPixel(x, y, 255, 255, 255);
            return;
        }
    }

    if(isInside(x + 1, y)){

        uchar *pix = im_2.scanLine(y);
        if(pix[4 * (x + 1)] == 255){
            putPixel(x, y, 255, 255, 255);

            return;
        }
    }


    if(isInside(x , y)){

        uchar *pix = im_2.scanLine(y);
        if(pix[4 * x] == 255){
            putPixel(x, y, 255, 255, 255);

            return;
        }
    }


    if(isInside(x, y + 1)){
        uchar *pix = im_2.scanLine(y + 1);
        if(pix[4 * x] == 255){
            putPixel(x, y, 255, 255, 255);
            return;
        }
    }
    putPixel(x, y, 0, 0,  0);

}

void Ekran::erozja(int x, int y){

        if(isInside(x, y - 1)){
            uchar *pix = im_2.scanLine(y - 1);
            if(pix[4 * x] == 0){
                putPixel(x, y, 0, 0, 0);
                return;
            }
        }

        if(isInside(x - 1, y)){
            uchar *pix = im_2.scanLine(y);
            if(pix[4 * (x - 1)] == 0){
                putPixel(x, y, 0, 0, 0);
                return;
            }
        }

        if(isInside(x + 1, y)){

            uchar *pix = im_2.scanLine(y);
            if(pix[4 * (x + 1)] == 0){
                putPixel(x, y, 0, 0, 0);

                return;
            }
        }

        if(isInside(x, y + 1)){
            uchar *pix = im_2.scanLine(y + 1);
            if(pix[4 * x] == 0){
                putPixel(x, y, 0, 0, 0);
                return;
            }
        }

        if(isInside(x, y)){
            uchar *pix = im_2.scanLine(y);
            if(pix[4 * x] == 0){
                putPixel(x, y, 0, 0, 0);
                return;
            }
        }

        putPixel(x, y, 255, 255,  255);
}

void Ekran::otwarcie(){
    Ekran::operacja(0);
    Ekran::operacja(1);
}

void Ekran::domkniecie(){
    Ekran::operacja(1);
    Ekran::operacja(0);
}
