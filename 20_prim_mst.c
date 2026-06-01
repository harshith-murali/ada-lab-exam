/* ================================================================ */
/* PRIM'S ALGORITHM - MST O(n^2) ADJACENCY MATRIX */
/* ================================================================ */

/*
Algorithm name: Prim's Minimum Spanning Tree Algorithm
Problem it solves:
Finds a minimum spanning tree of a connected undirected weighted graph.
Time complexity: O(V^2)
Space complexity: O(V)
*/

#include <stdio.h>
#include <limits.h>

#define MAX_VERTICES 8
#define NO_EDGE 0

/* Returns the unvisited vertex with minimum key value. */
int minKeyVertex(int n, const int key[], const int inMST[]) {
    int minValue = INT_MAX;
    int minIndex = -1;
    for (int vertex = 0; vertex < n; vertex++) {
        if (!inMST[vertex] && key[vertex] < minValue) {
            minValue = key[vertex];
            minIndex = vertex;
        }
    }
    return minIndex;
}

/* Computes the MST parent array using Prim's algorithm. */
void primMST(int n, int graph[MAX_VERTICES][MAX_VERTICES], int parent[]) {
    int key[MAX_VERTICES];
    int inMST[MAX_VERTICES] = {0};

    for (int i = 0; i < n; i++) {
        key[i] = INT_MAX;
        parent[i] = -1;
    }
    key[0] = 0;

    for (int count = 0; count < n - 1; count++) {
        int u = minKeyVertex(n, key, inMST);
        inMST[u] = 1;
        for (int v = 0; v < n; v++) {
            if (graph[u][v] != NO_EDGE && !inMST[v] && graph[u][v] < key[v]) {
                parent[v] = u;
                key[v] = graph[u][v];
            }
        }
    }
}

/* Prints a matrix graph. */
void printGraph(int n, int graph[MAX_VERTICES][MAX_VERTICES]) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            printf("%4d", graph[i][j]);
        }
        printf("\n");
    }
}

/* Runs one Prim test and prints chosen tree edges. */
void runTest(int n, int graph[MAX_VERTICES][MAX_VERTICES]) {
    int parent[MAX_VERTICES];
    int totalCost = 0;

    printf("Graph adjacency matrix:\n");
    printGraph(n, graph);
    primMST(n, graph, parent);
    printf("MST edges:\n");
    for (int v = 1; v < n; v++) {
        printf("%d - %d cost %d\n", parent[v], v, graph[v][parent[v]]);
        totalCost += graph[v][parent[v]];
    }
    printf("Total MST cost: %d\n\n", totalCost);
}

int main(void) {
    int graph1[MAX_VERTICES][MAX_VERTICES] = {
        {0, 2, 0, 6, 0},
        {2, 0, 3, 8, 5},
        {0, 3, 0, 0, 7},
        {6, 8, 0, 0, 9},
        {0, 5, 7, 9, 0}
    };
    int graph2[MAX_VERTICES][MAX_VERTICES] = {
        {0, 4, 1, 0},
        {4, 0, 2, 5},
        {1, 2, 0, 3},
        {0, 5, 3, 0}
    };

    printf("Prim's MST Algorithm\n\n");
    runTest(5, graph1);
    runTest(4, graph2);
    return 0;
}

/*
High-level idea:
Prim's algorithm grows one tree.
Each step adds the outside vertex that can be connected with the cheapest edge.
The key array stores each outside vertex's best current connection cost.
In the first test, the tree starts at 0, then cheaply reaches 1, 2, 4, and 3,
forming an MST with total cost 16.
*/
