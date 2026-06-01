/* ================================================================ */
/* FLOYD'S ALGORITHM - ALL-PAIRS SHORTEST PATHS */
/* ================================================================ */

/*
Algorithm name: Floyd's Algorithm
Problem it solves:
Finds shortest path distances between every pair of vertices in a weighted
directed graph.
Time complexity: O(V^3)
Space complexity: O(V^2)
*/

#include <stdio.h>

#define MAX_VERTICES 8
#define INF 1000000

/* Computes all-pairs shortest distances. */
void floyd(int n, int graph[MAX_VERTICES][MAX_VERTICES],
           int dist[MAX_VERTICES][MAX_VERTICES]) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            dist[i][j] = graph[i][j];
        }
    }

    for (int k = 0; k < n; k++) {
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                if (dist[i][k] + dist[k][j] < dist[i][j]) {
                    dist[i][j] = dist[i][k] + dist[k][j];
                }
            }
        }
    }
}

/* Prints matrix, showing INF for unreachable entries. */
void printMatrix(int n, int matrix[MAX_VERTICES][MAX_VERTICES]) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (matrix[i][j] >= INF / 2) {
                printf("%6s", "INF");
            } else {
                printf("%6d", matrix[i][j]);
            }
        }
        printf("\n");
    }
}

/* Runs one Floyd test. */
void runTest(int n, int graph[MAX_VERTICES][MAX_VERTICES]) {
    int dist[MAX_VERTICES][MAX_VERTICES];
    printf("Input graph matrix:\n");
    printMatrix(n, graph);
    floyd(n, graph, dist);
    printf("Shortest path distances:\n");
    printMatrix(n, dist);
    printf("\n");
}

int main(void) {
    int graph1[MAX_VERTICES][MAX_VERTICES] = {
        {0, 5, INF, 10},
        {INF, 0, 3, INF},
        {INF, INF, 0, 1},
        {INF, INF, INF, 0}
    };
    int graph2[MAX_VERTICES][MAX_VERTICES] = {
        {0, 2, INF},
        {INF, 0, 4},
        {1, INF, 0}
    };

    printf("Floyd's Algorithm\n\n");
    runTest(4, graph1);
    runTest(3, graph2);
    return 0;
}

/*
High-level idea:
Floyd's algorithm improves paths by allowing vertices as intermediates.
When vertex k is allowed, every pair i, j checks whether i -> k -> j is shorter.
After all vertices have been considered, every shortest distance is known.
In the first test, the path 0 -> 1 -> 2 -> 3 has cost 9, improving the direct
0 -> 3 cost of 10.
*/
