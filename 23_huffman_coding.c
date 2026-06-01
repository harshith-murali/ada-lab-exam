/* ================================================================ */
/* HUFFMAN TREES - HUFFMAN CODING */
/* ================================================================ */

/*
Algorithm name: Huffman Coding
Problem it solves:
Builds a prefix-code tree from symbol frequencies so common symbols get
shorter binary codes.
Time complexity: O(n^2) with array-based priority queue
Space complexity: O(n)
*/

#include <stdio.h>
#include <stdlib.h>

#define MAX_SYMBOLS 20

typedef struct HuffmanNode {
    char symbol;
    int frequency;
    struct HuffmanNode *left;
    struct HuffmanNode *right;
} HuffmanNode;

/* Allocates a Huffman tree node. */
HuffmanNode *createNode(char symbol, int frequency, HuffmanNode *left,
                        HuffmanNode *right) {
    HuffmanNode *node = (HuffmanNode *)malloc(sizeof(HuffmanNode));
    if (node == NULL) {
        printf("Memory allocation failed\n");
        exit(1);
    }
    node->symbol = symbol;
    node->frequency = frequency;
    node->left = left;
    node->right = right;
    return node;
}

/* Removes and returns the minimum-frequency node from an array queue. */
HuffmanNode *extractMin(HuffmanNode *queue[], int *size) {
    int minIndex = 0;
    HuffmanNode *minNode;

    for (int i = 1; i < *size; i++) {
        if (queue[i]->frequency < queue[minIndex]->frequency) {
            minIndex = i;
        }
    }

    minNode = queue[minIndex];
    for (int i = minIndex; i < *size - 1; i++) {
        queue[i] = queue[i + 1];
    }
    (*size)--;
    return minNode;
}

/* Builds and returns the Huffman tree root. */
HuffmanNode *buildHuffmanTree(const char symbols[], const int frequencies[],
                              int n) {
    HuffmanNode *queue[MAX_SYMBOLS];
    int size = n;

    for (int i = 0; i < n; i++) {
        queue[i] = createNode(symbols[i], frequencies[i], NULL, NULL);
    }

    while (size > 1) {
        HuffmanNode *left = extractMin(queue, &size);
        HuffmanNode *right = extractMin(queue, &size);
        HuffmanNode *parent = createNode('$', left->frequency + right->frequency,
                                         left, right);
        queue[size++] = parent;
    }
    return queue[0];
}

/* Prints Huffman codes by walking left as 0 and right as 1. */
void printCodes(HuffmanNode *root, int code[], int depth) {
    if (root == NULL) {
        return;
    }
    if (root->left == NULL && root->right == NULL) {
        printf("%c: ", root->symbol);
        for (int i = 0; i < depth; i++) {
            printf("%d", code[i]);
        }
        printf(" (freq %d)\n", root->frequency);
        return;
    }
    code[depth] = 0;
    printCodes(root->left, code, depth + 1);
    code[depth] = 1;
    printCodes(root->right, code, depth + 1);
}

/* Frees all tree nodes. */
void freeTree(HuffmanNode *root) {
    if (root != NULL) {
        freeTree(root->left);
        freeTree(root->right);
        free(root);
    }
}

/* Runs one Huffman coding test. */
void runTest(const char symbols[], const int frequencies[], int n) {
    int code[MAX_SYMBOLS];
    HuffmanNode *root;

    printf("Symbols and frequencies:\n");
    for (int i = 0; i < n; i++) {
        printf("%c:%d ", symbols[i], frequencies[i]);
    }
    printf("\nCodes:\n");
    root = buildHuffmanTree(symbols, frequencies, n);
    printCodes(root, code, 0);
    freeTree(root);
    printf("\n");
}

int main(void) {
    char symbols1[] = {'a', 'b', 'c', 'd', 'e', 'f'};
    int frequencies1[] = {5, 9, 12, 13, 16, 45};
    char symbols2[] = {'x', 'y', 'z', 'w'};
    int frequencies2[] = {7, 2, 9, 4};

    printf("Huffman Coding\n\n");
    runTest(symbols1, frequencies1, 6);
    runTest(symbols2, frequencies2, 4);
    return 0;
}

/*
High-level idea:
Huffman coding repeatedly combines the two least frequent nodes.
The combined node becomes their parent with frequency equal to their sum.
After one tree remains, left edges are coded as 0 and right edges as 1.
In the first test, frequencies 5 and 9 combine first, then that new node joins
later combinations until the final prefix-code tree is formed.
*/
