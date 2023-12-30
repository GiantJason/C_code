#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define SIZE 10
#define MINES 15

void initializeBoard(char board[SIZE][SIZE], char hiddenBoard[SIZE][SIZE]);
void printBoard(char board[SIZE][SIZE]);
int countAdjacentMines(int row, int col, char hiddenBoard[SIZE][SIZE]);
void revealBoard(char board[SIZE][SIZE], char hiddenBoard[SIZE][SIZE], int row, int col);
void revealMines(char board[SIZE][SIZE], char hiddenBoard[SIZE][SIZE]);
int isGameWon(char board[SIZE][SIZE], char hiddenBoard[SIZE][SIZE]);

int main()
{
    char board[SIZE][SIZE];
    char hiddenBoard[SIZE][SIZE];

    initializeBoard(board, hiddenBoard);
    printBoard(board);

    int row, col, found = 0;

    while (1)
    {
        printf("Enter row and column (e.g., 1 2): ");
        scanf("%d %d", &row, &col);

        if (row < 1 || row > SIZE || col < 1 || col > SIZE)
        {
            printf("Invalid input. Try again.\n");
            continue;
        }

        if (hiddenBoard[row - 1][col - 1] == 'X')
        {
            printf("Game Over! You hit a mine.\n");
            continue;
        }

        revealBoard(board, hiddenBoard, row - 1, col - 1);
        revealMines(board, hiddenBoard);
        printBoard(board);
        printf("Mines remaining: %d\n", (MINES - found));

        if (isGameWon(board, hiddenBoard))
        {
            printf("Congratulations! You won!\n");
            break;
        }
    }

    return 0;
}

void initializeBoard(char board[SIZE][SIZE], char hiddenBoard[SIZE][SIZE])
{
    int i, j;

    // Initialize the boards
    for (i = 0; i < SIZE; i++)
    {
        for (j = 0; j < SIZE; j++)
        {
            board[i][j] = '-';
            hiddenBoard[i][j] = ' ';
        }
    }

    // Place mines randomly
    srand(time(NULL));
    for (i = 0; i < MINES; i++)
    {
        int row, col;
        do
        {
            row = rand() % SIZE;
            col = rand() % SIZE;
        } while (hiddenBoard[row][col] == 'X');
        hiddenBoard[row][col] = 'X';
    }
}

void printBoard(char board[SIZE][SIZE])
{
    int i, j;

    printf("\n\t");
    for (i = 1; i <= SIZE; i++)
    {
        printf("%d\t", i);
    }
    printf("\n");

    for (i = 0; i < SIZE; i++)
    {
        printf("%d\t", i + 1);
        for (j = 0; j < SIZE; j++)
        {
            printf("%c\t", board[i][j]);
        }
        printf("\n");
    }
}

int countAdjacentMines(int row, int col, char hiddenBoard[SIZE][SIZE])
{
    int count = 0;
    int i, j;

    for (i = row - 1; i <= row + 1; i++)
    {
        for (j = col - 1; j <= col + 1; j++)
        {
            if (i >= 0 && i < SIZE && j >= 0 && j < SIZE && hiddenBoard[i][j] == 'X')
            {
                count++;
            }
        }
    }

    return count;
}

void revealBoard(char board[SIZE][SIZE], char hiddenBoard[SIZE][SIZE], int row, int col)
{
    if (board[row][col] != '-')
    {
        // printf("Please choose the valid row & column numbers!");
        return;
    }

    int mines = countAdjacentMines(row, col, hiddenBoard);
    if (mines > 0)
    {
        board[row][col] = mines + '0';
    }
    else
    {
        board[row][col] = ' ';
        int i, j;
        for (i = row - 1; i <= row + 1; i++)
        {
            for (j = col - 1; j <= col + 1; j++)
            {
                if (i >= 0 && i < SIZE && j >= 0 && j < SIZE)
                {
                    revealBoard(board, hiddenBoard, i, j);
                }
            }
        }
    }
}
void revealMines(char board[SIZE][SIZE], char hiddenBoard[SIZE][SIZE])
{
    // Check if the surrounding numbers match the number of mines
    
    for (int a = 0; a < SIZE; a++)
    {
        for (int b = 0; b < SIZE; b++)
        {
            int count = 0;
            //make sure to process cells with a number 
            if (board[a][b] == '-' || board[a][b] == ' ')
            {
                continue;
            }
            int mines = board[a][b] - '0';
            for (int i = a - 1; i <= a + 1; i++)
            {
                for (int j = b - 1; j <= b + 1; j++)
                {
                    if (i >= 0 && i < SIZE && j >= 0 && j < SIZE)
                    {
                        if (board[i][j] == '-')
                        {
                            count++;
                        }
                        if(board[i][j] == 'X'){
                            mines--;
                        }
                    }
                }
            }
            if (count == mines)
            {
                for (int i = a - 1; i <= a + 1; i++)
                {
                    for (int j = b - 1; j <= b + 1; j++)
                    {
                        if (i >= 0 && i < SIZE && j >= 0 && j < SIZE)
                        {
                            if (board[i][j] == '-' && hiddenBoard[i][j] == 'X')
                            {
                                board[i][j] = 'X';
                                found += 1;
                            }else{
                                continue;
                            }
                        }
                    }
                }
            }
        }
    }
}

int isGameWon(char board[SIZE][SIZE], char hiddenBoard[SIZE][SIZE])
{
    int i, j;

    for (i = 0; i < SIZE; i++)
    {
        for (j = 0; j < SIZE; j++)
        {
            if (board[i][j] == '-' && hiddenBoard[i][j] != 'X')
            {
                return 0; // Game is not won yet
            }
        }
    }

    return 1; // All safe cells are revealed
}