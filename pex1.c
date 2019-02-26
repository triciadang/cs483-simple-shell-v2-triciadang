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

    char* cmdToInput = strdup(input_buf);

    char* tmp_ptr;

    tmp_ptr = strtok(input_buf, " \t");
    int i = 0;

    while (tmp_ptr != NULL) {
        cmd_ptr_array[i] = strdup(tmp_ptr);
//        printf("token[%d]  \"%s\"\n", i, cmbd_ptr_array[i]);
        tmp_ptr = strtok(NULL, " \t");
        i++;

    }

    cmd_ptr_array[i] = NULL;


    while (strcmp(cmd_ptr_array[0], "exit")!=0){

        //if it is your first command
        if (numberOfCommands == 0){
            historyList = listInsertHead(historyList, cmdToInput);
            numberOfCommands++;
        }
        else{
            if (strcmp(cmdToInput, listGet(historyList, numberOfCommands)) != 0){
                historyList = listInsertTail(historyList, cmdToInput);
                numberOfCommands++;
            }
        }

        if (strcmp(cmd_ptr_array[0], "history")==0) {
            int numOfCmds = atoi(cmd_ptr_array[1]);
            for (int i = numOfCmds; i > 0; i-- ){
                printf("%d ", i);
                listPrintN(historyList, i);
                printf("\n");
            }
        }

        else if (strcmp(cmd_ptr_array[0], "recall")==0) {
            int cmdIndex = atoi(cmd_ptr_array[1]);
            printf("%d ", cmdIndex);
            listPrintN(historyList, cmdIndex);
            printf("\n");
        }


        else if (strcmp(cmd_ptr_array[0], "cd")==0) {
            if (strcmp(cmd_ptr_array[1], "~") == 0){
                chdir(getenv("HOME"));
            }

            else{
                chdir(cmd_ptr_array[1]);
            }
        }

        else if (strcmp(cmd_ptr_array[0], "")==0) {
            break;
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
                status = execvp(cmd_ptr_array[0], cmd_ptr_array);


            }

        }



        printf(getcwd(cwd, size));
        printf("> ");
        fgets(input_buf, 49, stdin);
        input_buf[strlen(input_buf)-1] = '\0';

        cmdToInput = strdup(input_buf);

        char* tmp_ptr;

        tmp_ptr = strtok(input_buf, " \t");
        int i = 0;

        while (tmp_ptr != NULL) {
            cmd_ptr_array[i] = strdup(tmp_ptr);
            tmp_ptr = strtok(NULL, " \t");
            i++;

        }

        cmd_ptr_array[i] = NULL;

    }

    free(historyList);


    return 0;

}

