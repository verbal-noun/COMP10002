#include <stdio.h>

int func2(char A[]);

int main(int argc, char const *argv[])
{
	printf("Done\n");
	func2((char*)"Hello World");
	printf("Done\n");
	return 0;

}

int func2(char A[]) {
	A[0] = '0';
	return 0;
}