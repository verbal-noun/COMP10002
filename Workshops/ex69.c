#include <stdio.h>
#include <stdlib.h>

#define NUM_COINS 6       /* we have 6 different coins      */
#define MIN_AMOUNT 1      /* the minimal amount of cents    */ 
#define MAX_AMOUNT 999    /* the maximal amount of cents    */


void print_change(int cents); 
int round_to_5(int cents); 
void try_a_coin (int *pcents, int coin); 

/* the main() is fully written for you, but there is a question:
   - How can we intergrate the "if" in lines 21-23 into the loop's guard?
*/ 
int main( int argc, char *argv[] ) {
	int amount;
	printf ("Enter amount in cents: ");
	scanf("%d", &amount);
	try_a_coin(&amount);
	/*
	while ( scanf("%d", &amount)==1 ) {
		if ( !(amount >= MIN_AMOUNT && amount <= MAX_AMOUNT) ) {
			break;
		} else {
			printf("\nThe amount is %d\n", amount);
			printf("The change is :\n");   
			print_change(amount);
	} 
	*/ 	 
	return 0;
}

/* returns a value rounded off to the nearest multiple of five */
int round_to_5(int cents) {
	return (cents+2)/5*5;
	
    /*-----------------  here is another way:
	int remainder= cents % 5;
	if ( remainder < 2 ) {
		return cents - remainder;
	} else {
		return (cents - remainder) + 5;
	}
    --------------------------*/ 
}

/* function to print change using coin valued “coin”
   and reduce the amount (*pcents) accordingly  */
/* NOT YET DONE - FIX ME! */ 
void try_a_coin (int *pcents, int coin) {
	/* say, if *pcents=45 and coin=20 we need:
		- print out: 20c, 20c,       
		- reduce *pcents to 5 
	*/
	int num;
	while(*pcents >= coin) {
		*pcents -= coin;
		num++;
	}

	printf("Number of %2d cent coins required: ", coin);
  	for(int i=0; i < num; i++){
  		printf("%dc ", coin);
  	}
}


/* print out changes required for the amount "cents" of cents */
/* NOT YET DONE - FIX ME! */ 
void print_change(int cents) {
	int n= NUM_COINS;
	
