#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <stdbool.h>
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

    //initialize variables
    char cwd[50];
    char input_buf[50];
    char* cmd_ptr_array[20];
    int status = 0;
    int numOfCmds = 0;
    int cmdIndex = 0;
    int numberOfCommands = 0;
    HistoryNodeType* historyList = malloc(sizeof(HistoryNodeType));
    size_t size;
    bool recall = false;


    //Print Air Force Shell and Current Working Directory
    printf("%s\n\n", "...Air Force Shell (afsh)...");
    printf("%s",getcwd(cwd, size));
    printf("> ");
    fgets(input_buf, 49, stdin);
    input_buf[strlen(input_buf)-1] = '\0';

    //copy the input into cmdToiInput
    char* cmdToInput = strdup(input_buf);

    //turns input to tokens
    char* tmp_ptr;

    tmp_ptr = strtok(input_buf, " \t");
    int i = 0;

    while (tmp_ptr != NULL) {
        cmd_ptr_array[i] = strdup(tmp_ptr);
        tmp_ptr = strtok(NULL, " \t");
        i++;

    }

    cmd_ptr_array[i] = NULL;


    //checks if user wants to exit
    while (strcmp(cmdToInput, "exit")!=0){

        if (recall == false) {

            //if it is your first command
            if (numberOfCommands == 0) {
                //adds command as head of the list
                historyList = listInsertHead(historyList, cmdToInput);
                //keeps count of number of commands
                numberOfCommands++;
            } else {

                //if the cmd is not equal to the previous one
                if (strcmp(cmdToInput, listGet(historyList, numberOfCommands)) != 0) {

                    //insert command to the end of the list
                    historyList = listInsertTail(historyList, cmdToInput);
                    numberOfCommands++;
                }
            }
        }

        else{
            listRemoveN(historyList, numberOfCommands);
            numberOfCommands--;

            if (strcmp(cmdToInput, listGet(historyList, numberOfCommands)) != 0) {

                //insert command to the end of the list
                historyList = listInsertTail(historyList, cmdToInput);
                numberOfCommands++;
            }
            recall = false;
        }


        if (cmd_ptr_array[0] != NULL) {
            if (strcmp(cmd_ptr_array[0], "history") == 0) {

                if (cmd_ptr_array[1] == NULL) {
                    numOfCmds = numberOfCommands;
                } else {
                    numOfCmds = atoi(cmd_ptr_array[1]);

                    if (numOfCmds > numberOfCommands){
                        numOfCmds = numberOfCommands;
                    }
                }
                for (int i = numOfCmds; i > 0; i--) {
                    printf("%d ", i);
                    listPrintN(historyList, numberOfCommands - i + 1);
                    printf("\n");
                }
            }
            else if (strcmp(cmd_ptr_array[0], "recall") == 0 && cmd_ptr_array[1] != NULL) {

                recall = true;

                cmdIndex = atoi(cmd_ptr_array[1]);

                if (cmdIndex > numberOfCommands) {
                    printf("%s\n", "Can't Recall: You didn't enter that many commands yet.");
                } else {
                    listPrintN(historyList, cmdIndex);
                    printf("\n");
                }

            }
            else if (strcmp(cmd_ptr_array[0], "cd") == 0 && cmd_ptr_array[1] != NULL) {
                if (strcmp(cmd_ptr_array[1], "~") == 0) {
                    status = chdir(getenv("HOME"));
                } else {
                    status = chdir(cmd_ptr_array[1]);
                }
            }


            //external command
            else {
                pid_t ret_val;

                ret_val = fork();
                if (ret_val != 0) {
                    wait(&status);
                } else {
                    status = execvp(cmd_ptr_array[0], cmd_ptr_array);


                }

            }
        }

        if (status == -1){
            printf("%s", "Command Not Valid\n");
        }

        status = 0;

        if (recall == false) {
            printf(getcwd(cwd, size));
            printf("> ");
            fgets(input_buf, 49, stdin);
            input_buf[strlen(input_buf)-1] = '\0';
            cmdToInput = strdup(input_buf);

            tmp_ptr = strtok(input_buf, " \t");
            int i = 0;

            while (tmp_ptr != NULL) {
                cmd_ptr_array[i] = strdup(tmp_ptr);
                tmp_ptr = strtok(NULL, " \t");
                i++;

            }

            cmd_ptr_array[i] = NULL;

        }

        else{

            cmdToInput = strdup(listGet(historyList, cmdIndex));

            tmp_ptr = strtok(cmdToInput, " \t");
            int i = 0;

            while (tmp_ptr != NULL) {
                cmd_ptr_array[i] = strdup(tmp_ptr);
                tmp_ptr = strtok(NULL, " \t");
                i++;

            }

            cmd_ptr_array[i] = NULL;

        }


    }

    printf("%s\n", "Terminating afsh...");

    free(historyList);


    return 0;

}

