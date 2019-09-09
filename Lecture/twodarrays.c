#include <stdio.h>

#define ROWS 5
#define COLS 10

void assign_2d(int A[][COLS], int nrows);
void print_2d(int A[][COLS], int nrows);

int
main(int argc, char *argv[]) {
	int Y[ROWS][COLS];
	assign_2d(Y, ROWS);
	print_2d(Y, ROWS);
	return 0;
}

void
assign_2d(int A[][COLS], int nrows) {
	int i, j;
	for (i=0; i<nrows; i++) {
		for (j=0; j<COLS; j++) {
			A[i][j] = 100 + 10*i + j;
		}
	}
}

void
print_2d(int A[][COLS], int nrows) {
	int i, j;
	for (i=0; i<nrows; i++) {
		for (j=0; j<COLS; j++) {
			printf("%4d ", A[i][j]);
		}
		printf("\n");
	}
}