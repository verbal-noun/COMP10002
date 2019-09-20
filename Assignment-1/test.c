#include <stdio.h>
#include <string.h> 

#define MAXLEN 999
#define LIMIT 50

int getlines(char line[], int limit);

int main(int argc, char const *argv[])
{
    char str[999];
    char ch;
    while((ch = getchar()) != EOF) {
        getlines(str, LIMIT);
        puts(str);
    }
    
    
    return 0;
}


int getlines(char line[], int limit)
{
    int c, len = 0;
    while((c = getchar()) != EOF && c != '\n' && len < limit) {
        line[len] = c;
        len++;
    }
    line[len] = '\0';
    if(c == EOF) {
        return EOF;
    }

    return 0;
}