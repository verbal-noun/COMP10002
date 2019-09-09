#include <stdio.h>

int main(int argc, char const *argv[])
{
	int num, copy, mod, rev = 0;
	printf("Enter a number: ");
	scanf("%d", &num);
	
	if (num < 0) {
		printf("Output: False\n");
		return 0;
	}

	copy = num;
	while (copy != 0)
	{
		mod = copy % 10;
		rev = rev * 10 + mod;
		copy = copy / 10;
	}
	
	if (num == rev) {
		printf("Output: True\n");
	} else {
		printf("Output: False\n");
	}
	
	return 0;
}