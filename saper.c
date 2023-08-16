#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define ROWS 11
#define COLS 11
#define MINES 10

void initializeBoard(int board[ROWS][COLS], int revealed[ROWS][COLS])
{
    int i, j;

    // Initialize all cells to be un-revealed and contain no mines
    for (i = 0; i < ROWS; i++) {
        for (j = 0; j < COLS; j++) {
            board[i][j] = 0;
            revealed[i][j] = 0;
        }
    }
}

void placeMines(int board[ROWS][COLS])
{
    int i, row, col;

    // Place mines in random locations on the board
    for (i = 0; i < MINES; i++) {
        row = rand() % ROWS;
        col = rand() % COLS;
        if (board[row][col] != -1) {
            board[row][col] = -1;
        }
        else {
            i--;
        }
    }
}

void calculateNumbers(int board[ROWS][COLS])
{
    int i, j, row, col;

    // Calculate the number of adjacent mines for each cell on the board
    for (i = 0; i < ROWS; i++) {
        for (j = 0; j < COLS; j++) {
            if (board[i][j] != -1) {
                int count = 0;
                for (row = i - 1; row <= i + 1; row++) {
                    for (col = j - 1; col <= j + 1; col++) {
                        if (row >= 0 && row < ROWS && col >= 0 && col < COLS && board[row][col] == -1) {
                            count++;
                        }
                    }
                }
                board[i][j] = count;
            }
        }
    }
}

void clearScreen() {
    int i;
    for (i = 0; i < 20; i++) {
        printf("\n");
    }
}

void baner() {
    clearScreen();
    printf(" _______  _______  _______  _______  ______   \n");
    printf("|       ||   _   ||       ||       ||    _ |  \n");
    printf("|  _____||  |_|  ||    _  ||    ___||   | ||  \n");
    printf("| |_____ |       ||   |_| ||   |___ |   |_||_ \n");
    printf("|_____  ||       ||    ___||    ___||    __  |\n");
    printf(" _____| ||   _   ||   |    |   |___ |   |  | |\n");
    printf("|_______||__| |__||___|    |_______||___|  |_|\n");
}

void printBoard(int board[ROWS][COLS], int revealed[ROWS][COLS], int end)
{
    baner();
    int i, j;
    if (end == 0) {
        // Print the board, revealing cells that have been revealed
        printf("  ");
        for (j = 0; j < COLS; j++) {
            printf("%d ", j);
        }
        printf("\n");
        for (i = 0; i < ROWS; i++) {
            printf("%d ", i);
            for (j = 0; j < COLS; j++) {
                if (revealed[i][j] == 0) {
                    printf(". ");
                }
                else if (revealed[i][j] == 1){
                    printf("%d ", board[i][j]);
                }
                else if (revealed[i][j] == 2) {
                    printf("F ");
                }

            }
            printf("\n");
        }
    }
    else {
        printf("  ");
        for (j = 0; j < COLS; j++) {
            printf("%d ", j);
        }
        printf("\n");
        for (i = 0; i < ROWS; i++) {
            printf("%d ", i);
            for (j = 0; j < COLS; j++) {
                if (board[i][j] == -1)
                {
                    printf("B ");
                }
                else
                {
                    printf("%d ", board[i][j]);
                }
            }
            printf("\n");
        }
    }
    
}

void revealCell(int board[ROWS][COLS], int revealed[ROWS][COLS], int row, int col)
{
    // Reveal a cell on the board
    revealed[row][col] = 1;
    if (board[row][col] == 0) {
        int i, j;
        for (i = row - 1; i <= row + 1; i++) {
            for (j = col - 1; j <= col + 1; j++) {
                if (i >= 0 && i < ROWS && j >= 0 && j < COLS && revealed[i][j] == 0) {
                    revealCell(board, revealed, i, j);
                }
            }
        }
    }
}

int checkWin(int board[ROWS][COLS], int revealed[ROWS][COLS])
{
    int i, j;
    // Check if all non-mine cells have been revealed
    for (i = 0; i < ROWS; i++) {
        for (j = 0; j < COLS; j++) {
            if (board[i][j] != -1 && revealed[i][j] == 0) {
                return 0;
            }
        }
    }
    return 1;
}

