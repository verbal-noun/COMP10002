#include <stdio.h>
#include <string.h>
#include <ctype.h>


#define YES 1
#define NO 0
#define DEFAULTWIDTH 50
#define DEFAULTINDENT 4
#define MAXLEN 999

int get_line(char line[]);
char process_line(char line[]);
void commands(char* line, int *mar, int *wid, int *command);
void line_printer(char line[],int *margin, int *width, int *cur_pos, int *first_comm);
void indenter(int *val);

int main()
{   
    char arr[MAXLEN]; 
    // A variable to determine the end of reading
    int end = 0;
    // Variables which help keeping track of words print in line
    int count = 0;
    // Variables to format the ouput 
    int indent = DEFAULTINDENT, width = DEFAULTWIDTH;
    // A variable to check first command or not
    int first_command = YES;
    
    while(end != EOF){
        end = get_line(arr);
        
        // If the line contains a command
        if(arr[0] == '.') 
        {
            commands(arr, &indent, &width, &first_command);
            // Reset line count 
            count = 0;
        }
        // else proceed towards printing the line
        else
        {   
            line_printer(arr, &indent, &width, &count, &first_command);
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

void line_printer(char line[],int *margin, int *width, int *cur_pos, int *first_comm)
{
    char s[]=" \t\r\n\v\f";;
    char* tok;
    char words[MAXLEN][MAXLEN];
    int numWords, i = 0;
    int **mar = &margin;

    if(*first_comm == NO) {
                *first_comm = YES;
            }
    // Not consecutive commands
    tok = strtok(line, s);
    //For every new line we should reset numWords to 0
    numWords = 0;
    while (tok != NULL) 
    {
    // Here we have our tokens coming in. Save these words into our array
    strcpy(words[numWords++], tok);
    // Use of strtok
    // go through other tokens
    tok = strtok(NULL, s);
    }

    for(i = 0; i < numWords; i ++)
    {
        //if(count == 0) printf("zero\n");
        *cur_pos = *cur_pos + strlen(words[i]) + 1;
                
        // For words line character count more than or equal to 50
        if(strlen(words[i]) >= *width) 
        {
            printf("\n");
            indenter(*mar);
            printf("%s\n", words[i]);
            *cur_pos = 0;        
        }
        // As long as the line limit is not reached
        else if((*cur_pos) <= *width )
        {
            // Print this condition everything this is reached
            if(((strlen(words[i]) + 1) - *cur_pos) == 0) 
            {
                indenter(*mar);
                printf("%s", words[i]);
                // Since no space is printed reset count
                *cur_pos = *cur_pos - 1;
            }
            else {
            printf(" %s", words[i]);         
            }                         
        }
        else {
            printf("\n");
            *cur_pos = strlen(words[i]);
            indenter(*mar);
            printf("%s", words[i]);      
            }
    }
}

void indenter(int *val) 
{
    // A variable for loops
    int i = 0;
    for (i = 0; i < *val; i++)
    {
        printf(" ");
    }
    
}