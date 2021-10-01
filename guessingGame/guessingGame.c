/*  CS2600 Number Guessing Game
    Alexander Rodriguez
    9/30/21

This program will allow a user to play a guessing game. It will
prompt the user with a menu to play the game, change the range
of values, or exit the program. */


#include <stdio.h>
#include <stdlib.h>
#include <time.h>

char playGame(long maxNum, int randNum);
char changeMaxNum(long *maxNumber, FILE *file);

int main() {
    int userChoice;
    time_t t;
    int randNum;
    long maxNum;
    char again;
    char validate;
    FILE *file;
    long *ptr = &maxNum;

    if(file = fopen("max_number.txt", "r")){
        fscanf(file, "%ld", &maxNum);
        fclose(file);
    } else {
        maxNum = 10;
    }

    do{
        // Display menu options 1-3 & prompt user for option
        printf("\nPress 1 to play a game\nPress 2 to change the max number\nPress 3 to quit\n");
        validate = scanf("%d", &userChoice) ? 'Y' : 'N';
        
        if(validate == 'N'){    // User selects non-numeric menu option
            getchar();
            again = 'y';
        }

        if(userChoice == 1){    // If user selects option 1
            // Randomly generate number
            srand((unsigned) time(&t));
            randNum = ((rand()%maxNum+1));
            again = playGame(maxNum, randNum);

        } else if (userChoice == 2){    // If user selects option 2

            again = changeMaxNum(ptr, file);

        } else if (userChoice == 3) {    // If user selects option 3
            // Display exit prompt and quit program
            printf("\nExiting program.\n");
            return 0;

        } else {    // User selects invalid integer
            printf("\nInvalid option!\n");
            again = 'y';
        }
    } while(again == 'y');
}


/*
This function is used to play the guessing game. It prompts the user to guess
a number, letting the user know if it is too low or too high and checks for
input validation.

Arguments: long maxNum, int randNum
Returns: char 'y'
*/
char playGame(long maxNum, int randNum){
    char validate;
    int userGuess;
    char temp;
    char loop = 'n';
    
    do {
    // Prompt user to guess a number
    printf("Guess the number 1 - %ld ('q' to exit): ", maxNum);

    validate = scanf("%d", &userGuess) ? 'Y' : 'N';
    temp = getchar();
    
        if(validate == 'N') {   // user did not enter an integer
            if (temp == 'q'){    // if user enters 'q' return 'y'
                return 'y';
            } else{     
                printf("\nPlease enter a numeric value only!\n");
                loop = 'y';
            }
        }else {
            if(userGuess > randNum) {    // if too high tell user and guess again
                printf("\nIncorrect, you guessed too high.\n");
                loop = 'y';
            } else if (userGuess < randNum) {    // if too low tell user and guess again
                printf("\nIncorrect, you guessed too low.\n");
                loop = 'y';
            } else {    // if guess is correct tell user and return 'y'
                printf("\nYou correctly guessed the random number, %d!\n", randNum);
                return 'y';
            }
        }
    } while( loop == 'y');
}

/*
This function is used to change the max number for the guessing game. It will prompt
the user to enter a value between 1 and the max value of the random number generator.

Arguments: long* maxNumber
Returns: char 'y'
*/
char changeMaxNum(long *maxNumber, FILE *file){
    char validate;
    char loop = 'n';
    long maxNum = *maxNumber;

    do {
        if(file = fopen("max_number.txt", "r")){
            fscanf(file, "%ld", &maxNum);
            fclose(file);
        }

        // Prompt user to enter a number greater than 0 and less than max
        printf("\nPlease enter a new maximum value bewtween 1 - %d: ", RAND_MAX);
        validate = scanf("%ld", &maxNum) ? 'Y' : 'N';
        if(validate == 'N'){
            printf("\nInvalid input!\n");
            getchar();
            loop = 'y';
        } else if (maxNum < 1) {    // If user inputs number less than 1
            printf("\nPlease choose a max number greater than 0!\n");
            loop = 'y';
        } else if (maxNum > RAND_MAX) { // If user enters number greater than max possible random value
            printf("\nPlease choose a max number less than %d!\n", RAND_MAX);
            loop = 'y';
        } else { // If user inputs valid interger
            file = fopen("max_number.txt", "w+");
            if(file == NULL){   // check to see if file was made
                printf("\nError, could not save max value to file.\n");
            } else {        // if file sucessfully made write new max to file
                fprintf(file, "%ld\n", maxNum);
            }

            fclose(file);
            printf("New maximum value is now %ld\n", maxNum);
            *maxNumber = maxNum;
            return 'y';
        }
    } while(loop == 'y');
}