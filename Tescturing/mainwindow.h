#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "ekran.h"
#include "ekran_2.h"


namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    void rysuj();
    ~MainWindow();
    Ui::MainWindow *ui;
private slots:

    void on_pushButton_clicked();

private:

};

#endif // MAINWINDOW_H
