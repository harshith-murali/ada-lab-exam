/* ================================================================ */
/* COMPUTING MEDIAN AND SELECTION - DETERMINISTIC QUICKSELECT */
/* ================================================================ */

/*
Algorithm name: Deterministic Selection using Quickselect Partitioning
Problem it solves:
Finds the kth smallest element and uses it to compute the median of an array.
This version uses the last element as a deterministic pivot.
Time complexity: O(n^2) worst case, O(n) average on typical inputs
Space complexity: O(1)
*/

#include <stdio.h>

#define MAX_SIZE 20

/* Swaps two array elements. */
void swapInt(int *first, int *second) {
    int temp = *first;
    *first = *second;
    *second = temp;
}

/* Partitions array[left..right] around a pivot and returns its final index. */
int partition(int array[], int left, int right) {
    int pivot = array[right];
    int smallerIndex = left;

    for (int scan = left; scan < right; scan++) {
        if (array[scan] <= pivot) {
            swapInt(&array[smallerIndex], &array[scan]);
            smallerIndex++;
        }
    }
    swapInt(&array[smallerIndex], &array[right]);
    return smallerIndex;
}

/* Returns the kth smallest value where k is zero based. */
int quickSelect(int array[], int left, int right, int k) {
    while (left <= right) {
        int pivotIndex = partition(array, left, right);
        if (pivotIndex == k) {
            return array[pivotIndex];
        }
        if (k < pivotIndex) {
            right = pivotIndex - 1;
        } else {
            left = pivotIndex + 1;
        }
    }
    return -1;
}

/* Copies an array so selection can modify the copy safely. */
void copyArray(int destination[], const int source[], int n) {
    for (int i = 0; i < n; i++) {
        destination[i] = source[i];
    }
}

/* Computes and prints kth element and median for one array. */
void runTest(const int values[], int n, int k) {
    int copy[MAX_SIZE];
    int medianCopy[MAX_SIZE];
    int kthValue;

    printf("Array: ");
    for (int i = 0; i < n; i++) {
        printf("%d ", values[i]);
    }
    printf("\n");

    copyArray(copy, values, n);
    kthValue = quickSelect(copy, 0, n - 1, k);
    printf("%d-th smallest value (zero based): %d\n", k, kthValue);

    copyArray(medianCopy, values, n);
    if (n % 2 == 1) {
        printf("Median: %.2f\n\n",
               (double)quickSelect(medianCopy, 0, n - 1, n / 2));
    } else {
        int leftCopy[MAX_SIZE];
        int rightCopy[MAX_SIZE];
        copyArray(leftCopy, values, n);
        copyArray(rightCopy, values, n);
        printf("Median: %.2f\n\n",
               (quickSelect(leftCopy, 0, n - 1, n / 2 - 1) +
                quickSelect(rightCopy, 0, n - 1, n / 2)) / 2.0);
    }
}

int main(void) {
    int values1[] = {7, 10, 4, 3, 20, 15};
    int values2[] = {12, 3, 5, 7, 4, 19, 26};
    int values3[] = {9, 1, 8, 2, 7};

    printf("Median and Selection using Deterministic Quickselect\n\n");
    runTest(values1, 6, 2);
    runTest(values2, 7, 3);
    runTest(values3, 5, 4);
    return 0;
}

/*
High-level idea:
Quickselect partitions the array like quicksort but only continues on the side
that contains the desired kth position.
When the pivot lands at index k, it is the kth smallest element.
For the first test, k = 2 asks for the third smallest value. Partitioning moves
smaller values left and narrows the search until the answer 7 is found.
*/
