#include <stdio.h>


int getline(char line[], int limit)
{
    int c, len = 0;
    while(c = getchar() != EOF && c != '\n' && len < limit) {
        line[len] = c;
        len++;
    }
    line[len] = '\0';
    if(c == EOF) {
        return EOF;
    }

    return 0;
}