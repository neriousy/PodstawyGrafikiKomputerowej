#ifndef EKRAN_H
#define EKRAN_H

#include <QWidget>
#include <QPainter>

class ekran : public QWidget
{
    Q_OBJECT
public:

    explicit ekran(QWidget *parent = nullptr);
    QImage im;

    typedef void(ekran::*func)(int, int, int, int, int);
    static func m_func[3];

    void paintEvent(QPaintEvent *);
    bool isInside(int x, int y);
    void putPixel(int x, int y, int r = 255, int g = 255, int b = 255);
    void paintRGB(int color, int action);
    void paintHSV(int color, int action);
    void paintR(int i, int j, int color, int t, int p);
    void paintG(int i, int j, int color, int t, int p);
    void paintB(int i, int j, int color, int t, int p);
    void paintH(int i, int j, int color, int t, int p);
    void paintS(int i, int j, int color, int t, int p);
    void paintV(int i, int j, int color, int t, int p);

    void HSVtoRGB(float h, float s, float v);
    void RBGtoHSV(float r, float g, float b);

signals:

};

#endif // EKRAN_H
