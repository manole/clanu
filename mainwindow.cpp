#include <QFileDialog>
#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->horizontalSlider->setEnabled(false);

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_actionOpenImage_triggered()
{
    QStringList file =
            QFileDialog::getOpenFileNames(this, tr("Choisissez une image"),"./",tr("Images (*.bmp *.png *.jpg .*jpeg)"));

    if(file.isEmpty()) return;

    QImage InputImage = QImage(file.at(0)); // conversion "string" vers "const char*"
    if (InputImage.isNull()){
       // cout << "Probleme lors de l'ouverture !! fichier pas trouve ou format pas reconnu" << endl;
        return ;
    }
    ui->imageFrame->setPixmap(QPixmap::fromImage(InputImage));

    if(haar.setImage(InputImage)){
        ui->horizontalSlider->setEnabled(true);
        haar.computeDHT();
    }
}

void MainWindow::on_horizontalSlider_sliderMoved(int compression)
{
    haar.computeIDHT(compression);
    ui->percentageLabel->setText(QString::number(compression)+" %");
    ui->imageFrame->setPixmap(QPixmap::fromImage(*haar.getCompressedImage()));

}
