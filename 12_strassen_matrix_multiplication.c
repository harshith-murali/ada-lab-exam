/* ================================================================ */
/* STRASSEN'S MATRIX MULTIPLICATION */
/* ================================================================ */

/*
Algorithm name: Strassen's Matrix Multiplication
Problem it solves:
Multiplies two square matrices using seven recursive products instead of eight.
This demo uses power-of-two matrix sizes.
Time complexity: O(n^log2(7)) about O(n^2.807)
Space complexity: O(n^2 log n)
*/

#include <stdio.h>

#define MAX_N 4

/* Adds two n by n matrices. */
void addMatrix(int n, int a[MAX_N][MAX_N], int b[MAX_N][MAX_N],
               int result[MAX_N][MAX_N]) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            result[i][j] = a[i][j] + b[i][j];
        }
    }
}

/* Subtracts b from a. */
void subtractMatrix(int n, int a[MAX_N][MAX_N], int b[MAX_N][MAX_N],
                    int result[MAX_N][MAX_N]) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            result[i][j] = a[i][j] - b[i][j];
        }
    }
}

/* Multiplies matrices using Strassen recursion. */
void strassen(int n, int a[MAX_N][MAX_N], int b[MAX_N][MAX_N],
              int c[MAX_N][MAX_N]) {
    int a11[MAX_N][MAX_N] = {{0}}, a12[MAX_N][MAX_N] = {{0}};
    int a21[MAX_N][MAX_N] = {{0}}, a22[MAX_N][MAX_N] = {{0}};
    int b11[MAX_N][MAX_N] = {{0}}, b12[MAX_N][MAX_N] = {{0}};
    int b21[MAX_N][MAX_N] = {{0}}, b22[MAX_N][MAX_N] = {{0}};
    int m1[MAX_N][MAX_N] = {{0}}, m2[MAX_N][MAX_N] = {{0}};
    int m3[MAX_N][MAX_N] = {{0}}, m4[MAX_N][MAX_N] = {{0}};
    int m5[MAX_N][MAX_N] = {{0}}, m6[MAX_N][MAX_N] = {{0}};
    int m7[MAX_N][MAX_N] = {{0}};
    int t1[MAX_N][MAX_N] = {{0}}, t2[MAX_N][MAX_N] = {{0}};
    int half = n / 2;

    if (n == 1) {
        c[0][0] = a[0][0] * b[0][0];
        return;
    }

    for (int i = 0; i < half; i++) {
        for (int j = 0; j < half; j++) {
            a11[i][j] = a[i][j];
            a12[i][j] = a[i][j + half];
            a21[i][j] = a[i + half][j];
            a22[i][j] = a[i + half][j + half];
            b11[i][j] = b[i][j];
            b12[i][j] = b[i][j + half];
            b21[i][j] = b[i + half][j];
            b22[i][j] = b[i + half][j + half];
        }
    }

    addMatrix(half, a11, a22, t1);
    addMatrix(half, b11, b22, t2);
    strassen(half, t1, t2, m1);
    addMatrix(half, a21, a22, t1);
    strassen(half, t1, b11, m2);
    subtractMatrix(half, b12, b22, t2);
    strassen(half, a11, t2, m3);
    subtractMatrix(half, b21, b11, t2);
    strassen(half, a22, t2, m4);
    addMatrix(half, a11, a12, t1);
    strassen(half, t1, b22, m5);
    subtractMatrix(half, a21, a11, t1);
    addMatrix(half, b11, b12, t2);
    strassen(half, t1, t2, m6);
    subtractMatrix(half, a12, a22, t1);
    addMatrix(half, b21, b22, t2);
    strassen(half, t1, t2, m7);

    for (int i = 0; i < half; i++) {
        for (int j = 0; j < half; j++) {
            c[i][j] = m1[i][j] + m4[i][j] - m5[i][j] + m7[i][j];
            c[i][j + half] = m3[i][j] + m5[i][j];
            c[i + half][j] = m2[i][j] + m4[i][j];
            c[i + half][j + half] = m1[i][j] - m2[i][j] + m3[i][j] + m6[i][j];
        }
    }
}

/* Prints an n by n matrix. */
void printMatrix(int n, int matrix[MAX_N][MAX_N]) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            printf("%5d", matrix[i][j]);
        }
        printf("\n");
    }
}

/* Runs one matrix multiplication test. */
void runTest(int n, int a[MAX_N][MAX_N], int b[MAX_N][MAX_N]) {
    int c[MAX_N][MAX_N] = {{0}};
    printf("Matrix A:\n");
    printMatrix(n, a);
    printf("Matrix B:\n");
    printMatrix(n, b);
    strassen(n, a, b, c);
    printf("Product:\n");
    printMatrix(n, c);
    printf("\n");
}

int main(void) {
    int a1[MAX_N][MAX_N] = {{1, 2}, {3, 4}};
    int b1[MAX_N][MAX_N] = {{5, 6}, {7, 8}};
    int a2[MAX_N][MAX_N] = {
        {1, 0, 2, 1},
        {3, 1, 0, 2},
        {2, 4, 1, 0},
        {1, 2, 3, 4}
    };
    int b2[MAX_N][MAX_N] = {
        {2, 1, 0, 3},
        {1, 0, 2, 1},
        {3, 2, 1, 0},
        {0, 1, 4, 2}
    };

    printf("Strassen Matrix Multiplication\n\n");
    runTest(2, a1, b1);
    runTest(4, a2, b2);
    return 0;
}

/*
High-level idea:
Strassen divides each matrix into four blocks.
Instead of eight block multiplications, it computes seven special products.
Those products are combined to form the four blocks of the answer.
For the 2 by 2 test, each block is a single number, so the seven formulas
directly combine to produce the usual matrix product.
*/
