/* Solution to comp10002 Assignment 2, 2019 semester 2.

   Authorship Declaration:

   (1) I certify that the program contained in this submission is completely
   my own individual work, except where explicitly noted by comments that
   provide details otherwise.  I understand that work that has been developed
   by another student, or by me in collaboration with other students,
   or by non-students as a result of request, solicitation, or payment,
   may not be submitted for assessment in this subject.  I understand that
   submitting for assessment work developed by or in collaboration with
   other students or non-students constitutes Academic Misconduct, and
   may be penalized by mark deductions, or by other penalties determined
   via the University of Melbourne Academic Honesty Policy, as described
   at https://academicintegrity.unimelb.edu.au.

   (2) I also certify that I have not provided a copy of this work in either
   softcopy or hardcopy or any other form to any other student, and nor will
   I do so until after the marks are released. I understand that providing
   my work to other students, regardless of my intention or any undertakings
   made to me by that other student, is also Academic Misconduct.

   (3) I further understand that providing a copy of the assignment
   specification to any form of code authoring or assignment tutoring
   service, or drawing the attention of others to such services and code
   that may have been made available via such a service, may be regarded
   as Student General Misconduct (interfering with the teaching activities
   of the University and/or inciting others to commit Academic Misconduct).
   I understand that an allegation of Student General Misconduct may arise
   regardless of whether or not I personally make use of such solutions
   or sought benefit from such actions.

   Signed by: Kaif Ahsan 108214
   Dated:     21 October 2019

*/


#include <stdio.h>
#include <assert.h>
#include <stdlib.h>


#define INVALID_START -1 /* If the first cell of route differs from start call*/
#define INVALID_END -2   /* If the last cell of route differs from goal call  */
#define INVALID_MOVE -3  /* If route makes any invalid move                   */
#define BLOCKED 4        /* If route is broken                                */   
#define VALID 5          /* If route is passes all the validity conditions    */
#define TRUE 1
#define FALSE 0
#define BLOCK '#'        /* Char to denote block is the route                 */
#define ROUTE '*'        /* Char to denote travelled path in the grid         */   
#define INPUT '$'        /* Indicator of routes and new block configuration   */
#define BREAK "------------------------------------------------\n"      
#define DIVIDER "================================================\n"
#define STAGE_ZERO "==STAGE 0=======================================\n"
#define STAGE_ONE "==STAGE 1=======================================\n"
#define STAGE_TWO "==STAGE 2=======================================\n"
#define LINE 3           /* Length of input like containing '$' (\0) included */
#define MARGIN 10        /* Controls the numbers printed in the margin        */


/* Struct declaration */
typedef struct node node_t;

/* A struct to handle the cell coordinates and counter values */
typedef struct
{
    /* data */
    int row;
    int col;
    int counter;
} data_t;

/* Struct for each node of the doubly linked list */
struct node 
{
    /* data */
    data_t data;
    node_t *next;
    node_t *prev;
};

/* Doubly linked list*/
/* Program taken from Lecture Slide 7 */
typedef struct
{
    node_t *head;
    node_t *foot;
} list_t;


/******************************************************************************/
/* Function prototypes */
list_t *makeEmptyList (void);
void freeList(list_t *list);
list_t *insertHead(list_t *list, data_t value);
list_t *insertFoot(list_t *list, data_t value);
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
int readLine(char line[]);
int mygetchar();

/******************************************************************************/


