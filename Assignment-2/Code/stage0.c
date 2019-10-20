#include <stdio.h>
#include <assert.h>
#include <stdlib.h>


#define INVALID -1 
#define BLOCKED 2
#define TRUE 1
#define FALSE 0
#define BLOCK "#"
#define ROUTE "*"
#define INPUT "$"

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
};


typedef struct
{
    /* Linked list for a block cell */
    node_t *head;
    node_t *foot;
} list_t;


/******************************************************************************/
/* Function prototypes */
list_t *makeEmptyList (void);
int is_list_empty(list_t *list);
void freeList(list_t *list);
list_t *insertHead(list_t *list, data_t value);
list_t *insertFoot(list_t *list, data_t value);
char **createGrid(data_t *size, data_t *init, data_t *end);
list_t *readBlocks(char **arr); 
void updateBlocks(list_t *blocks, char **arr);
list_t *readRoute(char **arr);
void freeGrid(char **arr, data_t size);
void gridInfoPrinter(data_t dim, data_t start, data_t end, list_t *barrier, 
    list_t *path);
int listItemCount(list_t *list);
void routePrinter(list_t *path);
int routeValidator(char **arr, data_t size, data_t start, data_t end, 
    list_t *route);
node_t *blockFinder(char **arr, list_t *route);
void routeFixer(char **arr, data_t size_t, list_t *route);
void traverseGrid(char **arr, node_t *cell, list_t *route, data_t dim);

/******************************************************************************/


int main(int argc, char const *argv[])
{   
    data_t size, start, goal;
    int status = 0; // Initial value needs to be fixed 

    // Creating a 2D to hold the grid 
    char **arr;
    arr = createGrid(&size, &start, &goal);

    
    // Creating the block cells
    list_t *blocks;
    blocks = readBlocks(arr);
    
    // Input the route 
    list_t *route;
    route = readRoute(arr);
    
    
    
    gridInfoPrinter(size, start, goal, blocks, route);
    status = routeValidator(arr, size, start, goal, route);
    //printf("%d\n", status);
    if(status == BLOCKED) {
        // call fixer algorithm
    }

    /* remember to free memory */
    freeList(blocks);
    freeList(route);
    freeGrid(arr, size);

    

    return 0;
}


/******************************************************************************/

