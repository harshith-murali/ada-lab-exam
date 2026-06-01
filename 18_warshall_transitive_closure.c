/* ================================================================ */
/* WARSHALL'S ALGORITHM - TRANSITIVE CLOSURE */
/* ================================================================ */

/*
Algorithm name: Warshall's Algorithm
Problem it solves:
Computes reachability between every pair of vertices in a directed graph.
Time complexity: O(V^3)
Space complexity: O(V^2)
*/

#include <stdio.h>

#define MAX_VERTICES 8

/* Computes transitive closure of graph into closure. */
void warshall(int n, int graph[MAX_VERTICES][MAX_VERTICES],
              int closure[MAX_VERTICES][MAX_VERTICES]) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            closure[i][j] = graph[i][j];
        }
        closure[i][i] = 1;
    }

    for (int k = 0; k < n; k++) {
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                if (closure[i][k] && closure[k][j]) {
                    closure[i][j] = 1;
                }
            }
        }
    }
}

/* Prints an n by n matrix. */
void printMatrix(int n, int matrix[MAX_VERTICES][MAX_VERTICES]) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            printf("%3d", matrix[i][j]);
        }
        printf("\n");
    }
}

/* Runs one Warshall test. */
void runTest(int n, int graph[MAX_VERTICES][MAX_VERTICES]) {
    int closure[MAX_VERTICES][MAX_VERTICES];
    printf("Graph adjacency matrix:\n");
    printMatrix(n, graph);
    warshall(n, graph, closure);
    printf("Transitive closure:\n");
    printMatrix(n, closure);
    printf("\n");
}

int main(void) {
    int graph1[MAX_VERTICES][MAX_VERTICES] = {
        {0, 1, 0, 0},
        {0, 0, 1, 0},
        {0, 0, 0, 1},
        {0, 0, 0, 0}
    };
    int graph2[MAX_VERTICES][MAX_VERTICES] = {
        {0, 1, 0},
        {0, 0, 1},
        {1, 0, 0}
    };

    printf("Warshall's Algorithm\n\n");
    runTest(4, graph1);
    runTest(3, graph2);
    return 0;
}

/*
High-level idea:
The algorithm asks whether vertex k can be used as an intermediate stop.
If i can reach k and k can reach j, then i can reach j.
Trying every k eventually discovers all indirect reachability.
In the first test, 0 reaches 1, 1 reaches 2, and 2 reaches 3, so Warshall
eventually marks that 0 can reach 2 and 3.
*/
