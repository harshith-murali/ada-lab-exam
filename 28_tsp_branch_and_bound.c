/* ================================================================ */
/* TRAVELLING SALESMAN PROBLEM - BRANCH AND BOUND */
/* ================================================================ */

/*
Algorithm name: Travelling Salesman Problem by Branch and Bound
Problem it solves:
Finds a minimum Hamiltonian cycle while pruning partial tours whose lower
bound is already no better than the best complete tour.
Time complexity: O(n!) worst case
Space complexity: O(n) recursion stack
*/

#include <stdio.h>
#include <limits.h>

#define MAX_CITIES 8

/* Returns the smallest outgoing edge from city excluding optional blocked city. */
int minOutgoingEdge(int n, int cost[MAX_CITIES][MAX_CITIES], int city) {
    int minimum = INT_MAX;
    for (int next = 0; next < n; next++) {
        if (next != city && cost[city][next] < minimum) {
            minimum = cost[city][next];
        }
    }
    return minimum;
}

/* Computes a simple lower bound for any completion of the current partial tour. */
int lowerBound(int n, int cost[MAX_CITIES][MAX_CITIES], const int visited[],
               int currentCity, int currentCost) {
    int bound = currentCost;

    for (int city = 0; city < n; city++) {
        if (!visited[city] || city == currentCity) {
            bound += minOutgoingEdge(n, cost, city);
        }
    }
    return bound;
}

/* Recursively searches tours and prunes branches whose bound is too large. */
void tspBranchAndBound(int n, int cost[MAX_CITIES][MAX_CITIES], int currentCity,
                       int level, int currentCost, int visited[],
                       int path[], int bestPath[], int *bestCost) {
    if (level == n) {
        int totalCost = currentCost + cost[currentCity][0];
        if (totalCost < *bestCost) {
            *bestCost = totalCost;
            for (int i = 0; i < n; i++) {
                bestPath[i] = path[i];
            }
        }
        return;
    }

    for (int next = 1; next < n; next++) {
        if (!visited[next]) {
            int nextCost = currentCost + cost[currentCity][next];
            visited[next] = 1;
            path[level] = next;

            if (lowerBound(n, cost, visited, next, nextCost) < *bestCost) {
                tspBranchAndBound(n, cost, next, level + 1, nextCost, visited,
                                  path, bestPath, bestCost);
            }

            visited[next] = 0;
            path[level] = -1;
        }
    }
}

/* Solves and prints one TSP branch-and-bound instance. */
void solveTspBranchAndBound(int n, int cost[MAX_CITIES][MAX_CITIES]) {
    int visited[MAX_CITIES] = {0};
    int path[MAX_CITIES];
    int bestPath[MAX_CITIES];
    int bestCost = INT_MAX;

    for (int i = 0; i < n; i++) {
        path[i] = -1;
        bestPath[i] = -1;
    }
    visited[0] = 1;
    path[0] = 0;

    tspBranchAndBound(n, cost, 0, 1, 0, visited, path, bestPath, &bestCost);

    printf("Optimal cost: %d\nOptimal tour: ", bestCost);
    for (int i = 0; i < n; i++) {
        printf("%d -> ", bestPath[i]);
    }
    printf("0\n");
}

/* Prints the distance matrix. */
void printMatrix(int n, int matrix[MAX_CITIES][MAX_CITIES]) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            printf("%4d", matrix[i][j]);
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

    printf("TSP Branch and Bound\n\nTest Case 1 Matrix:\n");
    printMatrix(4, graph1);
    solveTspBranchAndBound(4, graph1);
    printf("\nTest Case 2 Matrix:\n");
    printMatrix(4, graph2);
    solveTspBranchAndBound(4, graph2);
    return 0;
}

/*
High-level idea:
The search builds a tour one city at a time.
A lower bound estimates the cheapest possible completion from each partial tour.
If that bound is already at least the best known full tour, the branch is
discarded.
For the first test, once a tour of cost 80 is found, partial tours whose lower
bound is 80 or more are not explored further.
*/
