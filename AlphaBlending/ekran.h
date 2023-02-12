#ifndef EKRAN_H
#define EKRAN_H

#include <QWidget>
#include <QVector>
#include <QStack>
#include <QColor>

struct color{
    int r, g, b;
};

class Ekran : public QWidget
{
    Q_OBJECT
public:
    typedef color(Ekran::*func)(color, color, float);
    static func m_func[5];

    QImage im;
    QImage *im_2, *im_3, *im_4, *im_bgc;
    explicit Ekran(QWidget *parent = nullptr);
    void drawLine(int x1, int y1, int x2, int y2);
    bool isInside(int x, int y);
    color normal(color background, color source, float slider);
    color darken(color background, color source, float slider);
    color lighten(color background, color source, float slider);
    color difference(color background, color source, float slider);
    color multiply(color background, color source, float slider);
    void alphaBlend();
    ~Ekran();
protected:
    void paintEvent(QPaintEvent *);
    void putPixel(int x, int y, int r = 255, int g = 255, int b = 255);




signals:

};

#endif // EKRAN_H
