#include <stdio.h>
#include <string.h>
#include <ctype.h>

void make_center(char *str, int *margin, int *width);
void indenter(int *val);

int main(int argc, char const *argv[])
{
    char text[] = "hello  there   people";
    int margin = 4, width = 50;

    make_center(text, &margin, &width);   
    return 0;
}

void make_center(char *str, int *margin, int *width) {
    int i, x, string_len, limit = 0;
    int **mar = &margin;
    for(i = 0; i < strlen(str); ++i) {
        if(!isspace(str[i]) || (i > 0 && !isspace(str[i-1])))
        str[x++] = str[i];
    }
    str[x] = '\0';
    string_len = strlen(str);
    if(*(width - string_len) % 2 == 0) {
        limit = *width - string_len;
    } else {
        limit = (*width - string_len) + 1;
    }
    indenter(*mar);
    for(i = 0; i < limit; i++) {
        printf(" ");
    }
    printf("%s\n", str);

}

void indenter(int *val) {
    // A variable for loops
    int i = 0;
    for (i = 0; i < *val; i++)
    {
        printf(" ");
    }
    
}
