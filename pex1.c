#include <stdio.h>
#include <string.h>

/*=============================================================================
 |   Assignment:  PEX1
 |       Author:  Tricia Dang
 |      Section:  M3
 |        Class:  CS483
 +-----------------------------------------------------------------------------
 |   Description:  DESCRIBE THE PROBLEM THAT THIS PROGRAM WAS WRITTEN TO
 |      SOLVE.
 |
 |   Required Features Not Included:  DESCRIBE HERE ANY REQUIREMENTS OF
 |      THE ASSIGNMENT THAT THE PROGRAM DOES NOT ATTEMPT TO SOLVE.
 |
 |   Known Bugs:  IF THE PROGRAM DOES NOT FUNCTION CORRECTLY IN SOME
 |      SITUATIONS, DESCRIBE THE SITUATIONS AND PROBLEMS HERE.
 +-----------------------------------------------------------------------------
 |   Documentation Statement:  PLACE YOUR DOCUMENTATION STATEMENT HERE
 *===========================================================================*/

int main() {

    char buf[50];
    char* cmd_ptr_array[20];

    printf("Enter command: ");
    fgets(buf, 49, stdin);
    buf[strlen(buf)-1] = '\0';

    char* tmp_ptr;

    while ( buf != "exit") {

        tmp_ptr = strtok(buf, " \t");
        int i = 0;

        while (tmp_ptr != NULL) {
            cmd_ptr_array[i = strdup(tmp_ptr)];
            printf("token[%d]  \"%s\"\n", i, cmd_ptr_array[i]);
            tmp_ptr = strtok(NULL, " \t");
            i++;

        }

        cmd_ptr_array[i] = NULL;


        printf("Enter command: ");
        fgets(buf, 49, stdin);
    }

    return 0;
}