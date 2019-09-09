#include <stdio.h> 
#include <string.h>
#include <ctype.h>

#define MAXLEN 10
#define MAXWORDS 1000

typedef char words_t[MAXLEN+1];

int get_word(char W[], int limit);

int main(int argc, char const *argv[])
{
    words_t one_word, all_words[MAXWORDS];
    int distinctNum = 0, totWords = 0, i, found;
    while (get_word(one_word, MAXLEN) != EOF) {
        totWords++;
        // Linear search in array of previous words 
        found = 0;
        for (i=0; i<distinctNum && !found; i++) {
            found = (strcmp(one_word, all_words[i]) == 0);
        }

        if(!found && distinctNum < MAXWORDS) {
            strcpy(all_words[distinctNum], one_word);
            distinctNum++;
        }
    }

    return 0;
}


int get_word(char W[],int limit) {
    int c, len = 0;
    // Skipping over any non-alphabets 
    while ((c = getchar())!=EOF && !isalpha(c)) {
        // Do nothing
    }

    if (c == EOF) {
        return 0;
    }
    // First character of new word has been found
    W[len++] = c;
    while (len < limit && (c = getchar()) != EOF && isalpha(c))
    {
        W[len++] = c;
    }
    // Closing of the string 
    W[len] = '\0';
    return 0;
};