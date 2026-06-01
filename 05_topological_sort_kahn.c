/* ================================================================ */
/* TOPOLOGICAL SORTING - KAHN'S ALGORITHM */
/* ================================================================ */

/*
Algorithm name: Topological Sorting using Kahn's Algorithm
Problem it solves:
Orders vertices of a directed acyclic graph so every edge u -> v places u
before v in the order.
Time complexity: O(V^2) with adjacency matrix
Space complexity: O(V)
*/

#include <stdio.h>

#define MAX_VERTICES 10

/* Prints the adjacency matrix of a directed graph. */
void printGraph(int n, int graph[MAX_VERTICES][MAX_VERTICES]) {
    printf("Adjacency matrix:\n");
    for (int row = 0; row < n; row++) {
        for (int col = 0; col < n; col++) {
            printf("%3d", graph[row][col]);
        }
        printf("\n");
    }
}

/* Produces a topological order using indegrees and a simple array queue. */
int topologicalSortKahn(int n, int graph[MAX_VERTICES][MAX_VERTICES],
                        int order[]) {
    int indegree[MAX_VERTICES] = {0};
    int queue[MAX_VERTICES];
    int front = 0;
    int rear = 0;
    int count = 0;

    for (int from = 0; from < n; from++) {
        for (int to = 0; to < n; to++) {
            if (graph[from][to]) {
                indegree[to]++;
            }
        }
    }

    for (int vertex = 0; vertex < n; vertex++) {
        if (indegree[vertex] == 0) {
            queue[rear++] = vertex;
        }
    }

    while (front < rear) {
        int vertex = queue[front++];
        order[count++] = vertex;

        for (int to = 0; to < n; to++) {
            if (graph[vertex][to]) {
                indegree[to]--;
                if (indegree[to] == 0) {
                    queue[rear++] = to;
                }
            }
        }
    }

    return count == n;
}

/* Runs and prints one topological sorting test. */
void runTest(int n, int graph[MAX_VERTICES][MAX_VERTICES]) {
    int order[MAX_VERTICES];
    printGraph(n, graph);
    if (topologicalSortKahn(n, graph, order)) {
        printf("Topological order: ");
        for (int i = 0; i < n; i++) {
            printf("%d ", order[i]);
        }
        printf("\n\n");
    } else {
        printf("Cycle detected; no topological order exists.\n\n");
    }
}

int main(void) {
    int graph1[MAX_VERTICES][MAX_VERTICES] = {
        {0, 0, 1, 1, 0, 0},
        {0, 0, 0, 1, 1, 0},
        {0, 0, 0, 0, 0, 1},
        {0, 0, 0, 0, 0, 1},
        {0, 0, 0, 0, 0, 1},
        {0, 0, 0, 0, 0, 0}
    };
    int graph2[MAX_VERTICES][MAX_VERTICES] = {
        {0, 1, 1, 0},
        {0, 0, 0, 1},
        {0, 0, 0, 1},
        {0, 0, 0, 0}
    };

    printf("Topological Sorting using Kahn's Algorithm\n\nTest Case 1\n");
    runTest(6, graph1);
    printf("Test Case 2\n");
    runTest(4, graph2);
    return 0;
}

/*
High-level idea:
Kahn's algorithm repeatedly chooses vertices with indegree 0.
Removing such a vertex lowers the indegree of its outgoing neighbors.
If all vertices are removed, the produced list is a valid topological order.
In the first test, vertices 0 and 1 start with indegree 0. As they are removed,
more vertices become available until all six vertices are ordered.
*/
