#include <QApplication>
#include "mainwindow.h"
#include "ekran.h"
#include "ekran_2.h"


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    return a.exec();
}
