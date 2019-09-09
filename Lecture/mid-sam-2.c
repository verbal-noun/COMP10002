#include <stdio.h>
#include <stdlib.h>

#define MAX 20

int main(int argc, char const *argv[])
{
	int value, i, j, k, space;
	while(scanf("%d", &value) != 1) {
		printf("Invalid Value\n");
		return 0;
	}	
		if(value > MAX || value < 1) {
			printf("The value must be between 1 and 20\n");
			return 0;
		}

		space = value;
		for(i=0; i<value; i++) {
			for(j=space*2-1; j > 0; j--) {
				printf(" ");
			}

			for(k=0; k<(i*2)-1; k++){
				printf("* ");
			}
			space--;
			printf("\n");
		}
		
	return 0;
}