void You_Win() {
    printf(" __   __  _______  __   __    _     _  ___   __    _  __   __  \n");
    printf("|  | |  ||       ||  | |  |  | | _ | ||   | |  |  | ||  | |  | \n");
    printf("|  |_|  ||   _   ||  | |  |  | || || ||   | |   |_| ||  | |  | \n");
    printf("|       ||  | |  ||  |_|  |  |       ||   | |       ||  | |  | \n");
    printf("|_     _||  |_|  ||       |  |       ||   | |  _    ||__| |__| \n");
    printf("  |   |  |       ||       |  |   _   ||   | | | |   | __   __  \n");
    printf("  |___|  |_______||_______|  |__| |__||___| |_|  |__||__| |__| \n");
}

void You_Lose() {
    printf("     __   __  _______  __   __    ___      _______  _______  _______  __        \n");
    printf("    |  | |  ||       ||  | |  |  |   |    |       ||       ||       ||  |       \n");
    printf("    |  |_|  ||   _   ||  | |  |  |   |    |   _   ||  _____||    ___||  |       \n");
    printf("    |       ||  | |  ||  |_|  |  |   |    |  | |  || |_____ |   |___ |  |       \n");
    printf("    |_     _||  |_|  ||       |  |   |___ |  |_|  ||_____  ||    ___||__|       \n");
    printf("      |   |  |       ||       |  |       ||       | _____| ||   |___  __        \n");
    printf("      |___|  |_______||_______|  |_______||_______||_______||_______||__|       \n");
    printf(" _______  _______  __   __  _______    _______  __   __  _______  ______    __  \n");
    printf("|       ||   _   ||  |_|  ||       |  |       ||  | |  ||       ||    _ |  |  | \n");
    printf("|    ___||  |_|  ||       ||    ___|  |   _   ||  |_|  ||    ___||   | ||  |  | \n");
    printf("|   | __ |       ||       ||   |___   |  | |  ||       ||   |___ |   |_||_ |  | \n");
    printf("|   ||  ||       ||       ||    ___|  |  |_|  ||       ||    ___||    __  ||__| \n");
    printf("|   |_| ||   _   || ||_|| ||   |___   |       | |     | |   |___ |   |  | | __  \n");
    printf("|_______||__| |__||_|   |_||_______|  |_______|  |___|  |_______||___|  |_||__| \n");
}

void firstMove(int board[ROWS][COLS], int revealed[ROWS][COLS]) {
    int row, col;
    printBoard(board, revealed, 0);
    printf("Enter row and column: ");
    scanf("%d %d", &row, &col);
    while (board[row][col] != 0)
    {
        initializeBoard(board, revealed);
        placeMines(board);
        calculateNumbers(board);
    }
    revealCell(board, revealed, row, col);

}

void playGame()
{
    int board[ROWS][COLS];
    int revealed[ROWS][COLS];
    initializeBoard(board, revealed);
    placeMines(board);
    calculateNumbers(board);
    int row, col;
    int gameOver = 0;
    //int type;
    char type1;
    firstMove(board, revealed);  // Ensuring not to lose on the first move
    // Loop until the game is over
    while (!gameOver) {
        printBoard(board, revealed, gameOver);
        //printf("Enter 0-shoot , 1-flag: \n");
        //scanf("%d", &type);
        printf("f - flag, s - shoot:  ");
        scanf(" %c", &type1);
        printf("Enter row and column: ");
        scanf("%d %d", &row, &col);
        if (type1 == 's')
        {
            if (revealed[row][col] != 2)
            {
                if (board[row][col] == -1) {
                    clearScreen();
                    revealed[row][col] = 1;
                    gameOver = 1;
                    printBoard(board, revealed, gameOver);
                    You_Lose();
                }
                else {
                    revealCell(board, revealed, row, col);
                    if (checkWin(board, revealed)) {
                        clearScreen();
                        gameOver = 1;
                        printBoard(board, revealed, gameOver);
                        You_Win();
                    }
                }
            }
        }
        else if (type1=='f')
            revealed[row][col] = 2;
        //do dodania odflagowywanie
    }
}

int main()
{
    srand(time(NULL)); // Initialize random number generator

    playGame();

    return 0;
}
