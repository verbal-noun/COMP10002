#include <stdio.h>

// THIS IS A FAULTY PROGRAM FOR MYSELF TO LEARN ## TYPEDEF ## 
// Check out matrixadd.c for correct program 

#define SIZE 50

typedef double vector_t[SIZE];
typedef vector_t sqmatrix_t[SIZE];

void sqmatrix_add1(sqmatrix_t A, sqmatrix_t B, sqmatrix_t C, int n);

int main(int argc, char const *argv[])
{	
	// 2D Matrix addition
	vector_t A, B;
	// This creates a 2D matrix 
	sqmatrix_t C;

	for (int i=0; i<SIZE; i++) {
		A[i] = 0.5*i;
		B[i] = 1.0/(i+1);
	}

	sqmatrix_add1(A, B, C, SIZE);

	// Printing the matrix 
	for (i=0; i<SIZE; i++) {
		for (int j=0; j<SIZE; j++) {
			printf("%6.3f  ", C[i][j]);
		}
		printf("\n");
	}
	return 0;
}

void sqmatrix_add1(sqmatrix_t A, sqmatrix_t B, sqmatrix_t C, int n) {
	int i, j;

	for (i=0; i<n; i++) {
		for (j = 0; j < n; j++)
		{
			C[i][j] = A[i][j] + B[i][j];
		}
	}
}