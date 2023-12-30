#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void menu()
{
    printf("*******************************\n");
    printf("*********1. guess numbers *****\n");
    printf("*********0. quit          *****\n");
    printf("*******************************\n");
}

void game()
{
    int random = rand() % 100 + 1;
    int guess = 0;
    while (1)
    {
        printf("please guess the number:\n");
        scanf("%d", &guess);
        if (guess < random)
        {
            printf("smaller!!!\n");
        }
        else if (guess > random)
        {
            printf("bigger!!!\n");
        }
        else
        {
            printf("you`re right!!!!\n");
            break;
        }
    }
}

int main()
{
    int input = 0;
    srand((unsigned int)time(NULL));
    do
    {
        menu();
        printf("please select:\n");
        scanf("%d", &input);
        switch (input)
        {
        case 1:
            game();
            break;

        case 0:
            printf("exit!");
            break;

        default:
            printf("wrong selection, please reselect.\n");
            break;
        }
    } while (input != 0);
}