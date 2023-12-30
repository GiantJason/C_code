#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct
{
    int rows;
    int cols;
} Size;

typedef struct
{
    char **board;
    char **hiddenBoard;
    Size size;
    int mines;
} MinesweeperGame;

void initializeGame(MinesweeperGame *game, int rows, int cols, int mines);
void printBoard(MinesweeperGame *game);
int countAdjacentMines(MinesweeperGame *game, int row, int col);
void revealBoard(MinesweeperGame *game, int row, int col);
int isGameWon(MinesweeperGame *game);
void freeGameMemory(MinesweeperGame *game);

int main()
{
    MinesweeperGame game;
    initializeGame(&game, 10, 10, 15);
    printBoard(&game);

    int row, col;

    while (1)
    {
        printf("Enter row and column (e.g., 1 2): ");
        scanf("%d %d", &row, &col);

        if (row < 1 || row > game.size.rows || col < 1 || col > game.size.cols)
        {
            printf("Invalid input. Try again.\n");
            continue;
        }

        if (game.hiddenBoard[row - 1][col - 1] == 'X')
        {
            printf("Game Over! You hit a mine.\n");
            break;
        }

        revealBoard(&game, row - 1, col - 1);
        printBoard(&game);

        if (isGameWon(&game))
        {
            printf("Congratulations! You won!\n");
            break;
        }
    }

    freeGameMemory(&game);

    return 0;
}

void initializeGame(MinesweeperGame *game, int rows, int cols, int mines)
{
    int i, j;

    game->size.rows = rows;
    game->size.cols = cols;
    game->mines = mines;

    // Allocate memory for the boards
    game->board = (char **)malloc(rows * sizeof(char *));
    game->hiddenBoard = (char **)malloc(rows * sizeof(char *));

    for (i = 0; i < rows; i++)
    {
        game->board[i] = (char *)malloc(cols * sizeof(char));
        game->hiddenBoard[i] = (char *)malloc(cols * sizeof(char));

        for (j = 0; j < cols; j++)
        {
            game->board[i][j] = '-';
            game->hiddenBoard[i][j] = ' ';
        }
    }

    // Place mines randomly
    srand(time(NULL));
    for (i = 0; i < mines; i++)
    {
        int row, col;
        do
        {
            row = rand() % rows;
            col = rand() % cols;
        } while (game->hiddenBoard[row][col] == 'X');
        game->hiddenBoard[row][col] = 'X';
    }
}

// void printBoard(MinesweeperGame *game) {
//     int i, j;
//     int rowWidth = snprintf(NULL, 0, "%d", game->size.rows);

//     printf("\n  ");
//     for (i = 1; i <= game->size.cols; i++) {
//         printf("%*d ", rowWidth, i);
//     }
//     printf("\n");

//     for (i = 0; i < game->size.rows; i++) {
//         printf("%*d ", rowWidth, i + 1);
//         for (j = 0; j < game->size.cols; j++) {
//             printf("%c ", game->board[i][j]);
//         }
//         printf("\n");
//     }
// }
void printBoard(MinesweeperGame *game)
{
    int i, j;
    int rowWidth = snprintf(NULL, 0, "%d", game->size.rows);

    printf("\n%*s", rowWidth + 1, ""); // Print an extra space for alignment
    for (i = 1; i <= game->size.cols; i++)
    {
        printf("%d ", i);
    }
    printf("\n");

    for (i = 0; i < game->size.rows; i++)
    {
        printf("%*d ", rowWidth, i + 1);
        for (j = 0; j < game->size.cols; j++)
        {
            printf("%c ", game->board[i][j]);
        }
        printf("\n");
    }
}

int countAdjacentMines(MinesweeperGame *game, int row, int col)
{
    int count = 0;
    int i, j;

    for (i = row - 1; i <= row + 1; i++)
    {
        for (j = col - 1; j <= col + 1; j++)
        {
            if (i >= 0 && i < game->size.rows && j >= 0 && j < game->size.cols && game->hiddenBoard[i][j] == 'X')
            {
                count++;
            }
        }
    }

    return count;
}

void revealBoard(MinesweeperGame *game, int row, int col)
{
    if (game->board[row][col] != '-')
    {
        return;
    }

    int mines = countAdjacentMines(game, row, col);
    if (mines > 0)
    {
        game->board[row][col] = mines + '0';
    }
    else
    {
        game->board[row][col] = ' ';
        int i, j;
        for (i = row - 1; i <= row + 1; i++)
        {
            for (j = col - 1; j <= col + 1; j++)
            {
                if (i >= 0 && i < game->size.rows && j >= 0 && j < game->size.cols)
                {
                    revealBoard(game, i, j);
                }
            }
        }
    }
    // Check if the surrounding numbers match the number of mines
    int count = 0;
    for (int i = row - 1; i <= row + 1; i++)
    {
        for (int j = col - 1; j <= col + 1; j++)
        {
            if (i >= 0 && i < game->size.rows && j >= 0 && j < game->size.cols)
            {
                if (game->board[i][j] == '-')
                {
                    count++;
                }
            }
        }
    }

    if (count == mines)
    {
        for (int i = row - 1; i <= row + 1; i++)
        {
            for (int j = col - 1; j <= col + 1; j++)
            {
                if (i >= 0 && i < game->size.rows && j >= 0 && j < game->size.cols)
                {
                    if (game->board[i][j] == '-')
                    {
                        game->board[i][j] = 'X';
                    }
                }
            }
        }
    }
}

int isGameWon(MinesweeperGame *game)
{
    int i, j;

    for (i = 0; i < game->size.rows; i++)
    {
        for (j = 0; j < game->size.cols; j++)
        {
            if (game->board[i][j] == '-' && game->hiddenBoard[i][j] != 'X')
            {
                return 0; // Game is not won yet
            }
        }
    }

    return 1; // All safe cells are revealed
}

void freeGameMemory(MinesweeperGame *game)
{
    int i;

    // Free memory for the boards
    for (i = 0; i < game->size.rows; i++)
    {
        free(game->board[i]);
        free(game->hiddenBoard[i]);
    }

    free(game->board);
    free(game->hiddenBoard);
}
