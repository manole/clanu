#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtGui/QImage>
#include "haar.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    
private slots:
    void on_actionOpenImage_triggered();

    void on_horizontalSlider_sliderMoved(int position);

private:
    Ui::MainWindow *ui;
    DHT haar;
};

#endif // MAINWINDOW_H
