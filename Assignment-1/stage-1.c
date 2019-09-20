#include <stdio.h>
#include <string.h>

#define MAXLEN 999

int main(int argc, char const *argv[])
{

    // Very suspicicous... Just use buffer as a char*. Don't declare an array and 'point' b to that array
    //char buffer[MAXLEN];
    char *buffer;
    size_t buffer_size = MAXLEN;
    const char s[10] = " '\t''\n'";
    char* tok;
    // Changed str to 2d array. Maybe 'words' is a more appropriate name
    char words[1000][MAXLEN];
    int numWords = 0;
    int count = 0;
    while (getline(&buffer, &buffer_size, stdin) != EOF)
    {
        //char line[] = "";
        // For every line we read in, lets see what we read in
        // tokenising the input
        tok = strtok(buffer, s);
        printf("%c\n", buffer[0]);
        //For every new line we should reset numWords to 0
        if(buffer[0] == '.') {
            //
        }
        else {
            numWords = 0;
            while (tok != NULL) {
            // Here we have our tokens coming in. Save these words into our array
            strcpy(words[numWords++], tok);

            // Use of strtok
            // go through other tokens
            tok = strtok(NULL, s);
            }
        }
        

        // Here, we should have copied all the words into words.

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