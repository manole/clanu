#ifndef HAAR_H
#define HAAR_H

double *haar_vector_transform(int *vect, int N);

double *inverse_haar_vector_transform(double *vect, int N);

double **haar_matrix_transform(double **M, int N);

double **inverse_haar_matrix_transform(double **M, int N);

#endif // HAAR_H
