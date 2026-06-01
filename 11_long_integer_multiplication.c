/* ================================================================ */
/* MULTIPLICATION OF LONG INTEGERS USING ARRAYS */
/* ================================================================ */

/*
Algorithm name: Long Integer Multiplication with Digit Arrays
Problem it solves:
Multiplies large non-negative integers stored as character strings, using
arrays to hold decimal digits and intermediate carries.
Time complexity: O(n * m)
Space complexity: O(n + m)
*/

#include <stdio.h>
#include <string.h>

#define MAX_DIGITS 100

/* Multiplies two decimal strings and stores the product string. */
void multiplyLongIntegers(const char first[], const char second[], char product[]) {
    int len1 = (int)strlen(first);
    int len2 = (int)strlen(second);
    int result[2 * MAX_DIGITS] = {0};
    int start = 0;
    int index = 0;

    for (int i = len1 - 1; i >= 0; i--) {
        for (int j = len2 - 1; j >= 0; j--) {
            int digit1 = first[i] - '0';
            int digit2 = second[j] - '0';
            result[i + j + 1] += digit1 * digit2;
        }
    }

    for (int i = len1 + len2 - 1; i > 0; i--) {
        result[i - 1] += result[i] / 10;
        result[i] %= 10;
    }

    while (start < len1 + len2 - 1 && result[start] == 0) {
        start++;
    }
    for (int i = start; i < len1 + len2; i++) {
        product[index++] = (char)(result[i] + '0');
    }
    product[index] = '\0';
}

/* Runs one multiplication test case. */
void runTest(const char first[], const char second[]) {
    char product[2 * MAX_DIGITS + 1];
    multiplyLongIntegers(first, second, product);
    printf("%s * %s = %s\n", first, second, product);
}

int main(void) {
    printf("Long Integer Multiplication\n\n");
    runTest("123456789", "987654321");
    runTest("99999", "99999");
    runTest("31415926", "27182818");
    return 0;
}

/*
High-level idea:
The algorithm imitates school multiplication.
Each digit of the first number is multiplied by each digit of the second.
Products are added into positions based on decimal place, then carries are
propagated from right to left.
For 99999 * 99999, many partial products accumulate, carries are cleaned up,
and the final digit array becomes 9999800001.
*/
