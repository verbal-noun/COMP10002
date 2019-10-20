#include <stdio.h>
#include <assert.h>
#include <stdlib.h>


#define INVALID -1 
#define BLOCKED 4
#define TRUE 1
#define FALSE 0
#define BLOCK "#"
#define ROUTE "*"
#define INPUT "$"
#define BREAK "------------------------------------------------\n"
#define DIVIDER "================================================"

typedef struct node node_t;

typedef struct
{
    /* data */
    int row;
    int col;
    int counter;
} data_t;

typedef struct 
{
    int row;
    int col;
    int counter;
} traverse_t;

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


/******************************************************************************/
/* Function prototypes */
list_t *make_list_empty (void);
int is_list_empty(list_t *list);
void free_list(list_t *list);
list_t *insert_at_head(list_t *list, data_t value);
list_t *insert_at_foot(list_t *list, data_t value);
char **createGrid(data_t *size, data_t *init, data_t *end);
list_t *readBlocks(char **arr); 
void updateBlocks(char **arr, list_t *route, list_t *blocks, data_t size, 
    data_t start, data_t end);
list_t *readRoute(char **arr);
void freeGrid(char **arr, data_t size);
void gridInfoPrinter(char **arr, data_t dim, data_t start, data_t end, 
    list_t *barrier, list_t *path);
int listItemCount(list_t *list);
void routePrinter(list_t *path);
int routeValidator(char **arr, data_t size, data_t start, data_t end, 
    list_t *route);
node_t *blockFinder(char **arr, list_t *route);
void routeFixer(char **arr, data_t size, data_t start, data_t end, 
    list_t *route, int firstFix);
int traverseGrid(char **arr, node_t *cell, list_t *route, data_t dim);
int checkQueue(int row, int col, list_t *queue);
list_t *pathBuilder(list_t *queue, list_t *route, data_t size);
void updatePath(list_t *route, list_t *new_path, list_t* queue);
void gridVisualizer(char **grid, data_t size);
void gridEmptier(char **arr, data_t dim);
void routeDraw(char **arr, list_t *route);
void removeRoute(char **arr, list_t *route);
void firstAttempt(char **arr, data_t size, data_t start, data_t goal, 
    list_t *route);
int read_line(char line[]);

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
    
    gridInfoPrinter(arr, size, start, goal, blocks, route);
    status = routeValidator(arr, size, start, goal, route);

    printf("==STAGE 1=======================================\n");
    gridVisualizer(arr, size);
    if(status < BLOCKED) {
        return 0;
    }
    if(status == BLOCKED) {
        // call fixer algorithm
        firstAttempt(arr, size, start, goal, route);
    }

    // Have a function to update new blocks
    char line[100];
    int counter = 0;

    while(read_line(line) != EOF) {
        counter++;
        if(line[0] == '$') {
            updateBlocks(arr, route, blocks, size, start, goal);
        }
    }
    // update grid and free old blocks 
    // read in new blocks
    // do routeValidation 

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

list_t *insert_at_head(list_t *list, data_t value) {
    node_t *new;
    new = (node_t*)malloc(sizeof(*new));
    assert(new != NULL && list != NULL);
    new->data = value;
    new->next = NULL;
    new->prev = NULL;

    if(list->head == NULL) 
    {
        // This is a first insertion in the list 
        list->head = list->foot = new;
    }
    else
    {
        /* Items exists beforehand in the list */
        new->next = list->head;
        list->head->prev = new;
        list->head = new;
    }
    
    return list;
}
/*
    A function to make insertion at the linked list's foot 
*/
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

char **createGrid(data_t *size, data_t *init, data_t *end) {
    int row = 0, col = 0;
    int i = 0;
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

    // Filling up the space 
    gridEmptier(arr, *size);

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
        }
    }
    routeDraw(arr, route);

    return route;
}

void routeDraw(char **arr, list_t *route) {
    node_t *temp;

    temp = route->head;
    while(temp != NULL) {
        if(arr[temp->data.row][temp->data.col] == ' ') {
                arr[temp->data.row][temp->data.col] = '*';
        }

        temp = temp->next;
    }
}

