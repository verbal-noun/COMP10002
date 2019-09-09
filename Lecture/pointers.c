#include <stdio.h>

#define N 5
int main(int argc, char const *argv[])
{
	int A[N], *p, i;
	for(i=0; i<N; i++){
		A[i] = i*(i+1)/2;
	}
	
	p = A;
	for(p=A; p<A+N; p++){
		printf("p = %10p, *p = %2d\n", p, *p);
	}
	return 0;
}