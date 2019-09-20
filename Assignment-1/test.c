#include <stdio.h> 
#include <string.h> 
  
// Driver function 
int main() 
{ 
    // Declaration of string 
    char gfg[100] = " Geeks - for -   ,geeks, - Contribute"; 
    char *str[999];
    int i = 0;
    // Declaration of delimiter 
    const char s[10] = ", -"; 
    char* tok; 
  
    // Use of strtok 
    // get first token 
    tok = strtok(gfg, s); 
  
    // Checks for delimeter 
    while (tok != NULL) { 
        str[i++] = tok;
        // Use of strtok 
        // go through other tokens 
        tok = strtok(NULL, s); 
    } 

    for(int j=0; j <i; j++) {
        printf("%s\n", str[j]);
    }
  
    return (0); 
} 