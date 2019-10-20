#include <stdio.h>
#include <assert.h>
#include <stdlib.h>

char *createGrid(char *arr); 

typedef struct  node node_t;

// A structure to hold block coordinate
typedef struct 
{
    /* data */
    int row;
    int col;
} data_t;

struct node 
{
    /* data */
    data_t data;
    node_t *next;
};


typedef struct
{
    /* Linked list for a block cell */
    node_t *head;
    node_t *foot;
} list_t;

list_t 
*makeEmptyList (void) {
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
void freeList(list_t *list) {
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


list_t *insertFoot(list_t *list, data_t value) {
    node_t *new;
    new = (node_t*)malloc(sizeof(*new));
    assert(new != NULL && list != NULL);
    new->data = value;
    new->next = NULL;
    if(list->foot == NULL) 
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



int main(int argc, char const *argv[])
{   

    // Creating a grid with I and G coordinates 
    int row = 0, col = 0, i;
    int irow = 0, icol = 0;
    int grow = 0, gcol = 0;
    //char *arr;

    scanf("%dx%d\n", &row, &col);
    //arr =  (char*)malloc(row * sizeof(char));
    char *arr[row];
    for(i=0; i < row; i++)
    {
        arr[i] = (char*)malloc(col * sizeof(char));
    }    

    scanf("[%d,%d]\n", &irow, &icol);
    scanf("[%d,%d]\n", &grow, &gcol);

    arr[irow][icol] = 'I';
    arr[grow][gcol] = 'G';

    /*
    // Creating a linked list for the block cells 
    row = 0, col = 0;
    list_t *blocks;
    blocks = make_list_empty();
    */
    /*
    while (scanf("[%d,%d]\n", &row, &col) == 1)
    {
        //
        data_t coor;
        coor.row = row;
        coor.col = col;
        blocks = insert_at_foot(blocks, coor);
    }
    */
    //print_list(blocks);


    // Preventing memory leaks 
    // Freeing block cells 
    //free_list(blocks);

    /* remember to free memory */
    for(i = 0; i < row; i++)
    {
        free(arr[i]);
        arr[i] = NULL;
    }
    free(arr);
    
    return 0;
}


/*
char *createGrid(char *arr) 
{
    int row = 0, col = 0;
    int irow = 0, icol = 0;
    int grow = 0, gcol = 0;
    scanf("%dx%d\n", &row, &col);
    
    char *arr[row];
    for(int i=0; i < row; i++)
    {
        arr[i] = (char*)malloc(col * sizeof(char));
    }

    scanf("[%d,%d]\n", &irow, &icol);
    scanf("[%d,%d]\n", &grow, &gcol);

    arr[irow][icol] = 'I';
    arr[grow][gcol] = 'G';

    return arr;
}
*/

/*
    int count = 0; 
    for (int i = 0; i <  row; i++) 
      for (int j = 0; j < col; j++) 
         grid[i][j] = ++count; // Or *(*(arr+i)+j) = ++count 
  
    for (int i = 0; i <  row; i++) 
      for (int j = 0; j < col; j++) 
         printf("%d ", grid[i][j]); 
*/