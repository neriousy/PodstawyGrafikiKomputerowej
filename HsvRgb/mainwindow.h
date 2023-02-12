#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void SlidersRGB();
    void SlidersHSV();

private slots:

    void on_Red_sliderMoved(int position);
    void on_Green_sliderMoved(int position);
    void on_Blue_sliderMoved(int position);
    void on_h_sliderMoved(int position);
    void on_s_sliderMoved(int position);
    void on_v_sliderMoved(int position);

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
