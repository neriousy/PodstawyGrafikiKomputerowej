#include "ekran.h"
#include <QMouseEvent>
#include <QPainter>
#include <QVector>
#include <algorithm>
#include <QFile>
#include <QMessageBox>
#include <QString>




extern int options[3];
extern float sliders[3];

Ekran::func Ekran::m_func[5] = {
    &Ekran::normal,
    &Ekran::darken,
    &Ekran::lighten,
    &Ekran::difference,
    &Ekran::multiply
};

Ekran::Ekran(QWidget *parent)
    : QWidget{parent},
      im(800, 600, QImage::Format_RGB32)
{
    im.fill(255);
    im_bgc = new QImage(800, 600, QImage::Format_RGB32);
    im_bgc->fill(0xffffff);
    im_2 = new QImage(":/images/images/1.jpg");
    *im_2 = im_2->scaled(800, 600, Qt::KeepAspectRatio);
    im_3 = new QImage(":/images/images/2.jpg");
    *im_3 = im_3->scaled(800, 600, Qt::KeepAspectRatio);
    im_4 = new QImage(":/images/images/3.jpg");
    *im_4 = im_4->scaled(800, 600, Qt::KeepAspectRatio);
    update();
    alphaBlend();
}

Ekran::~Ekran(){
    delete this->im_2;
    delete this->im_3;
    delete this->im_4;
    delete this->im_bgc;
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

color Ekran::normal(color background, color source, float slider){
    color output;
    output.r = slider * source.r + (1 - slider) * background.r;
    output.g = slider * source.g + (1 - slider) * background.g;
    output.b = slider * source.b + (1 - slider) * background.b;

    return output;
}

color Ekran::darken(color background, color source, float slider){
    color output;
    output.r = slider * (background.r > source.r ? source.r : background.r) + (1 - slider) * background.r;
    output.g = slider * (background.g > source.g ? source.g : background.g) + (1 - slider) * background.g;
    output.b = slider * (background.b > source.b ? source.b : background.b) + (1 - slider) * background.b;

    return output;
}

color Ekran::lighten(color background, color source, float slider){
    color output;
    output.r = slider *(background.r < source.r ? source.r : background.r) + (1 - slider) * background.r;
    output.g = slider *(background.g < source.g ? source.g : background.g) + (1 - slider) * background.g;
    output.b = slider *(background.b < source.b ? source.b : background.b) + (1 - slider) * background.b;

    return output;
}

color Ekran::difference(color background, color source, float slider){
    color output;
    output.r = slider * std::abs(background.r - source.r) + (1 - slider) * background.r;
    output.g = slider * std::abs(background.g - source.g) + (1 - slider) * background.g;
    output.b = slider * std::abs(background.b - source.b) + (1 - slider) * background.b;

    return output;
}

color Ekran::multiply(color background, color source, float slider){
    color output;
    output.r = ((background.r * source.r) >> 8) + (1 - slider) * background.r;
    output.g = ((background.g * source.g) >> 8) + (1 - slider) * background.g;
    output.b = ((background.b * source.b) >> 8) + (1 - slider) * background.b;

    return output;
}


void Ekran::alphaBlend(){
    color output;
    color source, background;
        for(int y = 0; y < 600; y++){
            uchar* pix = this->im_bgc->scanLine(y);
            uchar* pix_2 = this->im_2->scanLine(y);
            uchar* pix_3 = this->im_3->scanLine(y);
            uchar* pix_4 = this->im_4->scanLine(y);
            for(int x = 0; x < 800; x++){
                background.r = pix[4 * x + 2];
                background.g = pix[4 * x + 1];
                background.b = pix[4 * x];

                source.r = pix_2[4 * x + 2];
                source.g = pix_2[4 * x + 1];
                source.b = pix_2[4 * x];

                output = (this->*m_func[options[0]])(background, source, sliders[0]);


                background = output;
                source.r = pix_3[4 * x + 2];
                source.g = pix_3[4 * x + 1];
                source.b = pix_3[4 * x];

                output = (this->*m_func[options[1]])(background, source, sliders[1]);

                background = output;
                source.r = pix_4[4 * x + 2];
                source.g = pix_4[4 * x + 1];
                source.b = pix_4[4 * x];

                output = (this->*m_func[options[2]])(background, source, sliders[2]);

                Ekran::putPixel(x, y, output.r, output.g, output.b);
            }
        }
  }

