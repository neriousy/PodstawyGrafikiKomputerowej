#include <QApplication>
#include "ekran.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    Ekran w;
    w.show();

    w.drawLine(212,109,212,389);
    w.drawLine(35,258,389 ,258);
    w.drawLine(143,388,290,113);
    w.drawLine(276,385,144,122);
    w.drawLine(77,390,348,118);
    w.drawLine(383,163,38,349);
    w.drawLine(66,174,350,333);
    w.drawLine(90,133,334,379);
    return a.exec();
}
