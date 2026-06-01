/* ================================================================ */
/* MERGE SORT */
/* ================================================================ */

/*
Algorithm name: Merge Sort
Problem it solves:
Sorts an array by recursively dividing it into halves and merging sorted halves.
Time complexity: O(n log n)
Space complexity: O(n)
*/

#include <stdio.h>

#define MAX_SIZE 50

/* Merges two sorted ranges array[left..mid] and array[mid+1..right]. */
void merge(int array[], int left, int mid, int right) {
    int temp[MAX_SIZE];
    int i = left;
    int j = mid + 1;
    int k = left;

    while (i <= mid && j <= right) {
        if (array[i] <= array[j]) {
            temp[k++] = array[i++];
        } else {
            temp[k++] = array[j++];
        }
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

/* Recursively sorts array[left..right]. */
void mergeSort(int array[], int left, int right) {
    if (left < right) {
        int mid = left + (right - left) / 2;
        mergeSort(array, left, mid);
        mergeSort(array, mid + 1, right);
        merge(array, left, mid, right);
    }
}

/* Prints an array. */
void printArray(const int array[], int n) {
    for (int i = 0; i < n; i++) {
        printf("%d ", array[i]);
    }
    printf("\n");
}

/* Runs one merge sort test case. */
void runTest(int array[], int n) {
    printf("Before: ");
    printArray(array, n);
    mergeSort(array, 0, n - 1);
    printf("After:  ");
    printArray(array, n);
    printf("\n");
}

int main(void) {
    int array1[] = {38, 27, 43, 3, 9, 82, 10};
    int array2[] = {5, 1, 1, 9, 0, -2};
    int array3[] = {100, 50, 25, 75, 60};

    printf("Merge Sort\n\n");
    runTest(array1, 7);
    runTest(array2, 6);
    runTest(array3, 5);
    return 0;
}

/*
High-level idea:
Merge sort splits the array until each part has one element.
Single-element arrays are already sorted.
The merge step repeatedly chooses the smaller front element from two sorted
halves to build a larger sorted range.
For the first test, 38 27 43 3 9 82 10 is split into halves, small halves are
sorted, and merging finally produces 3 9 10 27 38 43 82.
*/
