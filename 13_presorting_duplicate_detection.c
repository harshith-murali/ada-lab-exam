/* ================================================================ */
/* PRESORTING - DUPLICATE DETECTION */
/* ================================================================ */

/*
Algorithm name: Presorting for Duplicate Detection
Problem it solves:
Optimizes duplicate detection by sorting first, then checking only neighboring
items instead of comparing every pair.
Time complexity: O(n log n) using merge sort, improved from O(n^2) brute force
Space complexity: O(n)
*/

#include <stdio.h>

#define MAX_SIZE 50

/* Merges sorted halves for merge sort. */
void merge(int array[], int left, int mid, int right) {
    int temp[MAX_SIZE];
    int i = left;
    int j = mid + 1;
    int k = left;

    while (i <= mid && j <= right) {
        temp[k++] = (array[i] <= array[j]) ? array[i++] : array[j++];
    }
    while (i <= mid) {
        temp[k++] = array[i++];
    }
    while (j <= right) {
        temp[k++] = array[j++];
    }
    for (i = left; i <= right; i++) {
        array[i] = temp[i];
    }
}

/* Sorts the array so duplicate values become adjacent. */
void mergeSort(int array[], int left, int right) {
    if (left < right) {
        int mid = left + (right - left) / 2;
        mergeSort(array, left, mid);
        mergeSort(array, mid + 1, right);
        merge(array, left, mid, right);
    }
}

/* Returns 1 if any duplicate exists after presorting. */
int hasDuplicateByPresorting(int array[], int n) {
    mergeSort(array, 0, n - 1);
    for (int i = 1; i < n; i++) {
        if (array[i] == array[i - 1]) {
            return 1;
        }
    }
    return 0;
}

/* Prints an array. */
void printArray(const int array[], int n) {
    for (int i = 0; i < n; i++) {
        printf("%d ", array[i]);
    }
    printf("\n");
}

/* Runs one duplicate detection test. */
void runTest(int array[], int n) {
    printf("Original array: ");
    printArray(array, n);
    printf("Duplicate exists: %s\n", hasDuplicateByPresorting(array, n) ? "yes" : "no");
    printf("Sorted array:   ");
    printArray(array, n);
    printf("\n");
}

int main(void) {
    int array1[] = {8, 3, 5, 1, 3, 9};
    int array2[] = {4, 1, 6, 2, 9};
    int array3[] = {10, 10, 2, 7, 8, 2};

    printf("Presorting for Duplicate Detection\n");
    printf("Optimized task: duplicate detection becomes a neighbor scan after sorting.\n\n");
    runTest(array1, 6);
    runTest(array2, 5);
    runTest(array3, 6);
    return 0;
}

/*
High-level idea:
Without sorting, duplicate detection checks all pairs.
After sorting, equal values must be next to each other.
The program sorts once and then scans adjacent pairs only.
For the first test, sorting changes 8 3 5 1 3 9 into 1 3 3 5 8 9.
The adjacent pair 3, 3 proves that a duplicate exists.
*/
