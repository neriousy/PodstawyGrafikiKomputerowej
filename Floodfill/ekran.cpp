#include "ekran.h"
#include <QMouseEvent>
#include <QPainter>
#include <QVector>

extern int action;
extern int slider;
extern int sliderB;




QVector<Point> bezier;

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
    if(x >= 0 && y>= 0 && x < 771 && y < 491){
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
    this->im_2 = im;
    im.fill(0);
    for(int i = 0; i < (int)bezier.size(); i++){
        Ekran::putPixel(bezier[i].x, bezier[i].y, 0, 255, 0);
        Ekran::putPixel(bezier[i].x+1, bezier[i].y, 0, 255, 0);
        Ekran::putPixel(bezier[i].x, bezier[i].y+1, 0, 255, 0);
        Ekran::putPixel(bezier[i].x+1, bezier[i].y+1, 0, 255, 0);
    }
    if(bezier.size() > 3){
        if(action == 4){
            Ekran::drawBezier(sliderB);
        }else if(action == 6){
            Ekran::drawBSplit(sliderB);
        }

    }
    update();

}

int Ekran::findPoint(int x, int y){
    float distance;
    int index = 0;
    for(int i = 0; i < (int)bezier.size(); i++){
        if(i == 0){
            distance = sqrt(pow((x - bezier[i].x), 2) + pow((y - bezier[i].y), 2));
        }else{
            if(distance > sqrt(pow((x - bezier[i].x), 2) + pow((y - bezier[i].y), 2))){
                index = i;
                distance = sqrt(pow((x - bezier[i].x), 2) + pow((y - bezier[i].y), 2));
            }
        }
    }

    return index;
}

void Ekran::mouseMoveEvent(QMouseEvent *e){
    QPoint mouse = e->pos();
    this->x2 = mouse.x();
    this->y2 = mouse.y();
    if(action != 4 && action != 5){
        this->im = im_2;
    }
    if(action == 0){
        Ekran::drawLine(this->x1, this->y1, this->x2, this->y2);
    }else if(action == 1){
        r1 = sqrt(pow((x2 - x1),2) + pow((y2 - y1),2));
        Ekran::drawCircle(x1, y1, r1);
    }else if(action == 2){
        this->im_2 = im;
        r1 = abs(x1 - x2) / 2;
        r2 = abs(y1 - y2) / 2;
        Ekran::drawElipse(x1, y1, r1, r2);
    }else if(action == 3){
        this->im_2 = im;
        r1 = abs(x1 - x2) / 2;
        r2 = abs(y1 - y2) / 2;
        Ekran::drawShape((x1 + x2)/2, (y1 + y2)/2, slider, r1, r2);
    }else if(action == 4 || action == 6){
        if(bezier.size()){
            if(e->buttons() == Qt::MiddleButton){
                this->im = im_2;
                int index = Ekran::findPoint(this->x2, this->y2);
                bezier[index].x = mouse.x();
                bezier[index].y = mouse.y();
                Ekran::drawPoints();
                update();
                if(action == 4){
                    Ekran::drawBezier(sliderB);
                }else if(action == 6){
                    Ekran::drawBSplit(sliderB);
                }

            }
        }
    }
}

