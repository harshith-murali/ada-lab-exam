/* ================================================================ */
/* 0/1 KNAPSACK PROBLEM - DYNAMIC PROGRAMMING */
/* ================================================================ */

/*
Algorithm name: 0/1 Knapsack using Dynamic Programming
Problem it solves:
Finds maximum profit under a weight capacity when each item can be selected at
most once.
Time complexity: O(n * capacity)
Space complexity: O(n * capacity)
*/

#include <stdio.h>

#define MAX_ITEMS 10
#define MAX_CAPACITY 50

/* Fills a DP table and reconstructs selected items. */
int knapsackDP(int numItems, const int weights[], const int profits[],
               int capacity, int selected[]) {
    int dp[MAX_ITEMS + 1][MAX_CAPACITY + 1] = {{0}};

    for (int item = 1; item <= numItems; item++) {
        for (int cap = 0; cap <= capacity; cap++) {
            dp[item][cap] = dp[item - 1][cap];
            if (weights[item - 1] <= cap) {
                int includeProfit = profits[item - 1] +
                                    dp[item - 1][cap - weights[item - 1]];
                if (includeProfit > dp[item][cap]) {
                    dp[item][cap] = includeProfit;
                }
            }
        }
    }

    for (int i = 0; i < numItems; i++) {
        selected[i] = 0;
    }

    int cap = capacity;
    for (int item = numItems; item >= 1; item--) {
        if (dp[item][cap] != dp[item - 1][cap]) {
            selected[item - 1] = 1;
            cap -= weights[item - 1];
        }
    }

    return dp[numItems][capacity];
}

/* Runs and prints one DP knapsack test. */
void runTest(int numItems, const int weights[], const int profits[], int capacity) {
    int selected[MAX_ITEMS];
    int bestProfit = knapsackDP(numItems, weights, profits, capacity, selected);
    int totalWeight = 0;

    printf("Items: index(weight, profit)\n");
    for (int i = 0; i < numItems; i++) {
        printf("%d(%d, %d) ", i, weights[i], profits[i]);
    }
    printf("\nCapacity: %d\nOptimal profit: %d\nSelected items: ", capacity,
           bestProfit);
    for (int i = 0; i < numItems; i++) {
        if (selected[i]) {
            printf("%d ", i);
            totalWeight += weights[i];
        }
    }
    printf("\nTotal weight: %d\n\n", totalWeight);
}

int main(void) {
    int weights1[] = {2, 3, 4, 5};
    int profits1[] = {3, 4, 5, 8};
    int weights2[] = {1, 3, 4, 5};
    int profits2[] = {1, 4, 5, 7};
    int weights3[] = {4, 2, 3};
    int profits3[] = {10, 4, 7};

    printf("0/1 Knapsack using Dynamic Programming\n\n");
    runTest(4, weights1, profits1, 8);
    runTest(4, weights2, profits2, 7);
    runTest(3, weights3, profits3, 5);
    return 0;
}

/*
High-level idea:
dp[i][w] stores the best profit using the first i items and capacity w.
For each item, the algorithm chooses between excluding it and including it.
After the table is filled, selected items are recovered by walking backward.
For the first test, including item 3 with item 1 reaches weight 8 and profit
12, which becomes the optimal table value.
*/
