#include <stdio.h>
#include <string.h>
#include <assert.h>
#include <stdlib.h>

#define MAX 100

void kmp_search(char *pat, char *txt);

int main(int argc, char const *argv[])
{
    int F[MAX], n;
    char *str;
    int pos = 2, cnd = 0;

    str = argv[1];
    if (!str) {
        printf("Usage: %s string\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    n = strlen(str);
    F[0] = -1;
    F[1] = 0;
    while (pos < n)
    {
        if( F[pos-1] == F[cnd]) {
            cnd += 1;
            F[pos] = cnd;
            pos += 1;
        } 
        else if (cnd > 0) {
            cnd = F[cnd];
        }
        else {
            F[pos] = 0;
            pos += 1;
        }
        
    }
    
    return 0;
}


void kmp_search(char *pat, char *txt) {
    int txtlen = strlen(txt);
    int patlen = strlen(pat);

    // Creating an array to contain the longest prefix suffix values for pattern
    int arr[patlen];

    // Calculate the failure function for pattern  
    //

    
}