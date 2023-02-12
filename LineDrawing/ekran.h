#ifndef EKRAN_H
#define EKRAN_H

#include <QWidget>

class Ekran : public QWidget
{
    Q_OBJECT
public:
    QImage im, im_2;
    explicit Ekran(QWidget *parent = nullptr);
    int x1, x2, y1, y2;
    void drawLine(int x1, int y1, int x2, int y2);
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
