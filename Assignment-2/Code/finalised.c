#include <stdio.h>
#include <assert.h>
#include <stdlib.h>

typedef struct  node node_t;

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


/******************************************************************************/
/* Function prototypes */
list_t *make_list_empty (void);
int is_list_empty(list_t *list);
void free_list(list_t *list);
list_t *insert_at_foot(list_t *list, data_t value);
void traverseList(list_t *blocks);
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
    printf("%d\n", status);

    /* remember to free memory */
    free_list(blocks);
    free_list(route);
    freeGrid(arr, size);

    

    return 0;
}



/******************************************************************************/

list_t *make_list_empty (void) {
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


list_t *insert_at_foot(list_t *list, data_t value) {
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


void traverseList(list_t *blocks) {
    node_t *temp;
    
    temp = blocks->head;
    while (temp->next != NULL)
    {
        /* code */
        printf("%d \n", temp->data.row);
        temp = temp->next;
    }
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
    blocks = make_list_empty(); 

    while (scanf("[%d,%d]\n", &row, &col) == 2)
    {
        // Taking input until $ sign is reached or end of file. 
       
        coor.col = col;
        coor.row = row;
        blocks = insert_at_foot(blocks, coor);
        arr[row][col] = '#';
    }

    return blocks;
}

void removeBlocks(list_t *blocks, char **arr) {
    node_t *temp;
    
    temp = blocks->head;
    while (1==1)
    {
        // Adding # in the main grid
        arr[temp->data.row][temp->data.col] = ' ';
        temp = temp->next;
        if(temp->next == NULL) {
            arr[temp->data.row][temp->data.col] = ' ';
            break;
        }
    }
}

list_t *readRoute(char **arr) {
    int row = 0, col = 0;
    char c;
    list_t *route;
    
    route = make_list_empty();
    assert(route != NULL);
    
    scanf("%c\n", &c);
    
    if(c == '$') {
        while (scanf("[%d,%d]-> ", &row, &col) == 2) {
            //read in values for the root
            data_t route_coor;
            route_coor.row = row;
            route_coor.col = col;
            route = insert_at_foot(route, route_coor);
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

    printf("==STAGE 0======================================\n");
    printf("The grid has %d rows and %d columns.\n", dim.row, dim.col);
    // Print info about number of blocks
    barrierCount = listItemCount(barrier);
    printf("The grid has %d block(s).\n", barrierCount); 
    printf("The initial cell in the grid is [%d,%d] .\n", start.row, start.col);
    printf("The goal cell in the grid is [%d,%d] .\n", end.row, end.row);

    printf("The proposed route in the grid is:\n");
    routePrinter(path);

}

int listItemCount(list_t *list) {
    int count = 0;
    node_t *temp;
    
    temp = list->head;
    while(1==1)
    {
        // Increment counter for each node in the list
        count++;
        temp = temp->next;
        if(temp->next == NULL) {
            count++;
            break;
        }
    }

    return count;
}

void routePrinter(list_t *path) {
    int count = 0;
    node_t *temp;
    
    temp = path->head;
    while (1==1)
    {
        if(count == 5) {
            printf("\n");
            count = 0;
        }
        printf("[%d,%d]->", temp->data.row, temp->data.col);
        count++; 
        temp = temp->next;
        if(temp->next == NULL) {
            printf("[%d,%d]\n", temp->data.row, temp->data.col);
            break;
        }
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
            return 1;
        }

        if(route->foot->data.row != end.row || route->foot->data.col 
        != end.col) {
            printf("Goal cell in the route is wrong\n");
            return 1;
        }

        // Check for illegal move in the route
        node_t *temp; 
        data_t prev;

        temp = route->head;
        prev.row = temp->data.row;
        prev.col = temp->data.col;

        while(1==1)
        {
            // Check the validity of the current node 
            if(temp->data.row > size.row || temp->data.col > size.col){
                printf("route is outside of the grid.\n"); 
                return -1; 
            }
            
            rowTraverse = temp->data.row - prev.row;
            //printf("%d ", rowTraverse);
            if(rowTraverse > 1 || rowTraverse < -1 ) {
                printf("route makes an illegal row move\n");
                return -1;
            }

            colTraverse = temp->data.col - prev.col;
            if(colTraverse > 1 || colTraverse < -1) {
                printf("route makes an illegal col move\n");
                return -1;
            }

            prev.row = temp->data.row;
            prev.col = temp->data.col;
            temp = temp->next;
            
            if(temp->next == NULL) {
                rowTraverse = temp->data.row - prev.row;
                //printf("%d ", rowTraverse);
                if(rowTraverse > 1 || rowTraverse < -1 ) {
                    printf("route makes an illegal row move\n");
                    return -1;
                }

                colTraverse = temp->data.col - prev.col;
                if(colTraverse > 1 || colTraverse < -1) {
                    printf("route makes an illegal col move\n");
                    return -1;
                }
                break;
            } 
        }

        // Check if a block is present in the route 
         temp = route->head;

        while(1==1)
        {
            // Check for blocks 
            row = temp->data.row;
            col = temp->data.col;
            if(arr[row][col] == '#') {
                printf("There is a block in the route path\n");
                return  1;
            }
            temp = temp->next;
            if(temp->next == NULL) {
    
                break;
            }
        }
    printf("The route is valid!\n");
    return 0;
}   