#include<cmath>
#include<algorithm>
#include<iostream>
using namespace std;

/**Cette methode realise la transformation de Haar d'un vecteur de taille N
* on admet que que N=2^j;
*/
void haar_vector_transform(double *vect, int N)
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

void inverse_haar_vector_transform(double *vect, int N){

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

void haar_matrix_transform(double **A, const int N){

    double **B = new double*[N];

    /*Transformation sur les lignes*/
    for(int i = 0;i<N;i++) {
        haar_vector_transform(A[i] ,N);
    }
    /*Transformation sur les colones lignes*/
    for(int i = 0;i<N;i++) {
        B[i] = new double[N];
        for( int j = 0;j<N;j++){
            B[i][j] = A[j][i];
        }
        haar_vector_transform(B[i] ,N);
    }

    for(int i = 0;i<N;i++) {
        for( int j = 0;j<N;j++){
            A[j][i] = B[i][j];
        }
        delete [] B[i];
    }
}

void inverse_haar_matrix_transform(double **A, int N){

    double **B = new double*[N];

    /*Transformation inverse sur les colones lignes*/
    for(int i = 0;i<N;i++) {
        B[i] = new double[N];
        for( int j = 0;j<N;j++){
            B[i][j] = A[j][i];
        }
       inverse_haar_vector_transform(B[i] ,N);
    }

    for(int i = 0;i<N;i++) {
        for( int j = 0;j<N;j++){
            A[i][j] = B[j][i];
        }
    }

   /* Transformation sur les lignes*/
    for(int i = 0;i<N;i++) {
        inverse_haar_vector_transform(A[i] ,N);
        delete [] B[i];
    }
}
