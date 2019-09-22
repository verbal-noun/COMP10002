#include <stdio.h>
#include <string.h>
#include<ctype.h>

#define MAXLEN 999
#define YES 1
#define NO 0


void commands(char* line, int *mar, int *wid, int *command);
void indenter(int *val);

int main(int argc, char const *argv[])
{


    // Declaring variables
    char *buffer;
    size_t buffer_size = MAXLEN;
    // The delimiters for strtok function
    char s[]=" \t\r\n\v\f";;
    char* tok;
    // A 2D array to word the word we read in
    char words[1000][MAXLEN];
    int numWords = 0;
    // A variable to check first command or not
    int first_command = YES;
    // A variable for loops
    int i = 0;
    
    // A variable to assist us printing stuff
    int count = 0, margin = 4, width = 50;

    while (getline(&buffer, &buffer_size, stdin) != EOF)
    {
        //printf("%s", buffer);
        // tokenising the input


        if(buffer[0] == '.') {
            // processs the commands
            commands(buffer, &margin, &width, &first_command);
            count = 0;
        }
        else {
            if(first_command == NO) {
                first_command = YES;
            }
            // Not consecutive commands
            tok = strtok(buffer, s);
            //For every new line we should reset numWords to 0
            numWords = 0;
            while (tok != NULL) {
            // Here we have our tokens coming in. Save these words into our array
            strcpy(words[numWords++], tok);

            // Use of strtok
            // go through other tokens
            tok = strtok(NULL, s);
            }
            
            
            for(i = 0; i < numWords; i ++)
            {
                //if(count == 0) printf("zero\n");
                count = count + strlen(words[i]) + 1;
                
                // For words line character count more than or equal to 50
                if(strlen(words[i]) >= width) {
                    printf("\n");
                    indenter(&margin);
                    printf("%s\n", words[i]);
                   
                
                }
            // As long as the line limit is not reached
                //|| (count-1 == width)
                else if((count) <= width ){
                    // Print this condition everything this is reached

                    if(((strlen(words[i]) + 1) - count) == 0) {
                        indenter(&margin);
                        printf("%s", words[i]);
                        // Since no space is printed reset count
                        count--;
                    } else
                    {
                       printf(" %s", words[i]);
                       
                    }
                                        
                }
                else {
                    printf("\n");
                    count = strlen(words[i]);
                    indenter(&margin);
                    printf("%s", words[i]);
                    
                   
                }
        }

        // Here, we should have copied all the words into the array words.

        // Lets print out everything in words, for each of our line read

        }
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

void indenter(int *val) {
    // A variable for loops
    int i = 0;
    for (i = 0; i < *val; i++)
    {
        printf(" ");
    }
    
}