/* ================================================================ */
/* KNAPSACK PROBLEM - BRANCH AND BOUND */
/* ================================================================ */

/*
Algorithm name: 0/1 Knapsack by Branch and Bound
Problem it solves:
Finds the maximum profit subset while pruning branches whose optimistic upper
bound cannot beat the best solution.
Time complexity: O(2^n) worst case
Space complexity: O(2^n) for the simple queue
*/

#include <stdio.h>

#define MAX_ITEMS 10
#define MAX_QUEUE 200

typedef struct {
    int index;
    int weight;
    int profit;
    double ratio;
} Item;

typedef struct {
    int level;
    int weight;
    int profit;
    double bound;
    int taken[MAX_ITEMS];
} Node;

/* Sorts items by descending profit/weight ratio for stronger bounds. */
void sortItemsByRatio(Item items[], int n) {
    for (int i = 0; i < n - 1; i++) {
        int maxIndex = i;
        for (int j = i + 1; j < n; j++) {
            if (items[j].ratio > items[maxIndex].ratio) {
                maxIndex = j;
            }
        }
        if (maxIndex != i) {
            Item temp = items[i];
            items[i] = items[maxIndex];
            items[maxIndex] = temp;
        }
    }
}

/* Computes fractional upper bound from a node. */
double bound(Node node, int n, int capacity, const Item items[]) {
    int totalWeight = node.weight;
    double profitBound = node.profit;
    int next = node.level + 1;

    if (totalWeight >= capacity) {
        return 0.0;
    }

    while (next < n && totalWeight + items[next].weight <= capacity) {
        totalWeight += items[next].weight;
        profitBound += items[next].profit;
        next++;
    }
    if (next < n) {
        profitBound += (capacity - totalWeight) * items[next].ratio;
    }
    return profitBound;
}

/* Solves 0/1 knapsack using a breadth-first branch-and-bound queue. */
int knapsackBranchAndBound(Item items[], int n, int capacity, int bestTaken[]) {
    Node queue[MAX_QUEUE];
    int front = 0;
    int rear = 0;
    int bestProfit = 0;
    Node root = {-1, 0, 0, 0.0, {0}};

    for (int i = 0; i < n; i++) {
        items[i].ratio = (double)items[i].profit / items[i].weight;
        bestTaken[i] = 0;
    }
    sortItemsByRatio(items, n);
    root.bound = bound(root, n, capacity, items);
    queue[rear++] = root;

    while (front < rear) {
        Node current = queue[front++];
        int nextLevel = current.level + 1;

        if (current.bound <= bestProfit || nextLevel >= n) {
            continue;
        }

        Node includeNode = current;
        includeNode.level = nextLevel;
        includeNode.weight += items[nextLevel].weight;
        includeNode.profit += items[nextLevel].profit;
        includeNode.taken[nextLevel] = 1;

        if (includeNode.weight <= capacity && includeNode.profit > bestProfit) {
            bestProfit = includeNode.profit;
            for (int i = 0; i < n; i++) {
                bestTaken[i] = includeNode.taken[i];
            }
        }
        includeNode.bound = bound(includeNode, n, capacity, items);
        if (includeNode.bound > bestProfit && rear < MAX_QUEUE) {
            queue[rear++] = includeNode;
        }

        Node excludeNode = current;
        excludeNode.level = nextLevel;
        excludeNode.taken[nextLevel] = 0;
        excludeNode.bound = bound(excludeNode, n, capacity, items);
        if (excludeNode.bound > bestProfit && rear < MAX_QUEUE) {
            queue[rear++] = excludeNode;
        }
    }

    return bestProfit;
}

/* Runs one branch-and-bound knapsack test. */
void runTest(Item items[], int n, int capacity) {
    int bestTaken[MAX_ITEMS];
    int bestProfit;
    int totalWeight = 0;

    printf("Items original index(weight, profit): ");
    for (int i = 0; i < n; i++) {
        printf("%d(%d, %d) ", items[i].index, items[i].weight, items[i].profit);
    }
    bestProfit = knapsackBranchAndBound(items, n, capacity, bestTaken);
    printf("\nCapacity: %d\nOptimal profit: %d\nSelected items: ", capacity,
           bestProfit);
    for (int i = 0; i < n; i++) {
        if (bestTaken[i]) {
            printf("%d ", items[i].index);
            totalWeight += items[i].weight;
        }
    }
    printf("\nTotal weight: %d\n\n", totalWeight);
}

int main(void) {
    Item items1[] = {{0, 2, 40, 0}, {1, 3, 50, 0}, {2, 5, 100, 0},
                     {3, 4, 95, 0}};
    Item items2[] = {{0, 10, 60, 0}, {1, 20, 100, 0}, {2, 30, 120, 0}};

    printf("Knapsack Branch and Bound\n\n");
    runTest(items1, 4, 7);
    runTest(items2, 3, 50);
    return 0;
}

/*
High-level idea:
Each node represents choices made up to some item.
The bound estimates the best possible profit if remaining capacity could be
filled fractionally.
Branches whose bound cannot beat the best profit are skipped.
In the first test, high-ratio items are considered first; once a strong profit
is found, weaker branches with low bounds are pruned.
*/
