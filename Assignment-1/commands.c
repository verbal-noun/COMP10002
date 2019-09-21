#include <stdio.h>
#include <string.h>

#define MAXLEN 999

// Global variable 
int First_command = 0;

int commands(char* line);


int main(int argc, char const *argv[])
{
    /* code */
    return 0;
}


int commands(char* line) {
    if(line[1] == 'w' || line[1] == 'l' || line[1] == 'p' || line[1] == 'b') {
        if (!First_command) {
            First_command = 1;
        }
         
    }

    if(line[1] == 'b') {
        if (First_command) {
            printf("/n");
        } 
    } 
    else if(line[1] == 'p') {
        if (First_command) {
            printf("/n/n");
        } 
    }
    else {
        int num = 0, digit;
        // For 999 characters the formatter can only be upto 3 digits 
        for (size_t i = 0; i < 3; i++)
        {
            if(line[i+3] == ' '){
                break;
            }
            /* code */
            digit = line[i+3] - '0';
            num = num * 10 + digit;
        }

    }
    
}