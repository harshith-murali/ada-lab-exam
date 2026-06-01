/* ================================================================ */
/* TRAVELLING SALESMAN PROBLEM - EXHAUSTIVE SEARCH */
/* ================================================================ */

/*
Algorithm name: Travelling Salesman Problem by Exhaustive Search
Problem it solves:
Finds the minimum-cost tour that starts at city 0, visits every city once,
and returns to city 0.
Time complexity: O(n!)
Space complexity: O(n)
*/

#include <stdio.h>
#include <limits.h>

#define MAX_CITIES 8

/* Swaps two integers used while generating permutations. */
void swapInt(int *first, int *second) {
    int temp = *first;
    *first = *second;
    *second = temp;
}

/* Returns the cost of tour 0 -> permutation -> 0. */
int tourCost(int numCities, int cost[MAX_CITIES][MAX_CITIES], int permutation[]) {
    int total = 0;
    int previous = 0;
    for (int i = 0; i < numCities - 1; i++) {
        total += cost[previous][permutation[i]];
        previous = permutation[i];
    }
    return total + cost[previous][0];
}

/* Recursively tests all city orders and stores the cheapest one. */
void permuteTours(int left, int right, int numCities,
                  int cost[MAX_CITIES][MAX_CITIES], int permutation[],
                  int bestTour[], int *bestCost) {
    if (left == right) {
        int currentCost = tourCost(numCities, cost, permutation);
        if (currentCost < *bestCost) {
            *bestCost = currentCost;
            for (int i = 0; i < numCities - 1; i++) {
                bestTour[i] = permutation[i];
            }
        }
        return;
    }

    for (int i = left; i <= right; i++) {
        swapInt(&permutation[left], &permutation[i]);
        permuteTours(left + 1, right, numCities, cost, permutation,
                     bestTour, bestCost);
        swapInt(&permutation[left], &permutation[i]);
    }
}

/* Solves TSP by exhaustive permutation search. */
void solveTspExhaustive(int numCities, int cost[MAX_CITIES][MAX_CITIES]) {
    int permutation[MAX_CITIES];
    int bestTour[MAX_CITIES];
    int bestCost = INT_MAX;

    for (int city = 1; city < numCities; city++) {
        permutation[city - 1] = city;
    }

    permuteTours(0, numCities - 2, numCities, cost, permutation, bestTour,
                 &bestCost);

    printf("Optimal cost: %d\nOptimal tour: 0", bestCost);
    for (int i = 0; i < numCities - 1; i++) {
        printf(" -> %d", bestTour[i]);
    }
    printf(" -> 0\n");
}

/* Prints a distance matrix. */
void printMatrix(int numCities, int matrix[MAX_CITIES][MAX_CITIES]) {
    for (int row = 0; row < numCities; row++) {
        for (int col = 0; col < numCities; col++) {
            printf("%4d", matrix[row][col]);
        }
        printf("\n");
    }
}

int main(void) {
    int graph1[MAX_CITIES][MAX_CITIES] = {
        {0, 10, 15, 20},
        {10, 0, 35, 25},
        {15, 35, 0, 30},
        {20, 25, 30, 0}
    };
    int graph2[MAX_CITIES][MAX_CITIES] = {
        {0, 5, 9, 10},
        {5, 0, 6, 4},
        {9, 6, 0, 8},
        {10, 4, 8, 0}
    };

    printf("TSP Exhaustive Search\n\nTest Case 1 Matrix:\n");
    printMatrix(4, graph1);
    solveTspExhaustive(4, graph1);
    printf("\nTest Case 2 Matrix:\n");
    printMatrix(4, graph2);
    solveTspExhaustive(4, graph2);
    return 0;
}

/*
High-level idea:
City 0 is fixed as the start to avoid duplicate rotations.
The remaining cities are permuted in every possible order.
Each complete order is evaluated as a cycle returning to city 0.
For the first test case, all six orders of cities 1, 2, and 3 are checked.
The cheapest computed tour has cost 80, so that tour is printed.
*/
