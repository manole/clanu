#ifndef HAAR_H
#define HAAR_H

#include <QImage>

class DHT {
private:
    /***************************************************************************************/
    int N;           // le taille de l'image

    double tau;

    double **A;      // Matrice qui contient l'image originale;

    double **H;      // Matrice qui contient la tranormée de Haar de l'image A;

    double **P;      // Matrice qui contient la l'image compressé;


    /*****************************************************************************************/

    /*Les methodes suivantes sont utilisées pour réaliser la THD et la TIHD*/

    void haar_vector_transform(double *vect);

    void inverse_haar_vector_transform(double *vect);

    void haar_matrix_transform(double **M);

    void inverse_haar_matrix_transform(double **M);


public:
    DHT();

    bool setImage(QImage img);

    bool computeDHT();

    bool computeIDHT(int s);

    bool saveCompressedImage(QString path);

    QImage* getCompressedImage();
};


#endif // HAAR_H
