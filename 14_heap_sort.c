/* ================================================================ */
/* HEAPS AND HEAP SORT - BUILD-HEAP + HEAPIFY */
/* ================================================================ */

/*
Algorithm name: Heap Sort
Problem it solves:
Sorts an array by building a max heap and repeatedly moving the maximum
element to the end.
Time complexity: O(n log n)
Space complexity: O(1)
*/

#include <stdio.h>

/* Swaps two integers. */
void swapInt(int *first, int *second) {
    int temp = *first;
    *first = *second;
    *second = temp;
}

/* Restores max-heap property for subtree rooted at index root. */
void heapify(int array[], int heapSize, int root) {
    int largest = root;
    int leftChild = 2 * root + 1;
    int rightChild = 2 * root + 2;

    if (leftChild < heapSize && array[leftChild] > array[largest]) {
        largest = leftChild;
    }
    if (rightChild < heapSize && array[rightChild] > array[largest]) {
        largest = rightChild;
    }
    if (largest != root) {
        swapInt(&array[root], &array[largest]);
        heapify(array, heapSize, largest);
    }
}

/* Converts an array into a max heap. */
void buildHeap(int array[], int n) {
    for (int i = n / 2 - 1; i >= 0; i--) {
        heapify(array, n, i);
    }
}

/* Sorts array in ascending order using a max heap. */
void heapSort(int array[], int n) {
    buildHeap(array, n);
    for (int end = n - 1; end > 0; end--) {
        swapInt(&array[0], &array[end]);
        heapify(array, end, 0);
    }
}

/* Prints an array. */
void printArray(const int array[], int n) {
    for (int i = 0; i < n; i++) {
        printf("%d ", array[i]);
    }
    printf("\n");
}

/* Runs one heap sort test. */
void runTest(int array[], int n) {
    printf("Before: ");
    printArray(array, n);
    buildHeap(array, n);
    printf("Max heap array: ");
    printArray(array, n);
    heapSort(array, n);
    printf("Sorted: ");
    printArray(array, n);
    printf("\n");
}

int main(void) {
    int array1[] = {12, 11, 13, 5, 6, 7};
    int array2[] = {4, 10, 3, 5, 1};
    int array3[] = {20, -2, 15, 0, 8};

    printf("Heap Sort\n\n");
    runTest(array1, 6);
    runTest(array2, 5);
    runTest(array3, 5);
    return 0;
}

/*
High-level idea:
A max heap keeps the largest value at the root.
Build-heap rearranges the array into heap order.
Heap sort swaps the root with the last active element, shrinks the heap, and
heapifies again.
For the first test, 13 becomes the root. It is moved to the end, and the
process repeats until the array is sorted.
*/
