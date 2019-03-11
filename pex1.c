#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <stdbool.h>
#include <values.h>
#include "historyList.h"

/*=============================================================================
 |   Assignment:  PEX1
 |       Author:  Tricia Dang
 |      Section:  M3
 |        Class:  CS483
 +-----------------------------------------------------------------------------
 |   Description:  Create a command prompt with functionalities of cd,
 |                  recall, history, exit, and all other functions
 |                  are executed through a fork and exec.
 |
 |   Required Features Not Included:  DESCRIBE HERE ANY REQUIREMENTS OF
 |      THE ASSIGNMENT THAT THE PROGRAM DOES NOT ATTEMPT TO SOLVE.
 |
 |   Known Bugs:  IF THE PROGRAM DOES NOT FUNCTION CORRECTLY IN SOME
 |      SITUATIONS, DESCRIBE THE SITUATIONS AND PROBLEMS HERE.
 +-----------------------------------------------------------------------------
 |   Documentation Statement:  https://www.tutorialspoint.com/c_standard_library/
 |  c_function_strtol.htm was used to figure out to use strtol function. C2C
 |  Nicholas Baietto helped me figure out how to implement cd ~ by attaching the
 |  home path to the end of the rest of the string. He also helped me figure out what
 |  was wrong with my print cwd and told me to use the MAX_PATH as the size.
 |  https://www.codingame.com/playgrounds/14213/how-to-play-with-strings-in-c/string-split
 |  was used to figure out how to split the string.
 *===========================================================================*/

int main() {

    //initialize variables

    //current working directory
    char cwd[PATH_MAX];
    char* currentWD;

    //your input buf
    char input_buf[50];

    //the array of your command
    char* cmd_ptr_array[20];

    //says if the exec was valid
    int status = 0;

    //number of commands requested by the user in history or recall
    int numOfCmds = 0;

    //the index of the command that people want
    int cmdIndex = 0;

    //keeps track of number of commands inputted excluding same commands
    int numberOfCommands = 0;

    //for the strtol capability
    char* ptr;



    //linked list of all commands
    HistoryNodeType* historyList = malloc(sizeof(HistoryNodeType));

    //keeps track if recalled was called in the prev command
    bool recall = false;

    //says if you should perform the default exec
    bool performDefaultExec = true;


    //Print Air Force Shell and Current Working Directory
    printf("%s\n\n", "...Air Force Shell (afsh)...");
    currentWD = getcwd(cwd, PATH_MAX);
    printf("%s",currentWD);
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

        printf("token - %s\n", tmp_ptr);
        tmp_ptr = strtok(NULL, " \t");
        i++;

    }

    cmd_ptr_array[i] = NULL;


    //checks if user wants to exit
    while (strcmp(cmdToInput, "exit")!=0){

        //if recall was called in the last command, remove it from the history list and decrease number of commands
        if (recall == true) {
            //remove the recall command from the list
            listRemoveN(historyList, numberOfCommands);
            numberOfCommands--;
            recall = false;
        }


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

        //if the first part of the command is not null
        if (cmd_ptr_array[0] != NULL) {

            //implements the history command
            if (strcmp(cmd_ptr_array[0], "history") == 0) {

                //takes care of the case history n where n is equal to 0
                if (cmd_ptr_array[1] == NULL) {
                    numOfCmds = numberOfCommands;
                }

                else {
                    //history n - converts n to an integer
                    numOfCmds = strtol(cmd_ptr_array[1], ptr, 10);
                }

                //checks if n is actually an integer
                if (numOfCmds != 0){

                    //if a user inputs an n that is greater than the number of commands, just sets the command
                    //that the user wants to the number of commands you have
                    if (numOfCmds > numberOfCommands) {
                        numOfCmds = numberOfCommands;
                    }

                    //actually lists the commands
                    for (int i = numOfCmds; i > 0; i--) {
                        printf("%d ", i);
                        listPrintN(historyList, numberOfCommands - i + 1);
                        printf("\n");
                    }

                    //says to not perform the fork and execution
                    performDefaultExec = false;
                }
            }

            //implements the recall command
            else if (strcmp(cmd_ptr_array[0], "recall") == 0) {
                char* ptr;
                long ret;

                //if recall n where n is not blank
                if (cmd_ptr_array[1] != NULL) {
                    recall = true;


                    //converts the number you want to an integer
                    cmdIndex = strtol(cmd_ptr_array[1], ptr, 10);


                    //checks if n is actually an integer
                    if (cmdIndex != 0){

                        //if you try to recall a bigger number than you have commands
                        if (cmdIndex > numberOfCommands) {
                            printf("%s\n", "Can't Recall: You didn't enter that many commands yet.");
                        }

                        //prints out the list index
                        else {
                            listPrintN(historyList, cmdIndex);
                            printf("\n");
                        }

                        //says not to perform the fork and exec
                        performDefaultExec = false;
                    }
                }


            }

            //implements cd command
            else if (strcmp(cmd_ptr_array[0], "cd") == 0) {

                //if there is a second argument
                if (cmd_ptr_array[1] != NULL) {

                    //if the first character of the second argument is a ~
                    if (strncmp(&cmd_ptr_array[1][0], "~", 1) == 0){

                        //character to split the string
                        char delim[] = "~";

                        //splits the string on the ~
                        char* newStr = strdup(cmd_ptr_array[1]);

                        char *cutStr = strtok(newStr, delim);

                        //deals with just the squiggle
                        if (cutStr == NULL){
                            cutStr = "";
                        }

                        //adds path to HOME to the split string
                        cutStr = strcat(getenv("HOME"),cutStr);

                        //changes directory to that path
                        chdir(cutStr);

                    }

                    else
                        {
                        //changes directory to whatever was the first argument
                        status = chdir(cmd_ptr_array[1]);
                    }
                    performDefaultExec = false;
                }
            }


            //external command
            if (performDefaultExec) {
                pid_t ret_val;

                ret_val = fork();
                if (ret_val != 0) {
                    wait(&status);
                } else {
                    status = execvp(cmd_ptr_array[0], cmd_ptr_array);


                }
            }
        }

        //if the command was not successfully executed
        if (status == -1){
            printf("%s", "Command Not Valid\n");
        }

        //reset the status
        status = 0;

        //reset the performDefaultExec
        performDefaultExec = true;

        //if you are not in the recall or the exec was not successful
        if (recall == false || status == -1) {

            //repeat beginning prompt
            currentWD = strdup(getcwd(cwd, PATH_MAX));
            printf("%s",currentWD);
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

            //otherwise gets the command from the history list
            cmdToInput = strdup(listGet(historyList, cmdIndex));

            //changes it to tokens in order to implement like usual
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

