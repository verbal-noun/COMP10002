#include <stdio.h>

int main(int argc, char const *argv[])
{
	int num;
	int p50 = 0, p20 = 0, p10 = 0, p2 = 0, p = 0;

	// Input amount from 1-99c
	printf("Enter the amount of money: ");
	scanf("%d", &num);
	printf("\n");

	// Separate it into different coins 
	while( num >= 0) {
		if(num >= 50) {
			num -= 50;
			p50++;
		} else if (num >= 20){
			num -= 20;
			p20++;		
		} else if (num >= 10) {
			num -= 10;
			p10++;
		} else if (num >= 2) {
			num -= 2;
			p2++;
		} else {
			num--;
			p++;
		}
	}
	// Print number of each coin 
	printf("50c = %d, 20c= %d, 10c = %d, 2c = %d, 1c = %d\n", p50, p20, p10, p2, p);
	return 0;
}