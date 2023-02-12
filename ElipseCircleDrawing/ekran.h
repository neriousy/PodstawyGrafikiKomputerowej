#ifndef EKRAN_H
#define EKRAN_H

#include <QWidget>

class Ekran : public QWidget
{
    Q_OBJECT
public:
    QImage im, im_2;
    explicit Ekran(QWidget *parent = nullptr);
    double r1, r2;
    int x1, x2, y1, y2;
    void drawLine(int x1, int y1, int x2, int y2);
    void drawCircle(int x1, int y1, double r1);
    void drawElipse(int x1, int y1, double r1, double r2);
    void drawShape(int x1, int y1, int slider, int r1, int r2);
    void clear();
protected:
    void paintEvent(QPaintEvent *);
    void mouseMoveEvent(QMouseEvent *);
    void mousePressEvent(QMouseEvent *);
   // void mouseReleaseEvent(QMouseEvent *);
    void putPixel(int x, int y);
    bool isInside(int x, int y);


signals:

};

#endif // EKRAN_H
