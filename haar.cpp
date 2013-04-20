#include "haar.h"
#include <algorithm>
#include <cmath>
#include <iostream>

using namespace std;

/**Cette methode realise la transformation de Haar d'un vecteur de taille N
* on admet que que N=2^j;
*/

DHT::DHT(){
    //Initialization des vecteurs
    A = H = P = NULL;
}

void DHT::haar_vector_transform(double *vect)
{
    //{8,4,1,3 }
    double *y = new double[N];
    int taille = N;
    /*on calcule la moyenne et 2 terms consecutifs, donc N/2 terms, apres reaplique l'ogorithm sur ces N/2 terms
     * jousqu'a il  nous ne reste q'une moyenne,et des ecarts ( details),
     * a chaque iteration N!=1, vect = y[0 -->N/2] */
    while(taille>1){
        /*Pour N = 2^j composantes il existe N/2 moyennes, et on le reduit a chaque iteration*/
        taille = taille/2;
        /*Dans cette boucle on calule la moyenne de 2 coeff voisins, ainsi que leur difference*/
        for(int i = 0; i<taille;i++){
            y[i] = (vect[2*i]+vect[2*i+1])/2; // moyennes
            y[taille+i] = (vect[2*i]-vect[2*i+1])/2; // differences
        }
        copy(y,y+taille,vect);
    } 
    copy(y,y+N,vect);
    delete [] y;
}

void DHT::inverse_haar_vector_transform(double *vect){

    /* y contient le resiltat de la transortmation inverse;
     * alors que vect est un vecteur temporaire*/
    double *y = new double[N];
    int taille = 1;

    while(taille <N){

        /*Dans cette boucle on calule la moyenne de 2 coeff voisins, ainsi que leur difference*/
        for(int i = 0; i<taille;i++){
            y[2*i] = (vect[i]+vect[i+taille]); // moyennes
            y[2*i+1] = (vect[i]-vect[i+taille]); // differences

        }
        taille = taille*2;
        copy(y,y+taille,vect);
    }
     copy(y,y+N,vect);
     delete [] y;
}

void DHT::haar_matrix_transform(double **A){

    double **B = new double*[N];

    /*Transformation sur les lignes*/
    for(int i = 0;i<N;i++) {
        haar_vector_transform(A[i]);
    }
    /*Transformation sur les colones lignes*/
    for(int i = 0;i<N;i++) {
        B[i] = new double[N];
        for( int j = 0;j<N;j++){
            B[i][j] = A[j][i];
        }
        haar_vector_transform(B[i]);
    }

    for(int i = 0;i<N;i++) {
        for( int j = 0;j<N;j++){
            A[j][i] = B[i][j];
        }
        delete [] B[i];
    }
}

void DHT::inverse_haar_matrix_transform(double **A){

    double **B = new double*[N];

    /*Transformation inverse sur les colones lignes*/
    for(int i = 0;i<N;i++) {
        B[i] = new double[N];
        for( int j = 0;j<N;j++){
            B[i][j] = A[j][i];
        }
       inverse_haar_vector_transform(B[i]);
    }

    for(int i = 0;i<N;i++) {
        for( int j = 0;j<N;j++){
            A[i][j] = B[j][i];
        }
    }

   /* Transformation sur les lignes*/
    for(int i = 0;i<N;i++) {
        inverse_haar_vector_transform(A[i]);
        delete [] B[i];
    }
}

bool DHT::saveCompressedImage(QString path){

    getCompressedImage()->save(path);
    return true;
}

bool DHT::computeDHT(){
    if (A == NULL) return false;

    H = new double*[N];

    for(int i=0;i<N;i++){
        H[i] = new double[N];
        copy(A[i],A[i]+N,H[i]);
    }

    haar_matrix_transform(H);
    return true;
}

bool DHT::computeIDHT(int s){

    if (H == NULL) return false;

    P = new double*[N];

    for( int i=0;i<N;i++){
        P[i] = new double[N];
        copy(H[i],H[i]+N,P[i]);
    }

    for( int i=0;i<N;i++){
        for(int j=0;j<N;j++){
            if(P[i][j]*P[i][j]<s/5) P[i][j]=0;
        }
    }

    inverse_haar_matrix_transform(P);


    return true;

}

bool DHT::setImage(QImage InputImage){

    if(InputImage.isNull()) return false;

    int taille = 0;

    if (InputImage.width() <= InputImage.width()) {
        taille = InputImage.width();
    } else taille = InputImage.height();

    //verification si puissance de 2;
    if( taille & (taille - 1) && taille!=0) {
        this->N = taille;
    } else {
        int tmp = 1;
        while(tmp<taille) tmp<<=1;
        this->N = tmp;
    }

    if (A == NULL){
        A = new double*[N];
    }

    for( int i=0; i<N; i++) {
       A[i] = new double[N];
       for( int j=0; j<N; j++){
            A[i][j] =  qGray(InputImage.pixel(i,j));
        }
    }

    return true;
}

QImage* DHT::getCompressedImage(){

    QImage *OutputImage = new QImage(N, N, QImage::Format_RGB888);

    if (P == NULL) return OutputImage;

    for(int i=0; i<N; i++) {
       for(int j=0; j<N; j++){
          OutputImage->setPixel(i,j, qRgb((int)P[i][j],(int)P[i][j],(int)P[i][j]));
        }
    }
    return OutputImage;
}

