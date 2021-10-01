/*  CS2600 Restaurant Bill
    Alexander Rodriguez
    9/30/21

Write a program that computes the tax and tip on a bill.
Program shold accept the tax and tip bot has percentages
from the command line. Display the meal cost, tax amount,
and total bill on screen. */

#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <ctype.h>

int main() {
    float tax = 0;
    float tip = 0;
    int mealChoice;
    float mealCost;
    char validation;
    char loop;
    time_t t;

    // Display menu items and prices
    printf("\nMenu Items:\n1. Salad: $9.95\n2. Soup: $4.55\n3. Sandwich: $13.25\n4. Pizza: $22.35\n\n");

    do{
        // Prompt user for tax amount
        printf("\nPlease enter tax amount (percentage): ");
        validation = scanf("%f",&tax) ? 'Y' : 'N';

        if(validation == 'N'){  // validate input; if incorrect loop again
            printf("\nInvalid input, try again.\n");
            getchar();
            loop = 'y';
        }else{
            loop = 'n';
        }
    } while (loop == 'y');

    do {
        // Prompt user for tip amount
        printf("\nPlease enter tip amount (percentage): ");
        validation = scanf("%f",&tip) ? 'Y' : 'N';

        if(validation == 'N'){  // validate input; if incorrect loop again
            printf("\nInvalid input, try again.\n");
            getchar();
            loop = 'y';
        }else{
            loop = 'n';
        }
    } while(loop == 'y');

    // Randomly choose between menu item 1-4
    srand((unsigned) time(&t));
    mealChoice = (rand()%4);
    
    switch(mealChoice) {
        case 0: mealCost = 9.95;
            break;
        case 1: mealCost = 4.55;
            break;
        case 2: mealCost = 13.25;
            break;
        case 3: mealCost = 22.35;
            break;
        default: printf("Error in meal choice.");
            break;
    }

    // Calculate meal cost, tax amount, tip amount, 
    // and total then display

    printf("\nMeal cost: $%.2f\nTax amount: $%.2f\nTip Amount: $%.2f\nTotal Bill: $%.2f\n", mealCost, mealCost*(tax/100), mealCost*(tip/100), mealCost+(mealCost*(tax/100))+(mealCost*(tip/100)));

    return 0;
}