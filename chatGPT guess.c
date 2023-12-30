#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void printWelcomeMenu() {
    printf("=== Number Guessing Game ===\n");
    printf("1. Start Game\n");
    printf("2. Quit\n");
    printf("===========================\n");
}

int main() {
    srand(time(NULL)); // Seed for random number generation
    int option;

    do {
        printWelcomeMenu();
        printf("Select an option: ");
        scanf("%d", &option);

        switch (option) {
            case 1:
                // Game logic
                {
                    int randomNumber = rand() % 100 + 1; // Generate a random number between 1 and 100

                    printf("\nWelcome to the Number Guessing Game!\n");
                    printf("Try to guess the number between 1 and 100.\n");

                    while (1) {
                        int userNumber;
                        char input[100];

                        printf("Enter your guess (or 'q' to quit): ");
                        scanf("%s", input);

                        if (input[0] == 'q' || input[0] == 'Q') {
                            printf("Quitting the game. The correct number was %d.\n", randomNumber);
                            break;
                        }

                        userNumber = atoi(input);

                        if (userNumber < 1 || userNumber > 100) {
                            printf("Please enter a number between 1 and 100.\n");
                            continue;
                        }

                        if (userNumber < randomNumber) {
                            printf("Smaller! Try again.\n");
                        } else if (userNumber > randomNumber) {
                            printf("Bigger! Try again.\n");
                        } else {
                            printf("Congratulations! You guessed the correct number: %d\n", randomNumber);
                            break;
                        }
                    }
                }
                break;

            case 2:
                printf("Quitting the game. Goodbye!\n");
                break;

            default:
                printf("Invalid option. Please choose a valid option.\n");
                break;
        }

    } while (option != 2);

    return 0;\
}
