#include <stdio.h>
#include <string.h>

int
main(int argc, char* argv[]){
    char* buffer;
    char words[100][100];
    size_t buffersize = 100;
    char* token;
    int numwords = 0;

    while(getline(&buffer, &buffersize, stdin) != EOF){
        numwords = 0;
        token = strtok(buffer, " ");
        while(token != NULL){
            //printf("%s ", token);
            strcpy(words[numwords], token);
            numwords ++;
            token = strtok(NULL, " ");
        }

        for(int i = 0; i < numwords; i++){
            printf("%s ", words[i]);
        }
       
    }

    return 0;
}