#include<cmath>
#include<algorithm>
#include<iostream>
using namespace std;

/**Cette methode realise la transformation de Haar d'un vecteur de taille N
* on admet que que N=2^j;
*/
double *haar_vector_transform(double *x, int N)
{
    double *vect = new double[N], *y = new double[N];

    copy(x,x+N,vect);
    /*on calcule la moyenne et 2 terms consecutifs, donc N/2 terms, apres reaplique l'ogorithm sur ces N/2 terms
     * jousqu'a il  nous ne reste q'une moyenne,et des ecarts ( details),
     * a chaque iteration N!=1, vect = y[0 -->N/2] */

    while(N>1){

        /*Pour N = 2^j composantes il existe N/2 moyennes, et on le reduit a chaque iteration*/
        N = N/2;

        /*Dans cette boucle on calule la moyenne de 2 coeff voisins, ainsi que leur difference*/
        for(int i = 0; i<N;i++){
            y[i] = (vect[2*i]+vect[2*i+1])/2; // moyennes
            y[N+i] = (vect[2*i]-vect[2*i+1])/2; // differences
        }
        copy(y,y+N,vect);
    }
    delete [] vect;
    return y;
}

double *inverse_haar_vector_transform(double *x, int N){

    /* y contient le resiltat de la transortmation inverse;
     * alors que vect est un vecteur temporaire*/
    double *vect =new double[N],*y = new double[N];
    int taille = 1;

    copy(x,x+N,vect);
    while(taille <N){

        /*Dans cette boucle on calule la moyenne de 2 coeff voisins, ainsi que leur difference*/
        for(int i = 0; i<taille;i++){
            y[2*i] = (vect[i]+vect[i+taille]); // moyennes
            y[2*i+1] = (vect[i]-vect[i+taille]); // differences

        }
        taille = taille*2;
        copy(y,y+taille,vect);
    }
    delete [] vect;
    return y;
}

double **haar_matrix_transform(double **M, const int N){

    double **A=new double*[N], **B = new double*[N];

    /*Transformation sur les lignes*/
    for(int i = 0;i<N;i++) {
        A[i] = haar_vector_transform(M[i] ,N);
    }
    /*Transformation sur les colones lignes*/
    for(int i = 0;i<N;i++) {
        B[i] = new double[N];
        for( int j = 0;j<N;j++){
            B[i][j] = A[j][i];
        }
        B[i] = haar_vector_transform(B[i] ,N);
    }

    for(int i = 0;i<N;i++) {
        for( int j = 0;j<N;j++){
            A[j][i] = B[i][j];
        }
        delete [] B[i];
    }

    return A;
}

double **inverse_haar_matrix_transform(double **M, int N){

    double **A=new double*[N], **B = new double*[N];

    /*Transformation inverse sur les colones lignes*/
    for(int i = 0;i<N;i++) {
        B[i] = new double[N];
        for( int j = 0;j<N;j++){
            B[i][j] = M[j][i];
        }

        B[i] = inverse_haar_vector_transform(B[i] ,N);
    }

    for(int i = 0;i<N;i++) {
        A[i] = new double[N];
        for( int j = 0;j<N;j++){
            A[i][j] = B[j][i];
        }
    }

   /* Transformation sur les lignes*/
    for(int i = 0;i<N;i++) {
        A[i] = inverse_haar_vector_transform(A[i] ,N);
        delete [] B[i];

    }
    return A;
}
