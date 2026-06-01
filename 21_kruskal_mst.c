/* ================================================================ */
/* KRUSKAL'S ALGORITHM - MST USING UNION-FIND */
/* ================================================================ */

/*
Algorithm name: Kruskal's Minimum Spanning Tree Algorithm
Problem it solves:
Finds a minimum spanning tree by taking edges in increasing cost order while
avoiding cycles using union-find.
Time complexity: O(E^2) here due to simple edge sorting
Space complexity: O(V + E)
*/

#include <stdio.h>

#define MAX_VERTICES 10
#define MAX_EDGES 30

typedef struct {
    int source;
    int destination;
    int weight;
} Edge;

/* Finds representative of a set with path compression. */
int findSet(int parent[], int vertex) {
    if (parent[vertex] != vertex) {
        parent[vertex] = findSet(parent, parent[vertex]);
    }
    return parent[vertex];
}

/* Unites two sets by rank. */
void unionSets(int parent[], int rank[], int first, int second) {
    int rootFirst = findSet(parent, first);
    int rootSecond = findSet(parent, second);

    if (rootFirst == rootSecond) {
        return;
    }
    if (rank[rootFirst] < rank[rootSecond]) {
        parent[rootFirst] = rootSecond;
    } else if (rank[rootFirst] > rank[rootSecond]) {
        parent[rootSecond] = rootFirst;
    } else {
        parent[rootSecond] = rootFirst;
        rank[rootFirst]++;
    }
}

/* Sorts edges by weight using simple selection sort. */
void sortEdges(Edge edges[], int numEdges) {
    for (int i = 0; i < numEdges - 1; i++) {
        int minIndex = i;
        for (int j = i + 1; j < numEdges; j++) {
            if (edges[j].weight < edges[minIndex].weight) {
                minIndex = j;
            }
        }
        if (minIndex != i) {
            Edge temp = edges[i];
            edges[i] = edges[minIndex];
            edges[minIndex] = temp;
        }
    }
}

/* Computes and prints Kruskal MST. */
void kruskalMST(int numVertices, Edge edges[], int numEdges) {
    int parent[MAX_VERTICES];
    int rank[MAX_VERTICES] = {0};
    int chosen = 0;
    int totalCost = 0;

    for (int v = 0; v < numVertices; v++) {
        parent[v] = v;
    }
    sortEdges(edges, numEdges);

    printf("MST edges:\n");
    for (int i = 0; i < numEdges && chosen < numVertices - 1; i++) {
        int rootA = findSet(parent, edges[i].source);
        int rootB = findSet(parent, edges[i].destination);
        if (rootA != rootB) {
            printf("%d - %d cost %d\n", edges[i].source, edges[i].destination,
                   edges[i].weight);
            totalCost += edges[i].weight;
            chosen++;
            unionSets(parent, rank, rootA, rootB);
        }
    }
    printf("Total MST cost: %d\n", totalCost);
}

/* Prints input edge list. */
void printEdges(const Edge edges[], int numEdges) {
    printf("Edges:\n");
    for (int i = 0; i < numEdges; i++) {
        printf("%d - %d cost %d\n", edges[i].source, edges[i].destination,
               edges[i].weight);
    }
}

int main(void) {
    Edge edges1[] = {{0, 1, 10}, {0, 2, 6}, {0, 3, 5},
                     {1, 3, 15}, {2, 3, 4}};
    Edge edges2[] = {{0, 1, 1}, {0, 2, 4}, {1, 2, 2},
                     {1, 3, 6}, {2, 3, 3}};

    printf("Kruskal's MST Algorithm\n\nTest Case 1\n");
    printEdges(edges1, 5);
    kruskalMST(4, edges1, 5);
    printf("\nTest Case 2\n");
    printEdges(edges2, 5);
    kruskalMST(4, edges2, 5);
    return 0;
}

/*
High-level idea:
Edges are processed from cheapest to most expensive.
An edge is accepted only if it connects two different components.
Union-find tracks components and prevents cycles.
In the first test, edge 2-3 is chosen first, then 0-3, then 0-1. The resulting
tree spans all four vertices with total cost 19.
*/
