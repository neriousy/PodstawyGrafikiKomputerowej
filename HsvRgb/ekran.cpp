#include "ekran.h"

float R = 0, G = 0, B = 0, H = 0, S = 0, V = 0;

ekran::func ekran::m_func[3] = {
    &ekran::paintR,
    &ekran::paintG,
    &ekran::paintB,
};


ekran::ekran(QWidget *parent)
    : QWidget{parent},
    im(512, 512, QImage::Format_RGB32)
{
    im.fill(0);
}


void ekran::paintEvent(QPaintEvent *){
    QPainter p(this);
    p.fillRect(0, 0, 512, 512, Qt::black);
    p.drawImage(0, 0, im);
}

bool ekran::isInside(int x, int y){
    if(x >= 0 && y>= 0 && x <= 512 && y <= 512){
        return true;
    }
    return false;
}


void ekran::putPixel(int x, int y, int r, int g, int b){
    if(ekran::isInside(x, y)){
        uchar *pix = im.scanLine(y);
        pix[4*x] = b;
        pix[4*x + 1] = g;
        pix[4*x + 2] = r;
        update();
    }
}


void ekran::paintR(int i, int j, int color, int t, int p){
    putPixel(i, j, color, t, p);
    putPixel(i+1, j, color, t, p);
    putPixel(i, j-1, color, t, p);
    putPixel(i+1, j-1, color, t, p);

}

void ekran::paintG(int i, int j, int color, int t, int p){
    putPixel(i, j, t, color, p);
    putPixel(i+1, j, t, color, p);
    putPixel(i, j-1, t, color, p);
    putPixel(i+1, j-1, t, color, p);

}

void ekran::paintB(int i, int j, int color, int t, int p){
    putPixel(i, j, t, p, color);
    putPixel(i+1, j, t, p, color);
    putPixel(i, j-1, t, p, color);
    putPixel(i+1, j-1, t, p, color);
}

void ekran::paintRGB(int color, int a){
    int t = 0, p = 0;
    for(int i = 0 ; i < 512; i += 2){
        for(int j = 511; j >= 0; j -= 2){
            (this->*m_func[a])(i, j, color, t%256, p%256);
            p++;
        }
        t++;
    }
}

void ekran::paintHSV(int color, int a){
    float h = 0, s = 0, v = 0;
    float co_1 = 1. / 512.;
    float co_2 = 360. / 512.;

    if(a == 3){
        h = color;
        for(int i = 0 ; i < 512; i ++){
            for(int j = 511; j >= 0; j --){
                HSVtoRGB(h, s, v);
                putPixel(i, j, R, G , B);
                s += co_1;
            }
            s = 0;
            v += co_1;
        }
    }else if(a == 4){
        s = (float) (color / 100.);
        //qDebug("S: %f", s);
        for(int i = 0 ; i < 512; i ++){
            for(int j = 511; j >= 0; j --){
                HSVtoRGB(h, s, v);
                putPixel(i, j, R, G, B);
                v += co_1;
            }
            v = 0;
            h += co_2;
        }
    }else if(a == 5){
        v = (float) (color / 100.);
        //qDebug("V: %f", v);
        for(int i = 0 ; i < 512; i++){
            for(int j = 511; j >= 0; j --){
                HSVtoRGB(h, s, v);
                putPixel(i, j, R, G, B);
                s += co_1;
            }
            s = 0;
            h += co_2;
        }
    }
}

void ekran::HSVtoRGB(float h, float s, float v){
   float c, x, m, r, g, b;

   c = s * v;
   x = c * (1 - std::abs(fmod(h / 60, 2) - 1));
   m = v - c;

   if(h >= 0 && h < 60){
       r = c;
       g = x;
       b = 0;
   }else if(h >= 60 && h < 120){
       r = x;
       g = c;
       b = 0;
   }else if(h >= 120 && h < 180){
       r = 0;
       g = c;
       b = x;
   }else if(h >= 180 && h < 240){
       r = 0;
       g = x;
       b = c;
   }else if(h >= 240 && h < 300){
       r = x;
       g = 0;
       b = c;
   }else{
       r = c;
       g = 0;
       b = x;
   }



   R = (r + m) * 255;
   G = (g + m) * 255;
   B = (b + m) * 255;

}
void ekran::RBGtoHSV(float r, float g, float b){
    r = r / 255; g = g / 255; b = b / 255;

    float M = ((r > g) && (r > b)) ? r : ((b > g) ? b : g);
    float m = ((r < g) && (r < b)) ? r : ((b < g) ? b : g);
    float C = M - m;

    if(M == m){
        H = 0;
    }else if(M == r){
        H = fmod((60 * ((g - b) / C) + 360), 360.0);
    }else if(M == g){
        H = fmod((60 * ((b - r) / C) + 120), 360.0);
    }else if(M == b){
        H = fmod((60 * ((r - b) / C) + 240), 360.0);
    }

    if(M == 0){
        S = 0;
    }else{
        S = (C / M * 100.0);
    }

    V = M * 100.0;


}


