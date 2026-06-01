/* ================================================================ */
/* FRACTIONAL KNAPSACK PROBLEM - GREEDY RATIO */
/* ================================================================ */

/*
Algorithm name: Fractional Knapsack by Greedy Value/Weight Ratio
Problem it solves:
Maximizes profit when fractions of items may be taken.
Time complexity: O(n^2) here due to simple sorting
Space complexity: O(n)
*/

#include <stdio.h>

#define MAX_ITEMS 10

typedef struct {
    int index;
    double weight;
    double profit;
    double ratio;
} Item;

/* Sorts items by descending profit/weight ratio. */
void sortByRatio(Item items[], int n) {
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

/* Solves fractional knapsack and fills fraction taken for original items. */
double fractionalKnapsack(Item items[], int n, double capacity,
                          double fractionTaken[]) {
    double totalProfit = 0.0;

    for (int i = 0; i < n; i++) {
        fractionTaken[i] = 0.0;
        items[i].ratio = items[i].profit / items[i].weight;
    }
    sortByRatio(items, n);

    for (int i = 0; i < n && capacity > 0.0; i++) {
        if (items[i].weight <= capacity) {
            fractionTaken[items[i].index] = 1.0;
            capacity -= items[i].weight;
            totalProfit += items[i].profit;
        } else {
            fractionTaken[items[i].index] = capacity / items[i].weight;
            totalProfit += items[i].profit * fractionTaken[items[i].index];
            capacity = 0.0;
        }
    }
    return totalProfit;
}

/* Runs one fractional knapsack test. */
void runTest(Item items[], int n, double capacity) {
    double fractionTaken[MAX_ITEMS];
    double bestProfit;

    printf("Items: index(weight, profit)\n");
    for (int i = 0; i < n; i++) {
        printf("%d(%.1f, %.1f) ", items[i].index, items[i].weight,
               items[i].profit);
    }
    bestProfit = fractionalKnapsack(items, n, capacity, fractionTaken);
    printf("\nCapacity: %.1f\nOptimal profit: %.2f\nFractions taken:\n",
           capacity, bestProfit);
    for (int i = 0; i < n; i++) {
        printf("Item %d: %.2f\n", i, fractionTaken[i]);
    }
    printf("\n");
}

int main(void) {
    Item items1[] = {{0, 10, 60, 0}, {1, 20, 100, 0}, {2, 30, 120, 0}};
    Item items2[] = {{0, 5, 30, 0}, {1, 10, 40, 0}, {2, 20, 100, 0}};

    printf("Fractional Knapsack\n\n");
    runTest(items1, 3, 50);
    runTest(items2, 3, 22);
    return 0;
}

/*
High-level idea:
Because fractions are allowed, the best local choice is always the highest
profit-per-weight item still available.
The algorithm sorts by ratio, takes whole items while possible, then takes one
final fraction if needed.
In the first test, items with ratios 6, 5, and 4 are considered in that order,
giving profit 240 by taking all of items 0 and 1 and two thirds of item 2.
*/