int main(int argc, char const *argv[])
{   
    
    // Struct to hold dimensions of grid and coordinates of start and end cell
    data_t size, start, goal;
    // Variable which holds the condition of the route
    int status = 0; 
    // Creating a 2D to hold the grid 
    char **grid;
    grid = createGrid(&size, &start, &goal);

    // Variables used to process stage 2
    // An array to hold '$' input commands
    char line[LINE];
    // Variable to differentiate stage 1 and stage 2 
    int stageTwo = FALSE; 
    
    // Creating the blocks & reading from the input
    list_t *blocks;
    blocks = readBlocks(grid);
    
    // Creating a linked list for the route and taking input
    list_t *route;
    route = readRoute(grid);

    // Printing grid information as part of stage 0
    gridInfoPrinter(grid, size, start, goal, blocks, route);
    // Checking validity of the route
    status = routeValidator(grid, size, start, goal, route);

    // Stage 1 output formatting
    printf(STAGE_ONE);
    // Printing contents of the grid onto the screen 
    gridVisualizer(grid, size);
    // If route has invalid start, end or moves 
    if(status < BLOCKED) {
        printf(DIVIDER);
        return 0;
    }
    // If route has a block in it
    else if(status == BLOCKED) {
        // Call fixer function -> Attempt to fix only the first block 
        firstAttempt(grid, size, start, goal, route);
    }
    
    // Read in new block configurations
    while(readLine(line) != EOF) {
        if(line[0] == INPUT) {
            // Denote the initiation of stage 2 -> Full repair will be attempted
            if(!stageTwo) {
                stageTwo = TRUE;
                printf(STAGE_TWO);
            }
            // Update new configuration and proced repair if required
            updateBlocks(grid, route, blocks, size, start, goal);
        }
    }
    

    // If no stage 2 was part of the test print formatter
    if(!stageTwo) printf(DIVIDER);

    /* Freeing memory */
    freeList(blocks);
    freeList(route);
    freeGrid(grid, size);
    

    return 0;
}


/******************************************************************************/

/*
 * Function:  makeEmptyList
 * --------------------------
 * Function to create an empty list and return the address 
 * 
 * NOTE: Function imported from Lecture slides (Lecture 7)
 */

list_t *makeEmptyList (void) {
    list_t *list;
    list = (list_t*)malloc(sizeof(*list));
    assert(list!= NULL);
    list->head = list->foot = NULL;
    return list;
}

/******************************************************************************/
/*
 * Function:  freeList
 * --------------------------
 * Function to free a list_t type linked list
 *
 * list: The list which modified 
 * 
 * NOTE: Function imported from Lecture slides (Lecture 7)
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

/******************************************************************************/
/*
 * Function:  insertFoot
 * --------------------------
 * Function to insert item at the top of a doubly linked list
 *
 * list: The list which modified 
 * value: The data which will be added to the list 
 * 
 * return: Pointer address of the modified list
 * 
 * NOTE: Base function imported from Lecture slides (Lecture 7)
 */
