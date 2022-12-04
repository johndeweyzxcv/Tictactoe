#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>
#include<unistd.h>

void start();
void welcome();
int checkWinner(int value, char character[10]);
void conclusion(int event);
int occupiedSpaces(char occupiedStage[10]);
void gameState(char theStage[10]);
int randomMoves();

int randomMoves() {
    int rand_num;
    srand(time(0));
    rand_num = rand() % 9 + 1;
    return rand_num;
    //This function generates random random numbers for the computer.
}

void gameState(char theStage[10]) {
    printf("      %c|%c|%c      \n      -----      \n      %c|%c|%c      \n      -----      \n      %c|%c|%c      \n\n",
    theStage[1], theStage[2], theStage[3], theStage[4], theStage[5], theStage[6], theStage[7], theStage[8], theStage[9]
    );
    //This function prints the current status of the board.
}

int occupiedSpaces(char occupiedStage[10]) {
    int occupied;
    for(int i=1; i<10; i++) {
        if(occupiedStage[i] == 'X' || occupiedStage[i] == 'O') {
            occupied += 1;
        }
        else {
            continue;
        }
    }
    return occupied;
    //This function returns occupied spaces in buffer stage, if all the buffer stage is filled up (9) then it is a stalemate
}

void conclusion(int event) {
    if(event == 1) {
        printf("\n>>>> CONGRATULATIONS, YOU WIN! <<<<\n"); exit(0);
    }
    if(event == 2) {
        printf("\nSorry you lose. Better luck next time... :(\n"); exit(0);
    }
    if(event == 3) {
        printf("STALEMATE!\n"); exit(0);
    }
    else {
        printf("PROGRAM PANIC, UNKNOWN ERROR...\n"); exit(0);
    }
    //This will handle all the exit point in the program, determines if win, lose or stalemate.
}

int checkWinner(int value, char character[10]) {
    char val;
    val = 'X';
    //Checks int value parameter if 1 then val = X, it will find X for possible winning combination, 0 for O.
    if(value == 1) {
        val = 'X';
    }
    if(value == 0) {
        val = 'O';
    }

    int h1, h2, h3, v1, v2, v3, d1, d2;
    //Horizontal, Vertical, and Diagonal boxes.

    h1 = character[1] == val && character[2] == val && character[3] == val;
    h2 = character[4] == val && character[5] == val && character[6] == val;
    h3 = character[7] == val && character[8] == val && character[9] == val;
    //If the first horizontal row is equal to the val then it is a winner.

    v1 = character[1] == val && character[4] == val && character[7] == val;
    v2 = character[2] == val && character[5] == val && character[8] == val;
    v3 = character[3] == val && character[6] == val && character[9] == val;
    //If the first vertical row is equal to the val then it is a winner.

    d1 = character[1] == val && character[5] == val && character[9] == val;
    d2 = character[3] == val && character[5] == val && character[7] == val;
    //If one of the boxes in diagonal is equal to the val then it is a winner.

    if(
        h1 == 1 || h2 == 1 || h3 == 1 ||
        v1 == 1 || v2 == 1 || v3 == 1 ||
        d1 == 1 || d2 == 1
    ) {
        return 1;
    } else {
        return 0;
    }
    //Check all possible winning combinations returns 1 if wins 0 if not.
}

void start() {
    char stage[10];
    int turn;
    for(int i=1; i<10; i++) { stage[i] = ' '; }
    //Create a buffer stage to store the game state.
    //Defines who makes a move, 1 for player and 0 for computer.
    //Populate the stage array with a blank.

    printf("Who goes first move (1-You, 0-Computer)?: ");
    scanf("%d", &turn);

    while(turn == 1 || turn == 0) {

        printf("\n   BOARD STATUS:\n");
        gameState(stage); //Printf the state of the board
        sleep(1);

        if(turn == 1) {
            int target, verify, container;
            //target - Get the input of user.
            //verify - verify the input of user if out of bounds.
            //container - checks if the selected input is occupied by either X or O.

            do {
                printf("You are now moving select a number (1 - 9): ");
                sleep(1);
                scanf("%d", &target);
                verify = target < 1 || target > 9;
                container = stage[target] == 'X' || stage[target] == 'O';
                if(verify == 1) {
                    printf("You are entering a number that is less than 1 or greater than 9.\n");
                }
                if(container == 1) {
                    printf("You are overriding a data already written on the buffer stage.\n");
                }
                else {
                    continue;
                }
            } while(verify == 1 || container == 1);
            //Will keep asking input from the user until the input is less than 1 or greater than 9.
            //Or if will try to overwrite a data that has been already written.

            printf("Writing to the buffer stage...\n");
            stage[target] = 'X';
            sleep(1);
            target = 0;
            turn = 0;
            //Writing to the buffer stage.

            printf("Checking if you win...\n");
            if(checkWinner(1, stage) == 1) {
                conclusion(1);
            }
            sleep(1);
            printf("Checking for stale mate; Occupied spaces: %d\n", occupiedSpaces(stage));
            sleep(1);
            if(occupiedSpaces(stage) > 8) {
                conclusion(3);
            }
            else {
                continue;
            }
            sleep(1);
            //Checks if the user made winning combinations based on checkWinner() function.

        }

        if(turn == 0) {
            int target, verify, container;
            //target - Get the input of user.
            //verify - verify the input of user if out of bounds.
            //container - checks if the selected input is occupied by either X or O.

            do {
                printf("Computer is moving and selecting a number (1 - 9): \n");
                sleep(1);
                target = randomMoves();
                verify = target < 1 || target > 9;
                container = stage[target] == 'X' || stage[target] == 'O';
                if(verify == 1) {
                    printf("Computer is trying to enter a number that is less than 1 or greater than 9...\n");
                }
                if(container == 1) {
                    printf("Computer is trying to override a data already written on the buffer stage...\n");
                }
                else {
                    continue;
                }
            }while(verify == 1 || container == 1);
            //Will keep asking input from the computer until the input is less than 1 or greater than 9.
            //Or if will try to overwrite a data that has been already written.

            printf("Writing to the buffer stage...\n");
            stage[target] = 'O';
            sleep(1);
            target = 0;
            turn = 1;
            //Writing to the buffer stage

            printf("Checking if the computer win.\n");
            if(checkWinner(0, stage) == 1) {
                conclusion(1);
            }
            sleep(1);
            printf("Checking for stale mate; Occupied spaces: %d\n", occupiedSpaces(stage));
            sleep(1);
            if(occupiedSpaces(stage) > 8) {
                conclusion(3);
            }
            else {
                continue;
            }
            sleep(1);
            //Checks if the computer made winning combinations based on checkWinner() function.
        }

        else {
            printf("PROGRAM PANIC, UNKNOWN ERROR...\n");
            exit(0);
        }

    }
}

void welcome() {
    printf("Welcome to TIC TAC TOE GAME.\n");
    printf("----------------------------\n\n");
    printf("The objective of this game is to get a line of X's\nbefore the computer gets a line of 0's. A line may\nbe across, down, or diagonal.\n\n");
    printf("The board is labeled from 1 to 9 as follows:\n\n");
    printf("      1|2|3      \n      -----      \n      4|5|6      \n      -----      \n      7|8|9      \n\n");
}

void main(void) {
    welcome();
    start();
}
