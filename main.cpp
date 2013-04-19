#include <iostream>
#include <haar.h>
#include <algorithm>
#include <QtGui/QImage>
#include <QtGui/QColor>
#include <fstream>

using namespace std;

int main() {

    QImage InputImage = QImage("/home/skynet/Documents/CPP/CLANU/lena.bmp"); // conversion "string" vers "const char*"
    if (InputImage.isNull())
        {
        cout << "Probleme lors de l'ouverture !! fichier pas trouve ou format pas reconnu" << endl;
        return -1;
    }


    int N = InputImage.width();
    double **A = new double*[N];

    QImage *OutputImage = new QImage(N, N, QImage::Format_RGB888);


    int i,j;
    for( i=0; i<N; i++) {
       A[i] = new double[N];
       for( j=0; j<N; j++){
            A[i][j] =  qGray(InputImage.pixel(i,j));
        }
    }

    cout<<"Taille de l'image:"<<N<<endl;

    double **H = haar_matrix_transform(A,N);


    for( i=0; i<N; i++) {
       for( j=0; j<N; j++){
           if(H[i][j]*H[i][j]<15){
               H[i][j] = 0;
           }

        }
    }

    double **P = inverse_haar_matrix_transform(H,N);



    for( i=0; i<N; i++) {
       for( j=0; j<N; j++){
          OutputImage->setPixel(i,j, qRgb((int)P[i][j],(int)P[i][j],(int)P[i][j]));
        }
    }

   OutputImage->save("/home/skynet/Documents/CPP/CLANU/lena_restab.bmp");


    return 0;
}


