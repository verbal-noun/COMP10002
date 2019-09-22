#include <stdio.h>
#include<string.h>

int get_line(char line[]);

int main()
{   
    char arr[999]; 
    int end = 0;
    while(end != EOF){
        end = get_line(arr);
    };
}

int get_line(char line[]) {
    int c, len = 0;
    while((c = getchar()) != EOF && c != '\n') {
        line[len] = c;
        len++;
    }
    line[len] = '\0';
    printf("%s\n", line);
    if(c == EOF) {
        return EOF;
    }
    return 0;
}