list_t *makeEmptyList (void) {
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

/*
    A function to make insertion at the linked list's head 
*/

list_t *insertHead(list_t *list, data_t value) {
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

list_t *insertFoot(list_t *list, data_t value) {
    node_t *new;
    new = (node_t*)malloc(sizeof(*new));
    assert(new != NULL && list != NULL);
    new->data = value;
    new->next = NULL;
    if(list->foot == NULL) 
    {
        // This is a first insertion in the list 
        list->head = list->foot = new;
    }
    else
    {
        /* Items exists beforehand in the list */
        list->foot->next = new;
        list->foot = new;
    }
    
    return list;
}

char **createGrid(data_t *size, data_t *init, data_t *end) {
    int row = 0, col = 0;
    int i = 0, j =0;
    int irow = 0, icol = 0;
    int grow = 0, gcol = 0;
    char **arr;

    // Take input of the dimension
    scanf("%dx%d\n", &row, &col);
    size->row = row;
    size->col = col;

    arr = (char**)malloc(row * sizeof(char*));
    assert(arr != NULL);
    for(i=0; i < row; i++)
    {
        arr[i] = (char*)malloc(col * sizeof(char*));
        assert(arr[i] != NULL);
    }    

    // Filling up the space 
    for(i=0; i <row; i++) 
    {
        for(j=0;j<col;j++) 
        {
            arr[i][j] = ' ';
        }
    }

    // Inputting coordinates of I and G
    scanf("[%d,%d]\n", &irow, &icol);
    init->row = irow;
    init->col = icol;
    scanf("[%d,%d]\n", &grow, &gcol);
    end->row = grow;
    end->col = gcol;

    // Identify I and G in the grid 
    arr[irow][icol] = 'I';
    arr[grow][gcol] = 'G';

    return arr;
}

list_t *readBlocks(char **arr) {
    int row = 0, col = 0;
    data_t coor;

    list_t *blocks;
    blocks = makeEmptyList(); 

    while (scanf("[%d,%d]\n", &row, &col) == 2)
    {
        // Taking input until $ sign is reached or end of file. 
       
        coor.col = col;
        coor.row = row;
        blocks = insertFoot(blocks, coor);
        arr[row][col] = '#';
    }

    return blocks;
}

void removeBlocks(list_t *blocks, char **arr) {
    node_t *temp;
    
    temp = blocks->head;
    while (temp != NULL)
    {
        // Adding # in the main grid
        arr[temp->data.row][temp->data.col] = ' ';
        temp = temp->next;
    }
}

list_t *readRoute(char **arr) {
    int row = 0, col = 0;
    char c;
    list_t *route;
    
    route = makeEmptyList();
    assert(route != NULL);
    
    scanf("%c\n", &c);
    
    if(c == '$') {
        while (scanf("[%d,%d]-> ", &row, &col) == 2) {
            //read in values for the root
            data_t route_coor;
            route_coor.row = row;
            route_coor.col = col;
            route = insertFoot(route, route_coor);
            if(arr[row][col] == ' ') {
                arr[row][col] = '*';
            }
        }
    }

    return route;
}

void freeGrid(char **arr, data_t size) {
    int i = 0;
    for(i = 0; i < size.row; i++)
    {
        free(arr[i]);
        arr[i] = NULL;
    }
    free(arr);
}

void gridInfoPrinter(data_t dim, data_t start, data_t end, list_t *barrier, 
    list_t *path) {
    
    int barrierCount = 0;

    printf("==STAGE 0=======================================\n");
    printf("The grid has %d rows and %d columns.\n", dim.row, dim.col);
    // Print info about number of blocks
    barrierCount = listItemCount(barrier);
    printf("The grid has %d block(s).\n", barrierCount); 
    printf("The initial cell in the grid is [%d,%d].\n", start.row, start.col);
    printf("The goal cell in the grid is [%d,%d].\n", end.row, end.row);

    printf("The proposed route in the grid is:\n");
    routePrinter(path);

}

int listItemCount(list_t *list) {
    int count = 0;
    node_t *temp;
    
    temp = list->head;
    while(temp != NULL)
    {
        // Increment counter for each node in the list
        count++;
        temp = temp->next;
    }

    return count;
}

void routePrinter(list_t *path) {
    int count = 0;
    node_t *temp;
    
    temp = path->head;
    // Run a loop until the last item in processed 
    while (1==1)
    {
        // Print 5 items maximum if the list
        if(count == 5) {
            printf("\n");
            count = 0;
        }
        printf("[%d,%d]->", temp->data.row, temp->data.col);
        count++; 
        // Point node towards the next item 
        if(temp->next == NULL) {
            printf("[%d,%d]\n", temp->data.row, temp->data.col);
            break;
        }
        temp = temp->next;
    }
}

int routeValidator(char **arr, data_t size, data_t start, data_t end, 
    list_t *route) {

        int rowTraverse = 0;
        int colTraverse = 0;
        int row = 0, col = 0;

        if(route->head->data.row != start.row || route->head->data.col 
        != start.col) {
            printf("Initial cell in the route is wrong\n");
            return INVALID;
        }

        if(route->foot->data.row != end.row || route->foot->data.col 
        != end.col) {
            printf("Goal cell in the route is wrong\n");
            return INVALID;
        }

        // Check for illegal move in the route
        node_t *temp; 
        data_t prev;

        temp = route->head;
        prev.row = temp->data.row;
        prev.col = temp->data.col;

        while(temp != NULL)
        {
            // Check the validity of the current node 
            if(temp->data.row > size.row || temp->data.col > size.col){
                printf("route is outside of the grid.\n"); 
                return INVALID; 
            }
            
            rowTraverse = temp->data.row - prev.row;
            //printf("%d ", rowTraverse);
            if(rowTraverse > 1 || rowTraverse < -1 ) {
                printf("route makes an illegal row move\n");
                return INVALID;
            }

            colTraverse = temp->data.col - prev.col;
            if(colTraverse > 1 || colTraverse < -1) {
                printf("route makes an illegal col move\n");
                return INVALID;
            }

            prev.row = temp->data.row;
            prev.col = temp->data.col;
            temp = temp->next;
            
        }

        // Check if a block is present in the route 
        temp = route->head;

        while(temp != NULL)
        {
            // Check for blocks 
            row = temp->data.row;
            col = temp->data.col;
            if(arr[row][col] == '#') {
                printf("There is a block in the route path\n");
                return  BLOCKED;
            }
            temp = temp->next;

        }
    printf("The route is valid!\n");
    return TRUE;
}   

void routeFixer(char **arr, data_t size, list_t *route) {

    node_t *broken_segment;

    // Pass route into blockFinder function and return block coordinate
    broken_segment = blockFinder(arr, route);
    if(!broken_segment) {
        // routeFixer function called without any blocks in the route => error 
        exit(EXIT_FAILURE);
    }

    //  Pass broken segment into traverseGrid function and create a traversal 
    traverseGrid(arr, broken_segment, route, size);
    // Pass created stack to pathBuilder function and update path.  
}

void traverseGrid(char **arr, node_t *cell, list_t *route, data_t dim) {
    list_t *stack;
    stack = makeEmptyList();

    int found = FALSE;
    data_t info;
    int row = 0, col = 0;
    node_t *temp, *finder;

    info.row = cell->data.row;
    info.col = cell->data.col;
    info.counter = 0;
    stack = insertHead(stack, info);

    temp = stack->head;
    finder = cell->next;

    while (temp!=NULL) {
        row = temp->data.row;
        col = temp->data.col;

        
        // Check up
        if(row - 1 >= 0) {
            if(arr[row-1][col] != '#') {
                info.row = row - 1;
                info.col = col;
                info.counter = temp->data.counter + 1;
                stack = insertHead(stack, info);
            }

            // Check if new cell is part of the route 
            while(finder!=NULL) {
                if(row-1 == finder->data.row && col == finder->data.col) {
                    found = TRUE;
                    break;
                }

                finder = finder->next;
            } 
        }
        // Check down 
        if(row+1 <= dim.row) {
            if(arr[row+1][col] != '#') {
                info.row = row + 1;
                info.col = col;
                info.counter = temp->data.counter + 1;
                stack = insertHead(stack, info);
            }

            // Check if new cell is part of the route 
            while(finder!=NULL) {
                if(row+1 == finder->data.row && col == finder->data.col) {
                    found = TRUE;
                    break;
                }

                finder = finder->next;
            }  
        }
        // Check left 
        if(col-1 >= 0) {
            if(arr[row][col-1] != '#') {
                info.row = row;
                info.col = col - 1;
                info.counter = temp->data.counter + 1;
                stack = insertHead(stack, info);
            }
            // Check if new cell is part of the route 
            while(finder!=NULL) {
                if(row == finder->data.row && col-1 == finder->data.col) {
                    found = TRUE;
                    break;
                }

                finder = finder->next;
            } 
        }
        //Check right
        if(col+1 <= dim.col) {
            if(arr[row][col+1] != '#') {
                info.row = row;
                info.col = col+1;
                info.counter = temp->data.counter + 1;
                stack = insertHead(stack, info);
            }
            // Check if new cell is part of the route 
            while(finder!=NULL) {
                if(row == finder->data.row && col+1 == finder->data.col) {
                    found = TRUE;
                    break;
                }

                finder = finder->next;
            } 
        }
        
        temp = temp->next;
        if(found) break;
    }

    if(found) {
        // Call pathBuilder function  

    }
    

}

node_t *blockFinder(char **arr, list_t *route) {
    
    node_t *temp;
    int row = 0, col = 0;
    assert(route != NULL && route->head != NULL);

    temp = route->head;
    while(temp != NULL) {
        if(temp->next != NULL) {
            row = temp->next->data.row;
            col = temp->next->data.col;
        }

        if(arr[row][col] == '#') {
            return temp;
        }

        temp = temp->next;
    }

    return FALSE;
}