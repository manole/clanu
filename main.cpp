#include <iostream>
#include <QApplication>
#include <QtGui/QImage>
#include <QtGui/QColor>
#include <mainwindow.h>

using namespace std;

int main(int argc, char *argv[]) {

    QApplication a(argc, argv);
    MainWindow w;
    w.show();


    return  a.exec();
}


