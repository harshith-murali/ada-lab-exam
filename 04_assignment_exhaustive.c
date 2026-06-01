/* ================================================================ */
/* ASSIGNMENT PROBLEM - EXHAUSTIVE SEARCH */
/* ================================================================ */

/*
Algorithm name: Assignment Problem by Exhaustive Search
Problem it solves:
Assigns each worker to one unique job while minimizing total cost.
This implementation uses exhaustive search, suitable for small n.
Time complexity: O(n!)
Space complexity: O(n)
*/

#include <stdio.h>
#include <limits.h>

#define MAX_N 8

/* Swaps two job numbers in a permutation. */
void swapJobs(int *first, int *second) {
    int temp = *first;
    *first = *second;
    *second = temp;
}

/* Computes total cost for assignment[worker] = job. */
int assignmentCost(int n, int cost[MAX_N][MAX_N], int assignment[]) {
    int total = 0;
    for (int worker = 0; worker < n; worker++) {
        total += cost[worker][assignment[worker]];
    }
    return total;
}

/* Generates all job permutations and stores the cheapest assignment. */
void searchAssignments(int index, int n, int cost[MAX_N][MAX_N],
                       int assignment[], int bestAssignment[], int *bestCost) {
    if (index == n) {
        int currentCost = assignmentCost(n, cost, assignment);
        if (currentCost < *bestCost) {
            *bestCost = currentCost;
            for (int i = 0; i < n; i++) {
                bestAssignment[i] = assignment[i];
            }
        }
        return;
    }

    for (int i = index; i < n; i++) {
        swapJobs(&assignment[index], &assignment[i]);
        searchAssignments(index + 1, n, cost, assignment, bestAssignment,
                          bestCost);
        swapJobs(&assignment[index], &assignment[i]);
    }
}

/* Solves and prints an assignment problem instance. */
void solveAssignment(int n, int cost[MAX_N][MAX_N]) {
    int assignment[MAX_N];
    int bestAssignment[MAX_N];
    int bestCost = INT_MAX;

    for (int i = 0; i < n; i++) {
        assignment[i] = i;
    }
    searchAssignments(0, n, cost, assignment, bestAssignment, &bestCost);

    printf("Optimal cost: %d\nChosen assignment:\n", bestCost);
    for (int worker = 0; worker < n; worker++) {
        printf("Worker %d -> Job %d (cost %d)\n", worker, bestAssignment[worker],
               cost[worker][bestAssignment[worker]]);
    }
}

/* Prints the cost matrix. */
void printCostMatrix(int n, int cost[MAX_N][MAX_N]) {
    for (int row = 0; row < n; row++) {
        for (int col = 0; col < n; col++) {
            printf("%4d", cost[row][col]);
        }
        printf("\n");
    }
}

int main(void) {
    int cost1[MAX_N][MAX_N] = {
        {9, 2, 7, 8},
        {6, 4, 3, 7},
        {5, 8, 1, 8},
        {7, 6, 9, 4}
    };
    int cost2[MAX_N][MAX_N] = {
        {10, 3, 8},
        {9, 7, 5},
        {4, 6, 2}
    };

    printf("Assignment Problem by Exhaustive Search\n\nTest Case 1 Cost Matrix:\n");
    printCostMatrix(4, cost1);
    solveAssignment(4, cost1);
    printf("\nTest Case 2 Cost Matrix:\n");
    printCostMatrix(3, cost2);
    solveAssignment(3, cost2);
    return 0;
}

/*
High-level idea:
Each possible solution is a permutation of jobs.
The job at position i is assigned to worker i.
The algorithm computes the cost of every permutation and saves the smallest.
In the first test, 24 assignments are tested. The chosen mapping has total
cost 13, which no other mapping improves.
*/
