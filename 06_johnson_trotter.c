/* ================================================================ */
/* GENERATING PERMUTATIONS - JOHNSON-TROTTER ALGORITHM */
/* ================================================================ */

/*
Algorithm name: Johnson-Trotter Permutation Generation
Problem it solves:
Generates all permutations of 1..n by repeatedly swapping the largest mobile
element with the adjacent element in its direction.
Time complexity: O(n * n!)
Space complexity: O(n)
*/

#include <stdio.h>

#define MAX_N 8
#define LEFT -1
#define RIGHT 1

/* Prints the current permutation. */
void printPermutation(const int permutation[], int n) {
    for (int i = 0; i < n; i++) {
        printf("%d ", permutation[i]);
    }
    printf("\n");
}

/* Returns the index of the largest mobile element, or -1 if none exists. */
int largestMobileIndex(const int permutation[], const int direction[], int n) {
    int bestIndex = -1;
    int bestValue = -1;

    for (int i = 0; i < n; i++) {
        int neighbor = i + direction[i];
        if (neighbor >= 0 && neighbor < n &&
            permutation[i] > permutation[neighbor] &&
            permutation[i] > bestValue) {
            bestValue = permutation[i];
            bestIndex = i;
        }
    }
    return bestIndex;
}

/* Generates permutations using the Johnson-Trotter rule. */
void johnsonTrotter(int n) {
    int permutation[MAX_N];
    int direction[MAX_N];

    for (int i = 0; i < n; i++) {
        permutation[i] = i + 1;
        direction[i] = LEFT;
    }

    printPermutation(permutation, n);
    while (1) {
        int mobileIndex = largestMobileIndex(permutation, direction, n);
        if (mobileIndex == -1) {
            break;
        }

        int swapIndex = mobileIndex + direction[mobileIndex];
        int mobileValue = permutation[mobileIndex];
        int tempValue = permutation[mobileIndex];
        int tempDirection = direction[mobileIndex];
        permutation[mobileIndex] = permutation[swapIndex];
        direction[mobileIndex] = direction[swapIndex];
        permutation[swapIndex] = tempValue;
        direction[swapIndex] = tempDirection;

        for (int i = 0; i < n; i++) {
            if (permutation[i] > mobileValue) {
                direction[i] = -direction[i];
            }
        }
        printPermutation(permutation, n);
    }
}

int main(void) {
    printf("Johnson-Trotter Permutations\n\n");
    printf("Permutations for n = 3:\n");
    johnsonTrotter(3);
    printf("\nPermutations for n = 4:\n");
    johnsonTrotter(4);
    return 0;
}

/*
High-level idea:
Every number has a direction, initially left.
A mobile number is larger than the adjacent number it points to.
The largest mobile number swaps in its direction, then all larger numbers
reverse direction.
For n = 3, the algorithm starts at 1 2 3, moves 3 left, then continues until
no mobile element remains after all six permutations are printed.
*/
