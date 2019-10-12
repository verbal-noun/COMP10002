#include<assert.h>
#include<stdio.h>
#include<stdlib.h>

typedef struct  node node_t;

typedef struct
{
    /* data */
    int val;
} data_t;

struct node
{
    /* data */
    data_t data;
    node_t *next;
};

typedef struct
{
    /* data */
    node_t *head;
    node_t *foot;

} list_t;

/*
    A function to convert a linked list empty 
*/
list_t 
*make_list_empty (void) {
    list_t *list;
    list = (list_t*)malloc(sizeof(*list));
    assert(list!= NULL);
    list->head = list->foot = NULL;
    return list;
}

/* 
    A function to create an empty list which will be used as a handle in the 
    calling function. 
*/
int is_list_empty(list_t *list) {
    assert(list != NULL);
    return list->head == NULL;
}

/*
    A function to free the memory of a malloc call 
*/
void free_list(list_t *list) {
    node_t *curr, *prev;
    assert(list != NULL);
    curr = list -> head;
    while (curr)
    {
        /* code */
        prev = curr;
        curr = curr -> next;
        free(prev);
    }
    free(list);
};


/*
    A function to make insertion at the linked list's head 
*/

list_t *insert_at_head(list_t *list, data_t value) {
    node_t *new;
    new = (node_t*)malloc(sizeof(*new));
    assert(new != NULL && list != NULL);
    new->data = value;
    new->next = list->head;
    list->head = new;
    if (list->foot == NULL)
    {
        /* code */
        list->foot = new;
    }

    return list;
}

/* 
    A function to insert item at the foot of the linked list 
*/

list_t *insert_at_foot(list_t *list, data_t value) {
    node_t *new;
    new = (node_t*)malloc(sizeof(*new));
    assert(new != NULL && list != NULL);
    new->data = value;
    new->next = NULL;
    if(list->foot NULL) 
    {
        // This is a first insertion in the list 
        list->foot = new;
    }
    else
    {
        /* Items exists beforehand in the list */
        list->foot->next = new;
        list->foot = new;
    }
    
    return list;
}

/* 
    A function to read data at the head
*/
data_t get_head(list_t *list) {
    assert(list != NULL && list->head != NULL);
    return list->head->data;
}


/*
    A function to consume the data at the head the move the linked list 
    forward 
*/
list_t *get_foot(list_t *list) {
    node_t *oldhead;
    assert(list != NULL && list->head != NULL);
    oldhead = list -> head;
    list->head = list->head->next;
    if(list->head == NULL)
    {
        // Only item in the list got deleted
        list->foot = NULL;
    }
    
    free(oldhead);
    return list;
}
