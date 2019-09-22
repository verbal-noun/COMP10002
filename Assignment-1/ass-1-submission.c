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

   Signed by: Kaif Ahsan 1068214
   Dated:     22 September 2019

*/

#include <stdio.h>
#include <string.h>
#include<ctype.h>

#define MAXLEN 999
#define YES 1
#define NO 0


void commands(char* line, int *mar, int *wid, int *command);
void indenter(int *val);

int main(int argc, char const *argv[])
{


    // Declaring variables
    char *buffer;
    size_t buffer_size = MAXLEN;
    // The delimiters for strtok function
    char s[]=" \t\r\n\v\f";;
    char* tok;
    // A 2D array to word the word we read in
    char words[1000][MAXLEN];
    int numWords = 0;
    // A variable to check first command or not
    int first_command = YES;
    
    // A variable to assist us printing stuff
    int count = 0, margin = 4, width = 50;

    while (getline(&buffer, &buffer_size, stdin) != EOF)
    {
        //printf("%s", buffer);
        // tokenising the input


        if(buffer[0] == '.') {
            // processs the commands
            commands(buffer, &margin, &width, &first_command);
            count = 0;
        }
        else {
            if(first_command == NO) {
                first_command = YES;
            }
            // Not consecutive commands
            tok = strtok(buffer, s);
            //For every new line we should reset numWords to 0
            numWords = 0;
            while (tok != NULL) {
            // Here we have our tokens coming in. Save these words into our array
            strcpy(words[numWords++], tok);

            // Use of strtok
            // go through other tokens
            tok = strtok(NULL, s);
            }
            
            
            for(int i = 0; i < numWords; i ++)
            {
                //if(count == 0) printf("zero\n");
                count = count + strlen(words[i]) + 1;
                
                // For words line character count more than or equal to 50
                if(strlen(words[i]) >= width) {
                    printf("\n");
                    indenter(&margin);
                    printf("%s\n", words[i]);
                   
                
                }
            // As long as the line limit is not reached
                //|| (count-1 == width)
                else if((count) <= width ){
                    // Print this condition everything this is reached

                    if(((strlen(words[i]) + 1) - count) == 0) {
                        indenter(&margin);
                        printf("%s", words[i]);
                        // Since no space is printed reset count
                        count--;
                    } else
                    {
                       printf(" %s", words[i]);
                       
                    }
                                        
                }
                else {
                    printf("\n");
                    count = strlen(words[i]);
                    indenter(&margin);
                    printf("%s", words[i]);
                    
                   
                }
        }

        // Here, we should have copied all the words into the array words.

        // Lets print out everything in words, for each of our line read

        }
    }


    return 0;
}

void commands(char* line, int *mar, int *wid, int *command) {
    
    
    if(line[1] == 'b') {
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
        int num = 0, digit;
        // For 999 characters the formatter can only be upto 3 digits
        for (size_t i = 0; i < 3; i++)
        {
            if(!isdigit(line[i+3])){
                break;
            }
            /* code */
            digit = line[i+3] - '0';
            num = num * 10 + digit;


        }

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

void indenter(int *val) {
    for (int i = 0; i < *val; i++)
    {
        printf(" ");
    }
    
}