/* Solution to comp10002 Assignment 1, 2019 semester 2.

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

   Signed by: Kaif Ahsan, 1068214
   Dated: 23 September 2019

*/


#include <stdio.h>
#include <string.h>
#include <ctype.h>


#define DEFAULTWIDTH 50    /* Default text width */
#define DEFAULTINDENT 4    /* Default left indentation */
#define MAXLEN 999         /* Max number of characters in input lines */
#define LIMIT 3            /* Highest digit count after format commands */

#define YES 1              /* Signals first format command after text*/
#define NO 0               /* Signals consucutive format commands */

/****************************************************************/

/* function prototypes */

int read_line(char line[]);
char process_line(char line[]);
void format_commands(char* line, int *mar, int *wid, int *command);
void line_printer(char line[],int *margin, int *width, int *cur_pos, 
    int *first_comm);
void indenter(int *val);
int mygetchar();

/****************************************************************/

/* main program to format the text input*/

int main(int argc, char const *argv[])
{   
    // An array to hold content of each line 
    char arr[MAXLEN]; 
    // A variable which help keeping track of words printed a in line 
    int count = 0;
    // Variables to format the ouput 
    int indent = DEFAULTINDENT, width = DEFAULTWIDTH;
    // A variable to look for consecutive commands 
    int first_command = YES;
    
    while(read_line(arr) != EOF){

        // If the line contains a command
        if(arr[0] == '.') 
        {
            /* Process format commands */
            format_commands(arr, &indent, &width, &first_command);
            /* Reseting word count in line*/
            count = 0;
        }
        /* else proceed towards printing the line */
        else
        {   
            line_printer(arr, &indent, &width, &count, &first_command);
        }
    }

    return 0;
}

/****************************************************************/


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

int read_line(char line[]) {
    // variables to control text inflow 
    int ch, num = 0;

    while((ch = mygetchar()) != EOF && ch != '\n') {
        line[num] = ch;
        num++;
    }
    line[num] = '\0';

    if(ch == EOF) {
        return EOF;
    }
    return 0;
}

/****************************************************************/


/*
 * Function: commands
 * --------------------
 * processes the text formant commands.b, .p, .l and .w
 *    and print appropiate line break and new paragraphs 
 *
 *  line :    the input line 
 *  *mar:     text left indentation
 *  *wid      text width   
 *  *command: identifies two or more consecutive commands 
 */

void format_commands(char* line, int *mar, int *wid, int *command) {
    
    if(line[1] == 'b') {
        /* If it's the first format command create newline */
        if (*command) {
            printf("\n");
            *command = NO;
        }
    }
    else if(line[1] == 'p') {
        if (*command) {
            printf("\n");
            printf("\n");
            *command = NO;
        }
    }
    else {
        int i = 0;
        // Variables to read number after commands
        int num = 0, digit;

        /* For 999 character limit each line the formatter can only be 
        upto 3 digits */
        for (i = 0; i < LIMIT; i++)
        {
            /* Number after commands will always start at the third index of */
            if(!isdigit(line[i+3])){
                break;
            }
            /* Converting the string into an integer */
            digit = line[i+3] - '0';
            num = num * 10 + digit;
        }

        /* Update width or indentation accordingly */
        if(line[1] == 'w') {
            *wid = num;
            if (*command) {
            printf("\n");
            printf("\n");
            *command = NO;
            }
        }
        if(line[1] == 'l') {
            *mar = num;
            if (*command) {
            printf("\n");
            printf("\n");
            *command = NO;
            }
        }
    }
       
    
}

/****************************************************************/

/*
 * Function: line_printer
 * --------------------
 * Strips the words only and prints them with appropiate
 *    line breaks, indentation and width 
 *
 *  ine :        the input line 
 *  *mar:        text left indentation
 *  *wid         text width
 *  *cur_pos:    retains the number of words printer so far
 *               in the line.
 * *first_comm:  determines whether its the first command 
 */

void line_printer(char line[],int *margin, int *width, int *cur_pos, 
    int *first_comm)
{
    // The delimiters which will be stripped from lines
    char delim[]=" \t\r\n\v\f";
    // Contains the word tokens 
    char* tok;
    // A 2D array to contain the tokenised words in the line
    // Size determined by the fact that line can contain 999 characters
    char words[MAXLEN][MAXLEN];
    // Variable to loop through the line
    int numWords, i = 0;
    // Double pointer for the margin
    int **mar = &margin;

    /* Since text has started to print reset first_command */
    if(*first_comm == NO) {
                *first_comm = YES;
            }
    
    tok = strtok(line, delim);
    
    numWords = 0;
    while (tok != NULL) 
    {
    /* Copying the tokens into the array */
    strcpy(words[numWords++], tok);
    
    /*go through the rest of the tokens */
    tok = strtok(NULL, delim);
    }

    /* Printing the word tokens. */
    for(i = 0; i < numWords; i ++)
    {
        /* Monitor the number of character printed*/
        *cur_pos = *cur_pos + strlen(words[i]) + 1;
                
        /* For words line character count more than or equal to 50 */
        if(strlen(words[i]) >= *width) 
        {
            printf("\n");
            indenter(*mar);
            printf("%s\n", words[i]);
            *cur_pos = 0;        
        }
        /* As long as the line limit is not reached */
        else if((*cur_pos) <= *width )
        {
            // Print this condition everything this is reached
            if(((strlen(words[i]) + 1) - *cur_pos) == 0) 
            {
                indenter(*mar);
                printf("%s", words[i]);
                // Since no space is printed reset count
                *cur_pos = *cur_pos - 1;
            }
            else {
            printf(" %s", words[i]);         
            }                         
        }
        /* Max width reached and print a new line */
        else {
            printf("\n");
            *cur_pos = strlen(words[i]);
            indenter(*mar);
            printf("%s", words[i]);      
            }
    }
}

/****************************************************************/

/*
 * Function: indenter
 * --------------------
 * Prints the current left indentation
 *
 *  *val: value of left indent  
 * 
 */
void indenter(int *val) {
    // A variable for loops
    int i = 0;
    for (i = 0; i < *val; i++)
    {
        printf(" ");
    }
    
}

/****************************************************************/

/* Function imported from Assignment FAQ page 

 * Function:  mygetchar
 * --------------------
 * Speacial getchar(0) '/r'
 *  
 * returns: c after removing /r
 */

int mygetchar() {
		int c;
		while ((c=getchar())=='\r') {
		}
		return c;
}	

/* Algorithms are fun! */