list_t *insertHead(list_t *list, data_t value) {
    
    // Creating a new node 
    node_t *new;
    new = (node_t*)malloc(sizeof(*new));
    assert(new != NULL && list != NULL);

    // Initialise default values 
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

/******************************************************************************/
/*
 * Function:  insertFoot
 * --------------------------
 * Function to append item at the end of a doubly linked list
 *
 * list: The list which modified 
 * value: The data which will be added to the list 
 * 
 * return: Pointer address of the modified list
 * 
 * NOTE: Base function imported from Lecture slides (Lecture 7)
 */
list_t *insertFoot(list_t *list, data_t value) {
    
    // Creating a new node
    node_t *new;
    new = (node_t*)malloc(sizeof(*new));
    assert(new != NULL && list != NULL);

    // Initialise default values 
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

/******************************************************************************/
/*
 * Function:  createGrid
 * --------------------------
 * Function to create dynamic 2D grid based of input
 *
 * size: Dimention of the grid
 * init: Coordinate of starting cell
 * end: Coordinates of ending cell
 * 
 * return: Pointer to pointer to a character array. 
 */
char **createGrid(data_t *size, data_t *init, data_t *end) {
    // Variables which hold dimention of the grid
    int row = 0, col = 0;
    // Variable to assist in loops
    int i = 0;
    // x and y coordinates of start cell 
    int irow = 0, icol = 0;
    // x and y coordinates of goal cell 
    int grow = 0, gcol = 0;
    // 2D grid to store information from the input
    char **grid;

    // Take input of the dimension
    scanf("%dx%d\n", &row, &col);
    size->row = row;
    size->col = col;

    // Dynamic allocation of 2D grid based on input 
    grid = (char**)malloc(row * sizeof(char*));
    assert(grid != NULL);
    for(i=0; i < row; i++)
    {
        grid[i] = (char*)malloc(col * sizeof(char*));
        assert(grid[i] != NULL);
    }    

    // Inputting coordinates of I and G
    scanf("[%d,%d]\n", &irow, &icol);
    init->row = irow;
    init->col = icol;
    scanf("[%d,%d]\n", &grow, &gcol);
    end->row = grow;
    end->col = gcol;

    // Identify I and G in the grid 
    grid[irow][icol] = 'I';
    grid[grow][gcol] = 'G';

    // Filling up the space 
    gridEmptier(grid, *size);

    return grid;
}

/******************************************************************************/
/*
 * Function:  readBlocks 
 * --------------------------
 * Function to read the blocks from the input and store as a linked list
 *
 * arr: Dynamic 2D array to hold all contents of the grid
 * 
 * return: Returns a linked list containing the blocks in the grid 
 */
list_t *readBlocks(char **arr) {
    // Variables for x and y coordinates of the block 
    int row = 0, col = 0;
    data_t coor;

    // Creating list to hold the blocks 
    list_t *blocks;
    blocks = makeEmptyList(); 
    assert(blocks != NULL);

    while (scanf("[%d,%d]\n", &row, &col) == 2)
    {
        // Taking input until $ sign is reached or end of file. 
        coor.col = col;
        coor.row = row;
        blocks = insertFoot(blocks, coor);
        // Updating the cell block in the grid
        arr[row][col] = BLOCK;
    }

    return blocks;
}

/******************************************************************************/
/*
 * Function:  removeBlocks
 * -----------------------
 * Function to remove blocks from the grid and prepare grid for new blocks 
 * orientation
 * 
 * blocks: Linked list containing the obstacles in the grid
 * arr: Dynamic 2D array to hold all contents of the grid
 * 
 */

void removeBlocks(list_t *blocks, char **arr) {
    // Variable for traversing the blocks without consuming it
    node_t *temp;
    
    temp = blocks->head;
    while (temp != NULL)
    {
        // Removing # in the main grid
        arr[temp->data.row][temp->data.col] = ' ';
        temp = temp->next;
    }
}

/******************************************************************************/
/*
 * Function:  readRoute
 * ---------------------
 * Function to read routes from the input
 *
 * arr: Dynamic 2D array to hold all contents of the grid
 * 
 * return: Linked list containing the current route
 */
list_t *readRoute(char **arr) {
    // x and y coordinates of the route cell 
    int row = 0, col = 0;
    char c;
    list_t *route;
    
    route = makeEmptyList();
    assert(route != NULL);
    
    scanf("%c\n", &c);
    
    // start inputting if '$' indicator is present 
    if(c == INPUT) {
        while (scanf("[%d,%d]-> ", &row, &col) == 2) {
            //read in values for the route
            data_t route_coor;
            route_coor.row = row;
            route_coor.col = col;
            route = insertFoot(route, route_coor);
        }
    }
    // Draw the route onto the grid
    routeDraw(arr, route);

    return route;
}

/******************************************************************************/
/*
 * Function:  routeDraw
 * ---------------------
 * Function to draw current route onto the grid
 *
 * arr: Dynamic 2D array to hold all contents of the grid
 * route: Linked list of path taken to reach the destination
 * 
 */
void routeDraw(char **arr, list_t *route) {
    // Node to traverse the list without consuming it
    node_t *temp;

    temp = route->head;
    while(temp != NULL) {
        // Overwrite whitespace only
        if(arr[temp->data.row][temp->data.col] == ' ') {
                arr[temp->data.row][temp->data.col] = ROUTE;
        }

        temp = temp->next;
    }
}

/******************************************************************************/
/*
 * Function:  removeRoute
 * -----------------------
 * Function to remove the route from the grid 
 *
 * arr: Dynamic 2D array to hold all contents of the grid
 * route: Linked list of path taken to reach the destination
 * 
 */
void removeRoute(char **arr, list_t *route) {
    // Node to traverse the list without consuming it
    node_t *temp;

    temp = route->head;
    while(temp != NULL) {
        // Replace '*' with whitespace 
        if(arr[temp->data.row][temp->data.col] == ROUTE) {
            arr[temp->data.row][temp->data.col] = ' ';            
        }
        temp = temp->next;
    }

}

/******************************************************************************/
/*
 * Function:  freeGrid
 * --------------------------
 * Function to free a dynamic 2D grid
 *
 * arr: Dynamic 2D array to hold all contents of the grid
 * size: Dimention of the grid
 * 
 * NOTE: Function taken from Lecture 7 slides.
 */
void freeGrid(char **arr, data_t size) {
    int i = 0;
    
    for(i = 0; i < size.row; i++)
    {
        free(arr[i]);
        arr[i] = NULL;
    }
    free(arr);
}

/******************************************************************************/
/*
 * Function:  gridInfoPrinter
 * --------------------------
 * Function to process stage 0 info printing of the input
 *
 * arr: Dynamic 2D array to hold all contents of the grid
 * dim: Dimention of the grid
 * start: Coordinate of starting cell
 * end: Coordinates of ending cell
 * barrier: Linked list of the blocks in the grid 
 * path: Linked list of path taken to reach the destination
 * 
 */
void gridInfoPrinter(char **arr, data_t dim, data_t start, data_t end, 
    list_t *barrier, list_t *path) {
    
    // Variable to hold number of blocks 
    int barrierCount = 0;
    // Variable to hold status of current route
    int status = 0;

    printf(STAGE_ZERO);
    // Printing grid dimensions 
    printf("The grid has %d rows and %d columns.\n", dim.row, dim.col);
    // Print info about number of blocks
    barrierCount = listItemCount(barrier);
    printf("The grid has %d block(s).\n", barrierCount); 
    // Coordinates of start and goal cell 
    printf("The initial cell in the grid is [%d,%d].\n", start.row, start.col);
    printf("The goal cell in the grid is [%d,%d].\n", end.row, end.col);

    // Current route from the input
    printf("The proposed route in the grid is:\n");
    routePrinter(path);
    //Check current status of the route
    status = routeValidator(arr, dim, start, end, path);

    // Print status of the current route
    if(status == INVALID_START) {
        printf("Initial cell in the route is wrong\n");
    }
    else if(status == INVALID_END) {
        printf("Goal cell in the route is wrong!");
    } 
    else if(status == INVALID_MOVE) {
        printf("There is an illegal move in this route\n");
    }
    else if(status == BLOCKED) {
        printf("There is a block on this route!\n");
    }
    else {
        printf("The route is valid!\n");
    }
}

/******************************************************************************/
/*
 * Function:  listItemCount
 * -----------------------
 * Function which counts the number of nodes in a linked list 
 *
 * list: The linked list containing the nodes to be counted 
 * 
 * return: The number of nodes
 */
int listItemCount(list_t *list) {
    // Variable to hold number of items in the list 
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

/******************************************************************************/
/*
 * Function:  
 * -----------------------
 * Prints the route grid onto the screen - upto 5 coordinates at a time  
 * 
 * path: Linked list of path taken to reach the destination
 * 
 */
void routePrinter(list_t *path) {
    // Variable to control upto 5 items printed per line
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

/******************************************************************************/
/*
 * Function:  routeValidator
 * -----------------------
 * Function to process stage 1: make one attempt to fix the route and fix the 
 * first broken segment 
 *
 * arr: Dynamic 2D array to hold all contents of the grid
 * size: Dimention of the grid
 * start: Coordinate of starting cell
 * goal: Coordinates of ending cell
 * route: Linked list of path taken to reach the destination
 * 
 */
int routeValidator(char **arr, data_t size, data_t start, data_t end, 
    list_t *route) {

        // Variables to determine how far route has travelled at one step 
        int rowTraverse = 0;
        int colTraverse = 0;
        // Variables to holding block cell coordinates
        int row = 0, col = 0;
        // Variable to denote starting of the route 
        int firstCell = TRUE;

        // Check if the route starts with the correct coordinates
        if(route->head->data.row != start.row || route->head->data.col 
        != start.col) {
            return INVALID_START;
        }

        // Check if the route ends with the correct coordinates
        if(route->foot->data.row != end.row || route->foot->data.col 
        != end.col) {
            return INVALID_END;
        }

        // Check for illegal move in the route
        node_t *temp; 
        data_t prev;

        temp = route->head;
        prev.row = temp->data.row;
        prev.col = temp->data.col;

        // Check the validity of the current node 
        while(temp != NULL)
        {
            // Cheking if the route travels outside the grid
            if(temp->data.row > size.row || temp->data.col > size.col){
                return INVALID_MOVE; 
            }
            
            // Any illegal row movement 
            rowTraverse = temp->data.row - prev.row;
            if(rowTraverse > 1 || rowTraverse < -1 ) {
                // Check whether the route stays static after two rounds 
                if(rowTraverse == 0 && !firstCell) {
                    return INVALID_MOVE;
                }
                return INVALID_MOVE;
            }

            // Any illegal column movement
            colTraverse = temp->data.col - prev.col;
            if(colTraverse > 1 || colTraverse < -1) {
                // Check whether the route stays static after two rounds 
                if(colTraverse == 0 && !firstCell) {
                    return INVALID_MOVE;
                }
                return INVALID_MOVE;
            }

            // Store coordinates of previous row for comparison
            prev.row = temp->data.row;
            prev.col = temp->data.col;
            firstCell = FALSE;
            temp = temp->next;
            
        }

        // Check if a block is present in the route 
        temp = route->head;

        while(temp != NULL)
        {
            // Check for blocks 
            row = temp->data.row;
            col = temp->data.col;
            if(arr[row][col] == BLOCK) {
                return  BLOCKED;
            }
            temp = temp->next;

        }

    return VALID;
}   

/******************************************************************************/
/*
 * Function:  routeFixer
 * ---------------------
 * A recursive function which stops at first fix if its stage 1, else tries to 
 * do a full repair
 *
 * arr: Dynamic 2D array to hold all contents of the grid
 * size: Dimention of the grid
 * start: Coordinate of starting cell
 * goal: Coordinates of ending cell
 * route: Linked list of path taken to reach the destination
 * firstFix: An integer to denote whether this is Stage 1 or not
 * 
 */
void routeFixer(char **arr, data_t size, data_t start, data_t end, 
    list_t *route, int firstFix) {

    // The cell in route before the first block 
    node_t *broken_segment;

    // Status denoting variables 
    int notFixed = FALSE, status = 0;

    // Pass route into blockFinder function and return block coordinate
    broken_segment = blockFinder(arr, route);

    // Remove route with blocks in the path
    removeRoute(arr, route);

    if(!broken_segment) {
        // routeFixer function called without any blocks in the route => error 
        exit(EXIT_FAILURE);
    }

    //  Pass broken segment into traverseGrid function and create a traversal
    notFixed = traverseGrid(arr, broken_segment, route, size);
    if(notFixed) {
        // Terminate function if no solutions are foind 
    }
    else {
        // If not stage-1, try to do a full repair recursively
        status = routeValidator(arr, size, start, end, route);
        if(status == BLOCKED && !firstFix) {
            routeFixer(arr, size, start, end, route, firstFix);
            
        }
        else {
            // Draw new route onto the grid when path is fixed.
            routeDraw(arr, route); 
        }
    }

}

/******************************************************************************/
/*
 * Function:  firstAttempt
 * -----------------------
 * Function to process stage 1: make one attempt to fix the route and fix the 
 * first broken segement 
 *
 * arr: Dynamic 2D array to hold all contents of the grid
 * size: Dimention of the grid
 * start: Coordinate of starting cell
 * goal: Coordinates of ending cell
 * route: Linked list of path taken to reach the destination
 * 
 */
void firstAttempt(char **arr, data_t size, data_t start, data_t goal, 
    list_t *route) {
    // Variable to denote whether route is fixed or not
    int routeFixed = 0;
    
    // Fix route once denoting presence of Stage 1
    routeFixer(arr, size, start, goal, route, TRUE);
    routeFixed = routeValidator(arr, size, start, goal, route);
    
    // Visualise the route 
    if(routeFixed == VALID) {
        printf(BREAK);
        gridVisualizer(arr, size);
        printf(BREAK);
        routePrinter(route);
        printf("The route is valid!\n");
    }
    else {
        
        printf(BREAK);
        gridVisualizer(arr, size);
        printf(BREAK);
        routePrinter(route);
        printf("There is a block in this route!\n");
    } 
}

/******************************************************************************/
/*
 * Function:  traverseGrid 
 * -----------------------
 * Creates a linked list containing counter value starting from the cell right 
 * before the first block in the route 
 *
 * arr: Dynamic 2D array to hold all contents of the grid
 * cell: the cell right before the first block in the route 
 * route: Linked list of path taken to reach the destination
 * size: Dimentions of the grid
 *  
 * return: returns FALSE if no fix found of the broken route else returns TRUE
 */
int traverseGrid(char **arr, node_t *cell, list_t *route, data_t dim) {
    
    // List to hold queue created from grid traversal
    list_t *queue; 
    // A list to hold new alternative route 
    list_t *new_path;
    queue = makeEmptyList();
    new_path = makeEmptyList();

    // Variable to check cell exists in queue from before or not 
    int exist = 0;
    // Variable to denote whether a fix is found or not 
    int found = FALSE;
    // Struct to hold information about the new route 
    data_t info;
    int row = 0, col = 0;
    // Nodes to traverse lists without consuming 
    node_t *temp, *finder;

    // Input the first broken segment in the queue 
    info.row = cell->data.row;
    info.col = cell->data.col;
    info.counter = 0;
    queue = insertFoot(queue, info);

    temp = queue->head;
    
    // Traverse the queue until all options exhausted or fix is founds
    while (temp!=NULL) {
        row = temp->data.row;
        col = temp->data.col;

        
        // Check up
        if(row - 1 >= 0) {
            finder = cell->next;
            // check if that row already exists in the queue 
            exist = checkQueue(row-1, col, queue);

            // Check if it's blocked or not 
            if(arr[row-1][col] != BLOCK) {
                info.row = row - 1;
                info.col = col;
                info.counter = temp->data.counter + 1;
                if(!exist) queue = insertFoot(queue, info);
            }

            // Check if new cell is part of the route 
            while(finder!=NULL && !exist) {
                if(row-1 == finder->data.row && col == finder->data.col && 
                arr[row-1][col] != BLOCK) {
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
            // check if that row already exists in the queue 
            exist = checkQueue(row+1, col, queue);

            // Check if it's blocked or not 
            if(arr[row+1][col] != BLOCK) {
                info.row = row + 1;
                info.col = col;
                info.counter = temp->data.counter + 1;
                if(!exist) queue = insertFoot(queue, info);
            }

            // Check if new cell is part of the route 
            while(finder!=NULL && !exist) {
                if(row+1 == finder->data.row && col == finder->data.col && 
                arr[row+1][col] != BLOCK) {
                    found = TRUE;
                    break;
                }

                finder = finder->next;
            }  
        }
        if(found) break;

        // Check left 
        if(col-1 >= 0) {
            
            // check if that row already exists in the queue 
            exist = checkQueue(row, col-1, queue);

            // Check if it's blocked or not 
            if(arr[row][col-1] != BLOCK) {
                info.row = row;
                info.col = col - 1;
                info.counter = temp->data.counter + 1;
               if(!exist) queue = insertFoot(queue, info);
            }

            finder = cell->next;
            // Check if new cell is part of the route 
            while(finder!=NULL && !exist) {
                if(row == finder->data.row && col-1 == finder->data.col &&
                arr[row][col-1] != BLOCK) {
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
            // check if that row already exists in the queue 
            exist = checkQueue(row, col+1, queue);

            // Check if it's blocked or not 
            if(arr[row][col+1] != BLOCK) {
                info.row = row;
                info.col = col+1;
                info.counter = temp->data.counter + 1;
                if(!exist) queue = insertFoot(queue, info);
            }
            // Check if new cell is part of the route 
            while(finder!=NULL && !exist) {
                if(row == finder->data.row && col+1 == finder->data.col && 
                arr[row][col+1] != BLOCK) {
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
        // If a solution is found create a new alternative path
        new_path = pathBuilder(queue, route, dim);
        // Remove route with blocks in the path
        removeRoute(arr, route);
        // update old route
        updatePath(route, new_path, queue);

        // Freeing memory 
        freeList(queue);
        return FALSE; 
    }
    else {

        freeList(queue);
        return TRUE;
    }
    
}

/******************************************************************************/
/*
 * Function:  blockFinder
 * ----------------------
 * Traversed through the route and returns the address of the first block 
 *
 * arr: Dynamic 2D array to hold all contents of the grid
 * route: Linked list of path taken to reach the destination
 * 
 * return: returns the pointer address of the block 
 * NOTE: This function can only be called when it is predetermined that a block
 *       exists in the route. 
 */
node_t *blockFinder(char **arr, list_t *route) {
    
    node_t *temp;
    // Variables to hold coordinates 
    int row = 0, col = 0;
    assert(route != NULL && route->head != NULL);

    temp = route->head;
    while(temp != NULL) {
        if(temp->next != NULL) {
            row = temp->next->data.row;
            col = temp->next->data.col;
        }

        // If a blocks is found return pointer address  
        if(arr[row][col] == BLOCK) {
            return temp;
        }

        temp = temp->next;
    }

    return FALSE;
}

/******************************************************************************/
/*
 * Function:  checkQueue
 * -----------------------
 * Checks for duplicates in the queue 
 *
 * row: xycoordinate of the cell being considered
 * col: y-coordinate of the cell being considered
 * queue: A linked list containing the queue created from traversing the list 
 *        and flushing the grid with counter values  
 *  
 * return: TRUE if the queue exists previously else FALSE
 */
int checkQueue(int row, int col, list_t *queue) {
    node_t *temp;
    temp = queue->head;

    // IF coordinates previously exist if the queue or not
    while(temp != NULL) {
        if(temp->data.row == row && temp->data.col == col) {
            return TRUE;
        }

        temp = temp->next;
    }
    return FALSE;
}

/******************************************************************************/
/*  
 * Function:  pathBuilder 
 * ----------------------
 * Forms a new route by traversing from the bottom of the queue to the cell 
 * before the first broken segment
 * 
 * queue: A linked list containing the queue created from traversing the list 
 *        and flushing the grid with counter values 
 * route: Linked list of path taken to reach the destination
 * size: Dimentions of the grid
 * 
 * return: A new path containing an alternative route
 */
list_t *pathBuilder(list_t *queue, list_t* route, data_t size) {
    
    // A 2D grid which will flushed with counter values 
    char **grid;
    int i = 0, j = 0;
    node_t *temp;
    // Structures to hold information about the queue cells 
    data_t pos, info;
    // Linked list for the new alternative route 
    list_t *new_path;
    new_path = makeEmptyList();
    
    // Dynamic 2D grid creation
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

    // Insert counter values in the grid
    temp = queue->foot;
    while (temp != NULL) {
        grid[temp->data.row][temp->data.col] = temp->data.counter;
        temp = temp->prev;
    }

    // Coordinates and counter value of the starting cell 
    pos = queue->foot->data;
    
    // Look to build a path until we reach the destination cell 
    while(pos.counter != 1) {

        // Check upper cell 
        if((pos.row-1 >= 0) && grid[pos.row - 1][pos.col] == 
        (pos.counter - 1)) {
            info.row = pos.row -1;
            info.col = pos.col;
            info.counter = pos.counter - 1;
            pos = info;
            new_path = insertHead(new_path, info);
        }
        // Check bottom cell
        else if((pos.row + 1 < size.row) && grid[pos.row + 1][pos.col] == 
        (pos.counter - 1)) {
            info.row = pos.row + 1;
            info.col = pos.col;
            info.counter = pos.counter - 1;
            pos = info;
            new_path = insertHead(new_path, info);
        }
        // Check cell at the left 
        else if((pos.col -1 >= 0) && grid[pos.row][pos.col - 1] == 
        (pos.counter - 1)) {
            info.row = pos.row;
            info.col = pos.col - 1;
            info.counter = pos.counter - 1;
            pos = info;
            new_path = insertHead(new_path, info);
        }
        // Check cell at the right
        else if((pos.col < size.col) && grid[pos.row][pos.col + 1] == 
        (pos.counter - 1)) {
            info.row = pos.row;
            info.col = pos.col + 1;
            info.counter = pos.counter - 1;
            pos = info;
            new_path = insertHead(new_path, info);
        }
    } 
    
    return new_path;

    freeGrid(grid, size);     
}

/******************************************************************************/
/*
 * Function:  updatePath
 * ---------------------
 * Inserts the new built path from the queue into the original route and frees
 * old segments
 *
 * route: Linked list of path taken to reach the destination
 * new_path: Linked list containing the fixed segment
 * queue: A linked list containing the queue created from traversing the list 
 *        and flushing the grid with counter values 
 * 
 */
void updatePath(list_t *route, list_t *new_path, list_t* queue) {
    node_t *start, *end, *temp, *prev;
    assert(route && new_path && queue);

    // Variable to hold at the coordinate where the new route starts 
    start = NULL;
    // Variable to hold at the coordinate where the new route ends 
    end = NULL;

    temp = route->head;
    // Finding which part of the route needs to be changed 
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

    // Freeing blocked parts of old route
    temp = start->next;
    while (temp != end) {
        // Free list
        prev = temp;
        temp = temp -> next;
        free(prev);
    }

    // Update route 
    // Connecting broken segment with the head of the new path
    start->next = new_path->head;
    new_path->foot->prev = start;
    // Connecting the foot of the new route with the old route
    new_path->foot->next = end;
    end->prev = new_path->foot;
}

/******************************************************************************/
/*
 * Function:  gridVisualizer
 * -------------------------
 * Prints contents of the Grid on the screen
 *
 * arr: Dynamic 2D array to hold all contents of the grid
 * size: Dimentions of the grid  
 */
void gridVisualizer(char **grid, data_t size) {
    int i = 0, j = 0;
    // Variable to keep margin values in range [0,9]
    int counter = 0;
    
    // Printing the top margin
    printf(" ");
    while(counter < size.col) {
        printf("%d", i);
        counter++;
        i++;
        if(i == MARGIN) {
            i = 0;
        }    
    }
    printf("\n");
    counter = 0;

    // Printing contents of the 2D grid
    for(i = 0; i < size.row; i++) {
        printf("%d", counter);
        for(j = 0; j < size.col; j++) {
            printf("%c", grid[i][j]);
        }
        printf("\n");
        // Reseting the value for the left hand side margin
        counter++;
        if(counter == MARGIN) counter = 0;
    }
}

/******************************************************************************/
/*
 * Function:  gridEmptier
 * ----------------------
 * Fills dynamic 2D grid with ' '
 *
 * arr: Dynamic 2D array to hold all contents of the grid
 * dim: Dimentions of the grid
 */
void gridEmptier(char **arr, data_t dim) {
    
    int i = 0, j = 0;

    for(i=0; i <dim.row; i++) 
    {
        for(j=0;j<dim.col;j++) 
        {
            // Empty contents except the start and goal cell
            if(arr[i][j] != 'I' && arr[i][j] != 'G')
            arr[i][j] = ' ';
        }
    }
}

/******************************************************************************/
/*
 * Function:  updateBlocks
 * -----------------------
 * reads new block configuration and tries to do a full repart
 *
 * arr: Dynamic 2D array to hold all contents of the grid
 * route: Linked list of path taken to reach the destination
 * blocks: Obstacles on the grid 
 * size: Dimentions of the grid
 * start: Coordinate of starting cell
 * end: Coordinates of ending cell
 *  
 */
void updateBlocks(char **arr, list_t *route, list_t *blocks, data_t size, 
    data_t start, data_t end) {

    
    // Variable to contain the status of current route 
    int status = 0;
    // Variable which keeps track of the number of blocks 
    int blockCount = 0;
    // Remove old blocks 
    removeBlocks(blocks, arr);
    freeList(blocks);

    // Read in new blocks
    blocks = readBlocks(arr);
    blockCount = listItemCount(blocks);
    // If no blocks exist, print previous route 
    if(blockCount == 0) {
        routeDraw(arr, route);
        gridVisualizer(arr, size);
        printf(DIVIDER);
    }
    // For new blocks configuration 
    else {
        //visualise the grid
        gridVisualizer(arr, size);
        printf(BREAK);
        // Validate the route 
        status = routeValidator(arr, size, start, end, route);

        // Try to do a full repair 
        if(status == BLOCKED) {
            routeFixer(arr, size, start, end, route, FALSE);
        }

        // Visualise the grid before repair
        routeDraw(arr, route);
        gridVisualizer(arr, size);
        printf(BREAK);

        
        status = routeValidator(arr, size, start, end, route);
        // If route still blocked after attempt 
        if(status == BLOCKED) {
            printf("The route cannot be repaired!\n");
            routePrinter(route);
        }
        // Repair successful
        else {
            printf("The route is valid!\n");
        }
        printf(DIVIDER); 
    }   
      
}

/******************************************************************************/
/*
 * Function:  read_line
 * --------------------
 * reads the text input line by line
 *
 *  line: unformatted text input
 *  
 * returns: 0 if it reaches the end of line without encountering EOF
 *           EOF when end of file is reached.
 */

int readLine(char line[]) {
    // variables to control text inflow 
    int ch, len = 0;

    // Read each line
    while((ch = mygetchar()) != EOF && ch != '\n') {
        line[len] = ch;
        len++;
    }
    line[len] = '\0';

    if(ch == EOF) {
        return EOF;
    }
    return 0;
}

/****************************************************************/

/* 

 * Function:  mygetchar
 * --------------------
 * Special getchar(0) '/r'
 *  
 * returns: c after removing /r
 * 
 * NOTE: Function imported from Assignment FAQ page 
 */

int mygetchar() {
		int c;
		while ((c=getchar())=='\r') {
		}
		return c;
}	

/* Algoritms are fun */ 