#include <stdio.h>
#include<string.h>


#define YES 1
#define NO 0
#define DEFAULTMARGIN 50
#define DEFAULT INDENT 4

int get_line(char line[]);
char process_line(char line[]);
void commands(char* line, int *mar, int *wid, int *command);

int main()
{   
    char arr[999]; 
    int end = 0;
    while(end != EOF){
        end = get_line(arr);
        
        // If the line contains a command
        if(arr[0] == '.') 
        {
            //commands(arr, );
        }
        // else proceed towards printing the line
        else
        {

        }
    };
}

int get_line(char line[]) {
    int c, len = 0;
    while((c = getchar()) != EOF && c != '\n') {
        line[len] = c;
        len++;
    }
    line[len] = '\0';

    if(c == EOF) {
        return EOF;
    }
    return 0;
}


void commands(char* line, int *mar, int *wid, int *command) {
    
    
    if(line[1] == 'b') {
        if (*command) {
            printf("\n");
            *command = NO;
        }
    }
    else if(line[1] == 'p') {
        if (*command) {
            printf("\n");
            printf("\n");
            *command = NO;
        }
    }
    else {
        // A variable for loops
        int i = 0;
        int num = 0, digit;

        // For 999 characters the formatter can only be upto 3 digits
        for (i = 0; i < 3; i++)
        {
            if(!isdigit(line[i+3])){
                break;
            }
            /* code */
            digit = line[i+3] - '0';
            num = num * 10 + digit;


        }

        if(line[1] == 'w') {
            *wid = num;
            if (*command) {
            printf("\n");
            printf("\n");
            *command = NO;
            }
        }
        if(line[1] == 'l') {
            *mar = num;
            if (*command) {
            printf("\n");
            printf("\n");
            *command = NO;
            }
        }

    }

}