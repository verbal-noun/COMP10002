#include <stdio.h>
#include<stdlib.h>
#include <assert.h>

typedef struct node node_t;

typedef struct
{
    /* data */
    int row;
    int col;
    int counter;
} data_t;

struct node 
{
    /* data */
    data_t data;
    node_t *next;
    node_t *prev;
};

typedef struct
{
    /* Linked list for a block cell */
    node_t *head;
    node_t *foot;
} list_t;

list_t *insert_at_foot(list_t *list, data_t value) {
    node_t *new;
    new = (node_t*)malloc(sizeof(*new));
    assert(new != NULL && list != NULL);
    new->data = value;
    new->next = NULL;
    new->prev = NULL;

    if(list->foot == NULL) 
    {
        // This is a first insertion in the list 
        list->head = list->foot = new;
    }
    else
    {
        /* Items exists beforehand in the list */
        list->foot->next = new;
        new->prev = list->foot;
        list->foot = new;

    }
    
    return list;
}

int read_line(char line[]) {
    // variables to control text inflow 
    int ch, len = 0;

    while((ch = getchar()) != EOF && ch != '\n') {
        line[len] = ch;
        len++;
    }
    line[len] = '\0';

    if(ch == EOF) {
        return EOF;
    }
    return 0;
}

int main(int argc, char const *argv[])
{
    char ch[100][100];
    int i = 0;
    while(read_line(ch) != EOF) {
        
        printf("%s\n", ch[i]);
        i++;
    }
    return 0;
}

