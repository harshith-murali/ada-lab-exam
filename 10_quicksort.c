/* ================================================================ */
/* QUICKSORT */
/* ================================================================ */

/*
Algorithm name: Quicksort
Problem it solves:
Sorts an array by partitioning around a pivot and recursively sorting the two
resulting sides.
Time complexity: O(n^2) worst case, O(n log n) average case
Space complexity: O(log n) average recursion depth
*/

#include <stdio.h>

/* Swaps two integers. */
void swapInt(int *first, int *second) {
    int temp = *first;
    *first = *second;
    *second = temp;
}

/* Places elements <= pivot to the left and returns pivot's final index. */
int partition(int array[], int low, int high) {
    int pivot = array[high];
    int smallerIndex = low - 1;

    for (int scan = low; scan < high; scan++) {
        if (array[scan] <= pivot) {
            smallerIndex++;
            swapInt(&array[smallerIndex], &array[scan]);
        }
    }
    swapInt(&array[smallerIndex + 1], &array[high]);
    return smallerIndex + 1;
}

/* Recursively sorts array[low..high]. */
void quicksort(int array[], int low, int high) {
    if (low < high) {
        int pivotIndex = partition(array, low, high);
        quicksort(array, low, pivotIndex - 1);
        quicksort(array, pivotIndex + 1, high);
    }
}

/* Prints an array. */
void printArray(const int array[], int n) {
    for (int i = 0; i < n; i++) {
        printf("%d ", array[i]);
    }
    printf("\n");
}

/* Runs one quicksort test case. */
void runTest(int array[], int n) {
    printf("Before: ");
    printArray(array, n);
    quicksort(array, 0, n - 1);
    printf("After:  ");
    printArray(array, n);
    printf("\n");
}

int main(void) {
    int array1[] = {10, 7, 8, 9, 1, 5};
    int array2[] = {4, 2, 4, 1, 3};
    int array3[] = {12, -1, 0, 99, 18, 6};

    printf("Quicksort\n\n");
    runTest(array1, 6);
    runTest(array2, 5);
    runTest(array3, 6);
    return 0;
}

/*
High-level idea:
A pivot is chosen, here the last element.
Partitioning moves values not greater than the pivot to its left and larger
values to its right.
Then quicksort recursively sorts both sides.
For the first test, pivot 5 moves near the front, splitting small and large
values; recursive partitioning finishes the sorted order.
*/
