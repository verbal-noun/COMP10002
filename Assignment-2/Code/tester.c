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

int main(int argc, char const *argv[])
{
    int row = 0, col = 0;
    
    char **arr;
    list_t *list;
    list = (list_t*)malloc(sizeof(*list));
    assert(list!= NULL);
    list->head = list->foot = NULL;

    data_t info = {0,0,0};
    info.col, info.row = 1;
    insert_at_foot(list, info);
    info.col, info.row = 2;
    insert_at_foot(list, info);

    
    printf("%p\n", list->foot->prev);
    printf("%p\n", list->head);
    return 0;
}
