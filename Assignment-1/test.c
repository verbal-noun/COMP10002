#include <stdio.h>
#include <string.h>

#define MAXLEN 999

int main(int argc, char const *argv[])
{

    // Very suspicicous... Just use buffer as a char*. Don't declare an array and 'point' b to that array
    //char buffer[MAXLEN];
    char *buffer;
    size_t buffer_size = MAXLEN;
    const char s[10] = ", -";
    char* tok;
    // Changed str to 2d array. Maybe 'words' is a more appropriate name
    char words[1000][MAXLEN];
    int numWords = 0;
    while (getline(&buffer, &buffer_size, stdin) != EOF)
    {
        //char line[] = "";
        // For every line we read in, lets see what we read in
        printf("Line read: %s ", buffer);

        // tokenising the input
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
        
        // Here, we should have copied all the words into words.

        // Lets print out everything in words, for each of our line read
        printf("Tokenised line: ");
        for(int i = 0; i < numWords; i ++){
            printf("%s ", words[i]);
        }

        printf("\n");
    }


    return 0;
}