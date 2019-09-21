#include <stdio.h>
#include <string.h>

#define MAXLEN 999

// int commands(char* line);

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
    int count = 0, margin = 4, width = 50;
    while (getline(&buffer, &buffer_size, stdin) != EOF)
    {
        
        // tokenising the input
       
               
        if(buffer[0] == '.') {
            // processs the commands
        }
        else {
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
        }
        
        // Here, we should have copied all the words into the array words.

        // Lets print out everything in words, for each of our line read
        
        for(int i = 0; i < numWords; i ++){
            count = count + strlen(words[i]) + 1;
            // For words line character count more than or equal to 50
            if(strlen(words[i]) >= width) {
                printf("\n%s\n", words[i]);
                count = 0;
            }
            // As long as the line limit is not reached 
            else if(count <= width) {
                printf("%s ", words[i]);
            } 
            else {
                printf("\n");
                count = 0;
            }
            
        } 
    }


    return 0;
}

/*
int commands(char* line) {

}
*/