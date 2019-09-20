#include <stdio.h>
#include <string.h> 

#define MAXLEN 999

int main(int argc, char const *argv[])
{
    char buffer[MAXLEN];
    char *b = buffer; 
    size_t buffer_size = MAXLEN;
    const char s[10] = " '\t'"; 
    char *tok;
    char *str[MAXLEN];
    int i = 0;
    
    while (getline(&b, &buffer_size, stdin) != EOF)
    {
        
        char line[] = "";
    
        // tokenising the input 
        tok = strtok(buffer, s);

        while (tok != NULL) { 
        str[i++] = tok;
        // Use of strtok 
        // go through other tokens 
        
        } 


        for(int j=0; j <i; j++) 
        {
            if(strlen(line) == 0) {
                strcat(line, str[j]);
            } else
            {
                strcat(line, " ");
                strcat(line, str[j]);
            }
        }
        tok = strtok(NULL, s); 
        printf("%s", line);
    }
    
    
    return 0;
}
