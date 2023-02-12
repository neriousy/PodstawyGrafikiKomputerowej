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
    typedef void(Ekran::*func)(int, int);
    static func m_func[2];

    QImage im, im_2;
    QImage *im_temp;
    explicit Ekran(QWidget *parent = nullptr);
    void drawLine(int x1, int y1, int x2, int y2);
    bool isInside(int x, int y);
    void toMonochrome();
    void operacja(int a);
    void dylatacja(int x, int y);
    void erozja(int x, int y);
    void otwarcie();
    void domkniecie();
    ~Ekran();
protected:
    void paintEvent(QPaintEvent *);
    void putPixel(int x, int y, int r = 255, int g = 255, int b = 255);




signals:

};

#endif // EKRAN_H
