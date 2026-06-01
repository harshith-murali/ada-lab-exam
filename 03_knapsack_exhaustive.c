/* ================================================================ */
/* KNAPSACK PROBLEM - EXHAUSTIVE SEARCH OVER SUBSETS */
/* ================================================================ */

/*
Algorithm name: Knapsack by Exhaustive Search
Problem it solves:
Finds the most profitable subset of items whose total weight does not exceed
the capacity.
Time complexity: O(2^n * n)
Space complexity: O(n)
*/

#include <stdio.h>

#define MAX_ITEMS 20

/* Tries every subset and marks the best selected items. */
int exhaustiveKnapsack(int numItems, const int weights[], const int profits[],
                       int capacity, int selected[]) {
    int bestProfit = 0;
    int subsetCount = 1 << numItems;

    for (int i = 0; i < numItems; i++) {
        selected[i] = 0;
    }

    for (int mask = 0; mask < subsetCount; mask++) {
        int currentWeight = 0;
        int currentProfit = 0;

        for (int item = 0; item < numItems; item++) {
            if ((mask & (1 << item)) != 0) {
                currentWeight += weights[item];
                currentProfit += profits[item];
            }
        }

        if (currentWeight <= capacity && currentProfit > bestProfit) {
            bestProfit = currentProfit;
            for (int item = 0; item < numItems; item++) {
                selected[item] = (mask & (1 << item)) != 0;
            }
        }
    }
    return bestProfit;
}

/* Prints one complete test case. */
void runTest(int numItems, const int weights[], const int profits[], int capacity) {
    int selected[MAX_ITEMS];
    int bestProfit = exhaustiveKnapsack(numItems, weights, profits, capacity,
                                        selected);
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
    int weights2[] = {1, 4, 3, 5};
    int profits2[] = {150, 300, 200, 350};
    int weights3[] = {6, 2, 3, 2};
    int profits3[] = {30, 14, 16, 9};

    printf("Knapsack Exhaustive Search\n\n");
    runTest(4, weights1, profits1, 8);
    runTest(4, weights2, profits2, 7);
    runTest(4, weights3, profits3, 6);
    return 0;
}

/*
High-level idea:
Every item has two choices: selected or not selected.
A binary mask represents one subset of items.
The program evaluates all masks, ignores overweight subsets, and remembers the
valid subset with maximum profit.
In the first test, subset {1, 3} has weight 8 and profit 12, which is best.
*/
