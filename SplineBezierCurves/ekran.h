#ifndef EKRAN_H
#define EKRAN_H

#include <QWidget>
#include <QVector>
#include <QStack>
#include <QColor>

struct Point{
    int x, y;
};

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
    void drawBezier(int n);
    void clear();
    bool isInside(int x, int y);
    void drawPoints();
    void drawBSplit(int sliderB);
protected:
    void paintEvent(QPaintEvent *);
    void mouseMoveEvent(QMouseEvent *);
    void mousePressEvent(QMouseEvent *);
   // void mouseReleaseEvent(QMouseEvent *);
    void putPixel(int x, int y, int r = 255, int g = 255, int b = 255);

    int findPoint(int x, int y);


signals:

};

#endif // EKRAN_H
