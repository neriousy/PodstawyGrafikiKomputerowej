#ifndef EKRAN_2_H
#define EKRAN_2_H

#include <QWidget>
#include <QVector>
#include <QStack>
#include <QColor>


class ekran_2 : public QWidget
{
    Q_OBJECT
public:
    QImage im, im_2;
    explicit ekran_2(QWidget *parent = nullptr);
    double r1, r2;
    int x1, x2, y1, y2;
    void drawLine(int x1, int y1, int x2, int y2);
    void clear();
    bool isInside(int x, int y);
    void drawPoints();
    int findPoint(int x, int y);
     void putPixel(int x, int y, int r = 255, int g = 255, int b = 255);
protected:
    void paintEvent(QPaintEvent *);
    void mousePressEvent(QMouseEvent *);
    void mouseMoveEvent(QMouseEvent *);




signals:

};

#endif // EKRAN_2_H
