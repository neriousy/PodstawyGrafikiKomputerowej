#ifndef EKRAN_H
#define EKRAN_H

#include <QWidget>
#include <QVector>
#include <QStack>
#include <QColor>

struct Point{
    int x, y;
};

struct Point3D{
    float x, y, z;
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
    bool isInside(int x, int y);
    void drawPoints(QVector<Point> Points);
    void transform();
protected:
    void paintEvent(QPaintEvent *);
    void putPixel(int x, int y, int r = 255, int g = 255, int b = 255);



signals:

};

#endif // EKRAN_H