void removeRoute(char **arr, list_t *route) {
    node_t *temp;

    temp = route->head;
    while(temp != NULL) {
        if(arr[temp->data.row][temp->data.col] == '*') {
            arr[temp->data.row][temp->data.col] = ' ';            
        }
        temp = temp->next;
    }

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

void gridInfoPrinter(char **arr, data_t dim, data_t start, data_t end, 
    list_t *barrier, list_t *path) {
    
    int barrierCount = 0;
    int status = 0;

    printf("==STAGE 0=======================================\n");
    printf("The grid has %d rows and %d columns.\n", dim.row, dim.col);
    // Print info about number of blocks
    barrierCount = listItemCount(barrier);
    printf("The grid has %d block(s).\n", barrierCount); 
    printf("The initial cell in the grid is [%d,%d].\n", start.row, start.col);
    printf("The goal cell in the grid is [%d,%d].\n", end.row, end.row);

    printf("The proposed route in the grid is:\n");
    routePrinter(path);
    status = routeValidator(arr, dim, start, end, path);
    if(status == BLOCKED) {
        printf("There is a block on this route!\n");
    }
    else {
        printf("The route is valid!\n");
    }
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
        temp = temp->next;
        if(temp->next == NULL) {
            printf("[%d,%d].\n", temp->data.row, temp->data.col);
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
                //printf("There is a block in the route path\n");
                return  BLOCKED;
            }
            temp = temp->next;

        }
    //printf("The route is valid!\n");
    return TRUE;
}   

void routeFixer(char **arr, data_t size, data_t start, data_t end, 
    list_t *route, int firstFix) {

    node_t *broken_segment;
    list_t *new_path;
    int notFixed = FALSE, status = 0;
    new_path = make_list_empty();
    // Pass route into blockFinder function and return block coordinate
    broken_segment = blockFinder(arr, route);
    removeRoute(arr, route);
    if(!broken_segment) {
        // routeFixer function called without any blocks in the route => error 
        exit(EXIT_FAILURE);
    }

    //  Pass broken segment into traverseGrid function and create a traversal
    notFixed = traverseGrid(arr, broken_segment, route, size);
    if(notFixed) {
        // print code cannot be fixed
        
    }
    else {
        status = routeValidator(arr, size, start, end, route);
        if(status == BLOCKED && !firstFix) {
            routeFixer(arr, size, start, end, route, firstFix);
            
        }
        else {
            // return path is fixed.
            routeDraw(arr, route); 
        }
    }

    free_list(new_path);
}

void firstAttempt(char **arr, data_t size, data_t start, data_t goal, 
    list_t *route) {
    int routeFixed = 0;
    // Fix route once 
    routeFixer(arr, size, start, goal, route, 1);
    routeFixed = routeValidator(arr, size, start, goal, route);
    // Visualise the route 
    if(routeFixed == TRUE) {
        printf(BREAK);
        gridVisualizer(arr, size);
        printf(BREAK);
        routePrinter(route);
        printf("The route is valid!\n");
        printf(DIVIDER);
    }
    // Proceed to next stage
    else {
        /*
        gridVisualizer(arr, size);
        printf("==STAGE 2======================================\n");
        routeFixer(arr, size, start, goal, route, 0);
        routeFixed = routeValidator(arr, size, start, goal, route);

        if(routeFixed == TRUE) {
            gridVisualizer(arr, size);
            printf(BREAK);
            routePrinter(route);
            printf("The route is valid!\n");
        }
        else {
            gridVisualizer(arr, size);
            printf("The route cannot be fixed.\n");
        } */
    } 
}

