#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>
#include "historyList.h"

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

    char cwd[50];
    char input_buf[50];
    char* cmd_ptr_array[20];

    int numberOfCommands = 0;
    HistoryNodeType* historyList = malloc(sizeof(HistoryNodeType));

    size_t size;

    printf("%s",getcwd(cwd, size));
    printf("> ");
    fgets(input_buf, 49, stdin);
    input_buf[strlen(input_buf)-1] = '\0';

    char* tmp_ptr;

    tmp_ptr = strtok(input_buf, " \t");
    int i = 0;

    while (tmp_ptr != NULL) {
        cmd_ptr_array[i] = strdup(tmp_ptr);
//        printf("token[%d]  \"%s\"\n", i, cmd_ptr_array[i]);
        tmp_ptr = strtok(NULL, " \t");
        i++;

    }

    cmd_ptr_array[i] = NULL;

    while (strcmp(cmd_ptr_array[0], "exit")!=0){

        if (strcmp(cmd_ptr_array[0], "history")==0) {
//            for (int i = atoi(cmd_ptr_array[1]); i < 1; i-- ){
//                printf("%d %s", i, listGet(historyList, i));
//
//            }


        }

        else if (strcmp(cmd_ptr_array[0], "recall")==0) {
        }
        else if (strcmp(cmd_ptr_array[0], "cd")==0) {
            if (strcmp(cmd_ptr_array[1], "~") == 0){
                chdir(getenv("HOME"));
            }

            else{
                chdir(cmd_ptr_array[1]);
            }

//            printf("%s", cmd_ptr_array[1]);

        }


            //external command
        else{
            pid_t ret_val;
            int status;

            ret_val = fork();
            if (ret_val != 0){
                wait(&status);
            }
            else{
                execvp(cmd_ptr_array[0], cmd_ptr_array);

            }

        }

        //if it is your first command
        if (numberOfCommands == 0){
            listInsertHead(historyList, cmd_ptr_array);
            numberOfCommands++;
        }
        else{
            if (strcmp(cmd_ptr_array, listGet(historyList, numberOfCommands)) != 0){
                listInsertTail(historyList, cmd_ptr_array);
                numberOfCommands++;
            }
        }


        printf(getcwd(cwd, size));
        printf("> ");
        fgets(input_buf, 49, stdin);
        input_buf[strlen(input_buf)-1] = '\0';

        char* tmp_ptr;

        tmp_ptr = strtok(input_buf, " \t");
        int i = 0;

        while (tmp_ptr != NULL) {
            cmd_ptr_array[i] = strdup(tmp_ptr);
//            printf("token[%d]  \"%s\"\n", i, cmd_ptr_array[i]);
            tmp_ptr = strtok(NULL, " \t");
            i++;

        }

        cmd_ptr_array[i] = NULL;

    }

    free(historyList);


    return 0;

}