/* ================================================================ */
/* DIJKSTRA'S ALGORITHM - O(n^2) ADJACENCY MATRIX */
/* ================================================================ */

/*
Algorithm name: Dijkstra's Single-Source Shortest Path Algorithm
Problem it solves:
Finds shortest paths from one source to all vertices in a graph with
non-negative edge weights.
Time complexity: O(V^2)
Space complexity: O(V)
*/

#include <stdio.h>
#include <limits.h>

#define MAX_VERTICES 8
#define INF 1000000

/* Chooses the unvisited vertex with smallest known distance. */
int minDistanceVertex(int n, const int dist[], const int visited[]) {
    int minValue = INT_MAX;
    int minIndex = -1;
    for (int v = 0; v < n; v++) {
        if (!visited[v] && dist[v] < minValue) {
            minValue = dist[v];
            minIndex = v;
        }
    }
    return minIndex;
}

/* Computes shortest distances and parents from source. */
void dijkstra(int n, int graph[MAX_VERTICES][MAX_VERTICES], int source,
              int dist[], int parent[]) {
    int visited[MAX_VERTICES] = {0};

    for (int v = 0; v < n; v++) {
        dist[v] = INF;
        parent[v] = -1;
    }
    dist[source] = 0;

    for (int count = 0; count < n - 1; count++) {
        int u = minDistanceVertex(n, dist, visited);
        if (u == -1) {
            break;
        }
        visited[u] = 1;

        for (int v = 0; v < n; v++) {
            if (!visited[v] && graph[u][v] < INF &&
                dist[u] + graph[u][v] < dist[v]) {
                dist[v] = dist[u] + graph[u][v];
                parent[v] = u;
            }
        }
    }
}

/* Recursively prints path from source to vertex using parent array. */
void printPath(int parent[], int vertex) {
    if (vertex == -1) {
        return;
    }
    printPath(parent, parent[vertex]);
    printf("%d ", vertex);
}

/* Prints graph matrix, using INF for missing edges. */
void printGraph(int n, int graph[MAX_VERTICES][MAX_VERTICES]) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (graph[i][j] >= INF / 2) {
                printf("%5s", "INF");
            } else {
                printf("%5d", graph[i][j]);
            }
        }
        printf("\n");
    }
}

/* Runs one Dijkstra test. */
void runTest(int n, int graph[MAX_VERTICES][MAX_VERTICES], int source) {
    int dist[MAX_VERTICES];
    int parent[MAX_VERTICES];

    printf("Graph matrix:\n");
    printGraph(n, graph);
    dijkstra(n, graph, source, dist, parent);
    printf("Source: %d\nShortest paths:\n", source);
    for (int v = 0; v < n; v++) {
        printf("To %d cost %d path: ", v, dist[v]);
        printPath(parent, v);
        printf("\n");
    }
    printf("\n");
}

int main(void) {
    int graph1[MAX_VERTICES][MAX_VERTICES] = {
        {0, 10, 3, INF, INF},
        {INF, 0, 1, 2, INF},
        {INF, 4, 0, 8, 2},
        {INF, INF, INF, 0, 7},
        {INF, INF, INF, 9, 0}
    };
    int graph2[MAX_VERTICES][MAX_VERTICES] = {
        {0, 5, INF, 10},
        {INF, 0, 3, INF},
        {INF, INF, 0, 1},
        {INF, INF, INF, 0}
    };

    printf("Dijkstra's Algorithm\n\n");
    runTest(5, graph1, 0);
    runTest(4, graph2, 0);
    return 0;
}

/*
High-level idea:
Dijkstra keeps the best known distance from the source to each vertex.
At every step, the unvisited vertex with the smallest distance is finalized.
Its outgoing edges are relaxed to improve neighbors.
In the first test, vertex 2 becomes final early with distance 3, then it
improves distances to vertices 1 and 4.
*/
