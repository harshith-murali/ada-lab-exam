/* ================================================================ */
/* N-QUEENS PROBLEM - BACKTRACKING */
/* ================================================================ */

/*
Algorithm name: n-Queens Backtracking
Problem it solves:
Places n queens on an n by n chessboard so that no two queens attack each other.
Time complexity: O(n!)
Space complexity: O(n)
*/

#include <stdio.h>

#define MAX_N 10

/* Returns 1 if a queen can be placed at row, col. */
int isSafe(const int queens[], int row, int col) {
    for (int previousRow = 0; previousRow < row; previousRow++) {
        int previousCol = queens[previousRow];
        if (previousCol == col ||
            previousCol - previousRow == col - row ||
            previousCol + previousRow == col + row) {
            return 0;
        }
    }
    return 1;
}

/* Recursively places queens row by row and stops at first solution. */
int solveNQueens(int n, int row, int queens[]) {
    if (row == n) {
        return 1;
    }

    for (int col = 0; col < n; col++) {
        if (isSafe(queens, row, col)) {
            queens[row] = col;
            if (solveNQueens(n, row + 1, queens)) {
                return 1;
            }
        }
    }
    return 0;
}

/* Prints a board using Q for queens. */
void printBoard(int n, const int queens[]) {
    for (int row = 0; row < n; row++) {
        for (int col = 0; col < n; col++) {
            printf("%c ", queens[row] == col ? 'Q' : '.');
        }
        printf("\n");
    }
}

/* Runs one n-Queens test. */
void runTest(int n) {
    int queens[MAX_N];
    for (int i = 0; i < n; i++) {
        queens[i] = -1;
    }

    printf("n = %d\n", n);
    if (solveNQueens(n, 0, queens)) {
        printf("One solution:\n");
        printBoard(n, queens);
    } else {
        printf("No solution exists.\n");
    }
    printf("\n");
}

int main(void) {
    printf("n-Queens Backtracking\n\n");
    runTest(4);
    runTest(5);
    runTest(3);
    return 0;
}

/*
High-level idea:
The board is filled one row at a time.
For each row, the algorithm tries every column that is not attacked by earlier
queens.
If later rows become impossible, it backtracks and tries a different column.
For n = 4, the first successful arrangement puts queens in columns 1, 3, 0,
and 2 for rows 0 through 3.
*/