int traverseGrid(char **arr, node_t *cell, list_t *route, data_t dim) {
    list_t *stack, *new_path;
    stack = make_list_empty();
    new_path = make_list_empty();
    int exist = 0;

    int found = FALSE;
    data_t info;
    int row = 0, col = 0;
    node_t *temp, *finder;

    info.row = cell->data.row;
    info.col = cell->data.col;
    info.counter = 0;
    stack = insert_at_foot(stack, info);

    temp = stack->head;
    

    while (temp!=NULL) {
        row = temp->data.row;
        col = temp->data.col;

        
        // Check up
        if(row - 1 >= 0) {
            finder = cell->next;
            // check if that row already exists in the queue 
            exist = checkQueue(row-1, col, stack);

            if(arr[row-1][col] != '#') {
                info.row = row - 1;
                info.col = col;
                info.counter = temp->data.counter + 1;
                if(!exist) stack = insert_at_foot(stack, info);
            }

            // Check if new cell is part of the route 
            while(finder!=NULL && !exist) {
                if(row-1 == finder->data.row && col == finder->data.col && 
                arr[row-1][col] != '#') {
                    found = TRUE;
                    break;
                }

                finder = finder->next;
            } 
        }
        if(found) break;

        // Check down 
        if(row+1 < dim.row) {
            finder = cell->next;
            exist = checkQueue(row+1, col, stack);

            if(arr[row+1][col] != '#') {
                info.row = row + 1;
                info.col = col;
                info.counter = temp->data.counter + 1;
                if(!exist) stack = insert_at_foot(stack, info);
            }

            // Check if new cell is part of the route 
            while(finder!=NULL && !exist) {
                if(row+1 == finder->data.row && col == finder->data.col && 
                arr[row+1][col] != '#') {
                    found = TRUE;
                    break;
                }

                finder = finder->next;
            }  
        }
        if(found) break;

        // Check left 
        if(col-1 >= 0) {
            
            exist = checkQueue(row, col-1, stack);

            if(arr[row][col-1] != '#') {
                info.row = row;
                info.col = col - 1;
                info.counter = temp->data.counter + 1;
               if(!exist) stack = insert_at_foot(stack, info);
            }

            finder = cell->next;
            // Check if new cell is part of the route 
            while(finder!=NULL && !exist) {
                if(row == finder->data.row && col-1 == finder->data.col &&
                arr[row][col-1] != '#') {
                    found = TRUE;
                    break;
                }

                finder = finder->next;
            } 
        }
        if(found) break;

        //Check right
        if(col+1 < dim.col) {
            finder = cell->next;
            exist = checkQueue(row, col+1, stack);

            if(arr[row][col+1] != '#') {
                info.row = row;
                info.col = col+1;
                info.counter = temp->data.counter + 1;
                if(!exist) stack = insert_at_foot(stack, info);
            }
            // Check if new cell is part of the route 
            while(finder!=NULL && !exist) {
                if(row == finder->data.row && col+1 == finder->data.col && 
                arr[row][col+1] != '#') {
                    found = TRUE;
                    break;
                }

                finder = finder->next;
            } 
        }
        
        temp = temp->next;
        if(found) break;
    }
    
    // return value of found

    if(found) {
        new_path = pathBuilder(stack, route, dim);
        // update old route
        updatePath(route, new_path, stack);

        return 0; 
    }
    else return TRUE;

    
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

int checkQueue(int row, int col, list_t *queue) {
    node_t *temp;
    temp = queue->head;

    while(temp != NULL) {
        if(temp->data.row == row && temp->data.col == col) {
            return TRUE;
        }

        temp = temp->next;
    }
    return 0;
}

list_t *pathBuilder(list_t *queue, list_t* route, data_t size) {
    
    char **grid;
    int i = 0, j = 0;
    node_t *temp;
    data_t pos, info;
    list_t *new_path;
    new_path = make_list_empty();
    
    grid = (char**)malloc(size.row * sizeof(char*));
    assert(grid != NULL);
    for(i=0; i < size.row; i++) {
        grid[i] = (char*)malloc(size.col * sizeof(char*));
        assert(grid[i] != NULL);
    }

    for(i=0; i < size.row; i++) {
        for(j = 0; j < size.col; j++) {
            grid[i][j] = -1;
        }
    }

    temp = queue->foot;
    while (temp != NULL)
    {
        /* code */
        grid[temp->data.row][temp->data.col] = temp->data.counter;
        temp = temp->prev;
    }

    pos = queue->foot->data;
    
    while(pos.counter != 1) {

        // Check upper cell 
        if((pos.row-1 >= 0) && grid[pos.row - 1][pos.col] == 
        (pos.counter - 1)) {
            info.row = pos.row -1;
            info.col = pos.col;
            info.counter = pos.counter - 1;
            pos = info;
            new_path = insert_at_head(new_path, info);
        }
        // Check bottom cell
        else if((pos.row + 1 < size.row) && grid[pos.row + 1][pos.col] == 
        (pos.counter - 1)) {
            info.row = pos.row + 1;
            info.col = pos.col;
            info.counter = pos.counter - 1;
            pos = info;
            new_path = insert_at_head(new_path, info);
        }
        // Check cell at the left 
        else if((pos.col -1 >= 0) && grid[pos.row][pos.col - 1] == 
        (pos.counter - 1)) {
            info.row = pos.row;
            info.col = pos.col - 1;
            info.counter = pos.counter - 1;
            pos = info;
            new_path = insert_at_head(new_path, info);
        }
        // Check cell at the right
        else if((pos.col < size.col) && grid[pos.row][pos.col + 1] == 
        (pos.counter - 1)) {
            info.row = pos.row;
            info.col = pos.col + 1;
            info.counter = pos.counter - 1;
            pos = info;
            new_path = insert_at_head(new_path, info);
        }
    } 
    
    return new_path;

    freeGrid(grid, size);     
}

void updatePath(list_t *route, list_t *new_path, list_t* queue) {
    node_t *start, *end, *temp, *prev;
    assert(route && new_path && queue);

    start = NULL;
    end = NULL;
    temp = route->head;

    while(temp != NULL) {
        if((temp->data.row == queue->head->data.row) && (temp->data.col == 
        queue->head->data.col)) {
            start = temp;
        }

        if((temp->data.row == queue->foot->data.row) && (temp->data.col == 
        queue->foot->data.col)) {
            end = temp;
        }
        temp = temp -> next;
        if(start != NULL && end != NULL) break;
    }

    temp = start->next;
    while (temp != end) {
        // Free list
        prev = temp;
        temp = temp -> next;
        free(prev);
    }

    // Update route 
    start->next = new_path->head;
    new_path->foot->prev = start;

    new_path->foot->next = end;
    end->prev = new_path->foot;
}

void gridVisualizer(char **grid, data_t size) {
    int i = 0, j = 0, counter = 0;
    
    printf(" ");
    while(counter < size.col) {
        printf("%d", i);
        counter++;
        i++;
        if(i == 10) {
            i = 0;
        }    
    }
    
    printf("\n");
    counter = 0;

    for(i = 0; i < size.row; i++) {
        printf("%d", counter);
        for(j = 0; j < size.col; j++) {
            printf("%c", grid[i][j]);
        }
        printf("\n");
        counter++;
        if(counter == 10) counter = 0;
    }
}

void gridEmptier(char **arr, data_t dim) {
    
    int i = 0, j = 0;

    for(i=0; i <dim.row; i++) 
    {
        for(j=0;j<dim.col;j++) 
        {
            if(arr[i][j] != 'I' && arr[i][j] != 'G')
            arr[i][j] = ' ';
        }
    }
}

void updateBlocks(char **arr, list_t *route, list_t *blocks, data_t size, 
    data_t start, data_t end) {

    
    int status = 0;
    // Remove old exisitng blocks 
    removeBlocks(blocks, arr);
    free_list(blocks);
    // Read in new blocks
    blocks = readBlocks(arr);
    
    //visualise the grid
    gridVisualizer(arr, size);
    printf(BREAK);
    // Validate the route 
    status = routeValidator(arr, size, start, end, route);

    if(status == BLOCKED) {
        routeFixer(arr, size, start, end, route, FALSE);
    }

    gridVisualizer(arr, size);
    printf(DIVIDER);
    printf("\n");
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