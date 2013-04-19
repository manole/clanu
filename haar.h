#ifndef HAAR_H
#define HAAR_H


void haar_vector_transform(double *vect, int N);

void inverse_haar_vector_transform(double *vect, int N);

void haar_matrix_transform(double **M, int N);

void inverse_haar_matrix_transform(double **M, int N);

#endif // HAAR_H
