#include <stdio.h>
#include <string.h>

#define MAXLEN 999

int main(int argc, char const *argv[])
{

    
    // Declaring variables
    char *buffer;
    size_t buffer_size = MAXLEN;
    // The delimiters for strtok function
    const char s[10] = " '\t''\n'";
    char* tok;
    // A 2D array to word the word we read in
    char words[1000][MAXLEN];
    int numWords = 0;
    // A variable to assist us printing stuff
    int count = 0;

    while (getline(&buffer, &buffer_size, stdin) != EOF)
    {
        
        // tokenising the input
        tok = strtok(buffer, s);
        printf("%c\n", buffer[0]);
        
        if(buffer[0] == '.') {
            //
        }
        else {
            //For every new line we should reset numWords to 0
            numWords = 0;
            while (tok != NULL) {
            // Here we have our tokens coming in. Save these words into our array
            strcpy(words[numWords++], tok);

            // Use of strtok
            // go through other tokens
            tok = strtok(NULL, s);
            }
        }
        
        // Here, we should have copied all the words into the array words.

        // Lets print out everything in words, for each of our line read
        /*
        for(int i = 0; i < numWords; i ++){
            count = count + strlen(words[i]) + 1;
            if(count < 51) {
                printf("%s ", words[i]);
            } else {
                printf("\n");
                count = 0;
            }
            
        } */
    }


    return 0;
}