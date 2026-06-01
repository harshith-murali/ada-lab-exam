/* ================================================================ */
/* SUBSET-SUM PROBLEM - BACKTRACKING */
/* ================================================================ */

/*
Algorithm name: Subset-Sum Backtracking
Problem it solves:
Finds subsets whose elements add up exactly to a target sum.
Time complexity: O(2^n)
Space complexity: O(n)
*/

#include <stdio.h>

#define MAX_ITEMS 20

/* Recursively includes or excludes each item while looking for target sum. */
void subsetSumBacktracking(const int values[], int n, int index, int currentSum,
                           int target, int selected[], int *solutionCount) {
    if (currentSum == target) {
        printf("Subset: ");
        for (int i = 0; i < index; i++) {
            if (selected[i]) {
                printf("%d ", values[i]);
            }
        }
        printf("\n");
        (*solutionCount)++;
        return;
    }

    if (index == n || currentSum > target) {
        return;
    }

    selected[index] = 1;
    subsetSumBacktracking(values, n, index + 1, currentSum + values[index],
                          target, selected, solutionCount);
    selected[index] = 0;
    subsetSumBacktracking(values, n, index + 1, currentSum, target, selected,
                          solutionCount);
}

/* Runs one subset-sum test case. */
void runTest(const int values[], int n, int target) {
    int selected[MAX_ITEMS] = {0};
    int solutionCount = 0;

    printf("Values: ");
    for (int i = 0; i < n; i++) {
        printf("%d ", values[i]);
    }
    printf("\nTarget: %d\n", target);
    subsetSumBacktracking(values, n, 0, 0, target, selected, &solutionCount);
    if (solutionCount == 0) {
        printf("No subset found.\n");
    }
    printf("Number of solutions printed: %d\n\n", solutionCount);
}

int main(void) {
    int values1[] = {10, 7, 5, 18, 12, 20, 15};
    int values2[] = {3, 34, 4, 12, 5, 2};
    int values3[] = {2, 4, 6, 8};

    printf("Subset-Sum Backtracking\n\n");
    runTest(values1, 7, 35);
    runTest(values2, 6, 9);
    runTest(values3, 4, 5);
    return 0;
}

/*
High-level idea:
At each item, the search branches into include and exclude choices.
If the running sum reaches the target, the selected subset is printed.
If the sum exceeds the target, that branch stops early.
For the second test, the branch including 4, then 5 reaches target 9, so that
subset is reported before other branches continue.
*/
