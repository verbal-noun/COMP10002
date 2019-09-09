#include <stdio.h>

int main()
{
	float x = 1.0;
	while(x <= 2.0) {
		x += 0.1;
		printf("%0.10f\n", x);
	}

	return 0;
}