void Ekran::mousePressEvent(QMouseEvent *e){
    QPoint mouse = e->pos();
    this->x1 = mouse.x();
    this->y1 = mouse.y();

    if(action != 4 && action != 5){
        this->im_2 = this->im;
        this->x2 = mouse.x();
        this->y2 = mouse.y();
    }
    if(action == 0){
        Ekran::putPixel(mouse.x(), mouse.y());
    }else if(action == 4 || action == 6){
        if(e->button() == Qt::LeftButton){
            Point temp;
            temp.x = mouse.x();
            temp.y = mouse.y();
            bezier.push_back(temp);
            qDebug("Added point x: %d y: %d", this->x1, this->y1);
            Ekran::drawPoints();
            if(action == 4){
                Ekran::drawBezier(sliderB);
            }else if(action == 6){
                Ekran::drawBSplit(sliderB);
            }


        }else if(e->button() == Qt::RightButton){
            if(bezier.size()){
                int index = Ekran::findPoint(mouse.x(), mouse.y());
                qDebug("Deleted point x: %d, y: %d", bezier[index].x, bezier[index].y);
                this->im = this->im_2;
                bezier.erase(bezier.begin() + index);
                Ekran::drawPoints();
            }
        }
    }else if(action == 5){
        if(isInside(mouse.x(), mouse.y())){
            QColor old(im.pixel(mouse.x(), mouse.y()));
            Ekran::floodFill(mouse.x(), mouse.y(), old, this->color);
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

void Ekran::drawBezier(int sliderB){

    int segments = ((int)bezier.size() - 1) / 3;
    float t;
    Point P1, P2;
    if(segments){
        im_2 = this->im;
    }
    P1 = bezier[0];
    for(int i = 0; i < segments; i++){
        for(int j = 0; j <= sliderB; j++){
            t = (float) j / (float) sliderB;
            P2.x = pow(1 - t, 3) * bezier[3 * i].x + 3 * pow(1 - t, 2) * t * bezier[3 * i + 1].x + 3 * (1 - t) * pow(t, 2) * bezier[3 * i + 2].x + pow(t, 3) * bezier[3 * i +3].x;
            P2.y = pow(1 - t, 3) * bezier[3 * i].y + 3 * pow(1 - t, 2) * t * bezier[3 * i + 1].y + 3 * (1 - t) * pow(t, 2) * bezier[3 * i + 2].y + pow(t, 3) * bezier[3 * i +3].y;

            Ekran::drawLine(P1.x, P1.y, P2.x, P2.y);

            P1 = P2;
        }
    }
}


void Ekran::drawBSplit(int sliderB){
    float t;
    Point P1, P2;


    for(int i = 3; i < (int)bezier.size(); i++){
        for(int j = 0; j <= sliderB; j++){
            t = (float)j / (float)sliderB;

            P2.x = (-pow(t, 3) + 3 * pow(t, 2) - 3*t + 1) / 6 * bezier[i - 3].x + (3 * pow(t, 3) - 6 * pow(t, 2) + 4) / 6 * bezier[i - 2].x
                    + (-3  * pow(t, 3) + 3 * pow(t, 2) + 3 * t +1) / 6 * bezier[i - 1].x + pow(t ,3) / 6 * bezier[i].x;
            P2.y = (-pow(t, 3) + 3 * pow(t, 2) - 3*t + 1) / 6 * bezier[i - 3].y + (3 * pow(t, 3) - 6 * pow(t, 2) + 4) / 6 * bezier[i - 2].y
                    + (-3  * pow(t, 3) + 3 * pow(t, 2) + 3 * t +1) / 6 * bezier[i - 1].y + pow(t ,3) / 6 * bezier[i].y;
            if(j > 0){
                Ekran::drawLine(P1.x, P1.y, P2.x, P2.y);
            }

            P1 = P2;
        }
    }
}

void Ekran::floodFill(int x, int y, QColor OldColor, QColor NewColor){
    QStack<Point> stack;
    int nr, ng, nb;
    Point P, temp;
    P.x = x;
    P.y = y;

    nr = NewColor.red();
    ng = NewColor.green();
    nb = NewColor.blue();

    if(OldColor == NewColor){
        return;
    }

    stack.push(P);

    while(!stack.empty()){
        P = stack.pop();

        if(im.pixelColor(P.x, P.y) == OldColor){
            Ekran::putPixel(P.x, P.y, nr, ng ,nb);

            if(Ekran::isInside(P.x - 1, P.y) ){
                temp.x = P.x - 1;
                temp.y = P.y;
                stack.push(temp);
            }
            if(Ekran::isInside(P.x + 1, P.y) ){
                temp.x = P.x + 1;
                temp.y = P.y;
                stack.push(temp);
            }
            if(Ekran::isInside(P.x, P.y - 1) ){
                temp.x = P.x;
                temp.y = P.y - 1;
                stack.push(temp);
            }
            if(Ekran::isInside(P.x, P.y + 1) ){
                temp.x = P.x;
                temp.y = P.y + 1;
                stack.push(temp);
            }
        }
    }
}
void Ekran::clear(){
    im.fill(0);
    bezier.clear();
    update();
}


