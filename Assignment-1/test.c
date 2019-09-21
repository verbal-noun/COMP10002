#include <stdio.h>
#include <string.h>

#define MAXLEN 999
// Global variable
int First_command = 0;

void commands(char* line, int *mar, int *wid);
void indenter(int *val);

int main(int argc, char const *argv[])
{


    // Declaring variables
    char *buffer;
    size_t buffer_size = MAXLEN;
    // The delimiters for strtok function
    const char s[] = " \t";
    const char t[] = "\n";
    char* tok;
    // A 2D array to word the word we read in
    char words[1000][MAXLEN];
    char* word;
    int numWords = 0;
    // A variable to assist us printing stuff
    int count = 0, margin = 4, width = 50;

    while (getline(&buffer, &buffer_size, stdin) != EOF)
    {
        //printf("%s", buffer);
        // tokenising the input


        if(buffer[0] == '.') {
            // processs the commands
            commands(buffer, &margin, &width);
        }
        else {
            // Not consecutive commands
            First_command = 0;
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
            
            int first_word = 1;
            for(int i = 0; i < numWords; i ++)
            {
                count = count + strlen(words[i]) + 1;
                // For words line character count more than or equal to 50
                if(strlen(words[i]) >= width) {
                    size_t ln = strlen(words[i]) - 1;
                    if(words[i][ln] == '\n') {
                        words[i][ln] = '\0';
                    }
                    //printf("\n%s\n", words[i]);
                    count = 0;
                    first_word = 1;
                }
            // As long as the line limit is not reached
                else if(count < width) {
                    
                    size_t ln = strlen(words[i]) - 1;
                    if(words[i][ln] == '\n') {
                      words[i][ln] = '\0';
                    }
                    if()
                    printf("%s", words[i]);
                    
                }
            else {
                printf("\n");
                first_word = 1;
                size_t ln = strlen(words[i]) - 1;
                    if(words[i][ln] == '\n') {
                        words[i][ln] = '\0';
                    }
                printf("%s", words[i]);
                count = 0;
                
                }
        }

        // Here, we should have copied all the words into the array words.

        // Lets print out everything in words, for each of our line read

        }
    }


    return 0;
}

void commands(char* line, int *mar, int *wid) {
    if(line[1] == 'w' || line[1] == 'l' || line[1] == 'p' || line[1] == 'b') {
        if (!First_command) {
            First_command = 1;
        }

    }

    if(line[1] == 'b') {
        if (First_command) {
            printf("\n");
        }
    }
    else if(line[1] == 'p') {
        if (First_command) {
            printf("\n\n");
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
            printf("%d", digit);
            num = num * 10 + digit;


        }

        if(line[1] == 'w') {
            *wid = num;
            printf("%d", *wid);
            if (First_command) {
            printf("\n");
            }
        }
        if(line[1] == 'l') {
            *mar = num;
            if (First_command) {
            printf("\n");
            }
        }

    }

}

void indenter(int *val) {

}