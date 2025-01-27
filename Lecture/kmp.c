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

    int i = 0; // index for text
    int j = 0; // index for pattern 

    while (i < j) {
        if (pat[j] == txt[i]) {
            j++;
            i++;
        }
        
        if (j==patlen) {
            printf("Pattern found at index %d ", i - j);
            j = pat[j - i];
        }
        // Mismatch after j matches 
        else if ( i < txtlen && pat[j] != txt[i]) {
            /* code */
            if (j != 0) {
                j = pat[j-1];
            }
            else {
                i += 1;
            }
    } 

}
